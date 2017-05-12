# -*- coding:UTF-8 -*-

from decorators import timer
import numpy as np

class Car() :

    def __init__(self, peak_hour_start=0, peak_hour_end=7200, capacity=20, location=None, speed=5, geo_matrix=None, gon_speed=2, goff_speed=2, id=0, qos=900, dock_basetime=10) :
        '''
        `peak_hour_start`           表示高峰期起始时间
        `peak_hour_end`             表示高峰期结束时间
        `capacity`                  表示车辆的可以容纳多少人
        `available_seats`           记录当前车辆可用座位
        `depots_queue`              当前车辆的行车路线，到达一个地点就将其从该队列中移除
        `on_board_requests`         表示当前还没下车的requests
        `next_depot`                表示车辆下一站开往哪里
        `timestamp`                 表示车辆当前时间点
        `qos_timestamp`             表示车辆从第一个request开始，已经消耗的时间，最大不超过900
        `requests_transactions`     记录了旅客上下车的流水，一次车站停靠将上下车的旅客的Request统一记录到一个list中，再讲该list加入transactions中
                                    存储结构: requests_transactions = [(depot_id, [request1, request2, ...), ...]
        `ready_to_get_on_requests`  表示下一站将要上车的Request
        `speed`                     表示车辆行驶速度
        `geo_matrix`                表示地理距离矩阵
        `id`                        表示车辆身份的唯一数字标识符
        `qos`                       表示QoS的约束为多大
        `dock_basetime`             表示车辆每次靠站固定消耗时间
        '''
        self.peak_hour_start            = peak_hour_start
        self.peak_hour_end              = peak_hour_end
        self.capacity                   = capacity
        self.available_seats            = capacity
        self.depots_queue               = list()
        self.on_board_requests          = list()
        self.next_depot                 = None
        self.timestamp                  = 0
        self.qos_timestamp              = 0
        self.requests_transactions      = list()
        self.ready_to_get_on_requests   = None
        self.speed                      = speed
        self.geo_matrix                 = geo_matrix
        self.id                         = id
        self.qos                        = qos
        self.dock_basetime              = dock_basetime

    def __len__(self) :
        return len(self.requests_transactions)

    def ready_to_get_on(self, requests, depots) :
        '''
        设置待服务Request, 设置该Request的对应车站队列，并设置下一站
        '''
        self.ready_to_get_on_requests   = requests
        self.depots_queue               = depots
        try :
            self.next_depot             = self.depots_queue.pop(0)
        except :
            print('Car %d 已经完成使命'.format(self.id))

    def simulate_target_arrival_time(self, target_depot) :
        return self.timestamp + self.geo_matrix[self.location, target_depot] / self.speed

    def available_seats(self) :
        '''
        车辆所剩座位
        '''
        return self.available_seats
    
    def QoS(self, prep_request, plan, extra_on_board) :
        '''
        计算输入的request是否满足QoS小于qos的约束，如果满足，则返回重新规划的行车路径，否者返回None
        '''
        plan = self.insert_depot(prep_request, plan)
        on_board_people = 0
        total_distance  = 0
        for request in extra_on_board :
            on_board_people += request.seats
        for request in self.on_board_people :
            on_board_people += request.seats
        total_distance += self.geo_matrix[self.location, prep_request.from_depot]
        total_distance += self.geo_matrix[prep_request.from_depot, plan[0]]
        for i in range(1, len(plan)-1) :
            total_distance += self.geo_matrix[plan[i], plan[i+1]]
        predict_time = (on_board_people + self.on_board_people + prep_request.seats) * self.goff_speed + prep_request.seats * self.gon_speed + total_distance / self.speed
        if predict_time + self.qos_timestamp + self.dock_basetime * (len(plan)+1) > self.qos :
            return None
        else :
            plan.insert(0, prep_request.from_depot)
            return plan

    def insert_depot(self, request, plan) :
        '''
        按最小代价插入depot
        '''
        v = dict()
        for depot in request.to_depots :
            h = dict()
            # 如果插入最前
            h[0] = self.geo_matrix[request.from_depot, depot] + self.geo_matrix[depot, plan[0]] - self.geo_matrix[request.from_depot, plan[0]]
            # 中间
            for i in range(1, len(plan)) :
                h[i] = self.geo_matrix[plan[i-1], depot] + self.geo_matrix[depot, plan[i]] - self.geo_matrix[plan[i-1], plan[i]]
            # 插入最末尾
            h[len(plan)]    = self.geo_matrix[plan[-1], depot]
            # 选最小
            h               = zip(h.values(), h.keys()))
            min_value       = min(h)
            v[min(h)] = (depot, h[min_value])
        (depot, key) = v[min(v)]
        plan.insert(key, depot)
        return plan

    def timestamp(self) :
        '''
        返回此车当前的时间戳(距离出发时间)
        '''
        return self.timestamp

    def is_peak_hour(self) :
        '''
        用当前时间戳判断是否在高峰期
        '''
        if self.peak_hour_start <= self.timestamp <= self.peak_hour_end :
            return True
        return False

    def get_off(self) :
        '''
        完成下车动作，并计算时间
        '''
        seats = 0
        get_off_time = list()
        for request in self.on_board_requests :
            if self.location in request.to_depots :
                request = self.on_board_requests.pop(request)
                seats += request.seats
                get_off_time.append(request)
        self.available_seats += seats
        return self.goff_speed * len(seats), get_off_time

    def get_on(self) :
        '''
        完成上车动作，设置Request的服务状态，计算时间。
        '''
        self.on_board_requests.extend(self.ready_to_get_on_requests)
        seats = 0
        get_on_requests = list()
        for request in self.ready_to_get_on_requests :
            seats += request.available_seats
            request.satisfied = True
            get_on_time.append(request)
        self.available_seats -= seats
        return self.gon_speed * len(seats), get_on_requests

    def dock(self) :
        '''
        车辆到站停靠，需要确认哪些旅客上车，哪些旅客下车。
        '''
        # 不要更改赋值顺序
        last_depot                      = self.location
        self.location                   = self.next_depot
        get_off_time, get_off_requests  = self.get_off()
        get_on_time, get_on_requests    = self.get_on() 
        self.qos_timestamp              += self.geo_matrix[self.location, self.next_depot] / self.speed + get_on_time + get_off_time + self.dock_basetime
        self.timestamp                  = self.timestamp + self.geo_matrix[self.location, self.next_depot] / self.speed + get_on_time + get_off_time + self.dock_basetime
        self.requests_transactions.append((self.location, get_on_requests.extend(get_off_requests)))
        if len(self.on_board_requests) == 0 :
            self.qos_timestamp = 0

    def location(self) :
        '''
        返回车辆当前位置
        '''
        return self.location

class Depot() :

    def __init__(self, index, x, y) :
        '''
        `x` 表示该站的x坐标
        `y` 表示该站的y坐标
        `index` 表示该车站对应于地理矩阵的索引
        '''
        self.x      = x
        self.y      = y
        self.index  = index

    def __str__() :
        return 'Depot %d'.format(self.index)

class Request() :

    def __init__(self, available_start_time, available_end_time) :
        '''
        `satisfied`             表示该请求是否得到满足
        `depart_time`           表示乘客实际离开时刻
        `arrive_time`           表示乘客实际到达时刻
        `available_start_time`  表示乘客开始等待时刻
        `available_end_time`    表示乘客等待无效，离开时刻
        `from_depot`            表示出发车站
        `to_depots`              表示到达车站列表(有多个候选站点)
        `seats`                 表示需要的座位数
        '''
        self.satisfied              = False
        self.depart_time            = None
        self.arrive_time            = None
        self.available_start_time   = available_start_time
        self.available_end_time     = available_end_time
        self.from_depot             = None
        self.to_depots              = None
        self.seats                  = 0


class ACO() :
    '''
    目标：实现蚁群算法在PHVRP上的应用
    输入：由Depot构成的一个列表，由Request构成的一个列表。
    输出：由Request构成的6条最优路径（即一个解）

    约束：PHVRP 1. 点序列的总耗时不超过7200s (只考虑2个小时之间的请求)
                2. QoS不超过900s (去往下一个纯接客地点的时间不超过900s)

    @@@ 此算法消耗大量存储空间，消耗空间为三部分：
            1. 原始数据(形参: space(depots) + space(requests) + space(cars) )
            2. 循环数据(需要动态修改的数据，一般为原始数据的硬拷贝: space(depots) + space(requests) + space(cars) )
            3. 历史数据(使用过得数据，一般为循环数据的最终版本，会保存到历史数据中: num_of_generation * (space(requests) + space(cars)) )
    '''

    def __init__(self, requests=None, cars=None, geo_matrix=None, num_of_generation=0, precision=0.01) :
        '''
        `num_of_generation` 表示解迭代次数
        `precision` 表示判停精度
        `geo_matrix` 存储地理信息，边权为两点之间的长度
        `pheromone_matrix` 存储信息素信息，边权为两点之间的信息素浓度
        `depots` 表示所有车站信息，是个list
        `requests` 记录了所有原始Request
        `cars` 记录所有原始Car
        `requests_queue` 是在运行时动态变化的Request，每次迭代初始化为`requests`的硬拷贝
        `cars_queue` 是在运行时动态变化的Car，每次迭代初始化为`cars`的硬拷贝
        `cars_completed` 是运行时每次迭代后的Car的一个list，可以从里面提取解
        `cars_transactions` 是每次迭代的解的全局记录
        `requests_transactions` 是每次迭代的requests的最终状态的一个全局记录
        `global_optimized_transactions` 是全局最优解
        '''
        self.num_of_generation              = num_of_generation
        self.precision                      = precision
        self.geo_matrix                     = geo_matrix
        self.pheromone_matrix               = np.zeros(self.geo_matrix.shape, dtype=np.float64)
        self.requests                       = requests
        self.cars                           = cars
        self.requests_queue                 = None
        self.cars_queue                     = None
        self.cars_completed                 = None
        self.cars_transactions              = list()
        self.requests_transactions          = list()
        self.global_optimized_transactions  = None

    def main(self) :
        '''
        `num_of_generation` 表示迭代几次, 然后每一次迭代都要将`cars_queue`初始化
        每一次迭代都需要完成一次解的求解过程：1. 选取队首车辆. 2. 更新此车状态并重新插入到
        队列中(wheel函数) 3. 将解的Request记录，和Car记录全部记录下来。4. 更新信息素
        '''
        iteration = self.num_of_generation
        while(iteration) :
            self.cars_queue             = self.cars.copy()
            self.requests_queue         = self.requests.copy()
            self.cars_completed         = list()
            while(len(self.cars_queue)) :
                car = self.cars_queue.pop(0)
                wheel(car)
            self.update_transactions()
            self.volatile_pheromone()
            self.release_pheromone()
            iteration -= 1

    def update_trasactions(self) :
        '''
        记录解
        '''
        self.cars_transactions.append(self.cars.cars_completed.copy())
        self.requests_transactions.append(self.requests_queue.copy())

    def volatile_pheromone(self) :
        '''
        信息素挥发
        '''
        self.pheromone_matrix * 0.7

    def release_pheromone(self) :
        '''
        更新图中的信息素
        '''
        local_opimized_transactions = self.transactions_request_first(self.cars_completed)
        min_pheromone               = 0
        pheromone_array             = list()
        avg_pheromone               = 0
        for car in self.cars_completed :
            # 获取该车行驶路径上的信息素
            # 先将transactions格式转换成(u,v)节点对
            paths = self.get_paths(car.requests_transactions)
            for (u, v) in paths :
                link_pheromone      = self.pheromone_matrix[u, v]
                pheromone_array.append(link_pheromone)
        min_pheromone   = min(pheromone_array)
        avg_pheromone   = sum(pheromone_array) / len(pheromone_array)
        # 首先将所有路径上的link的信息素增加`min_pheromone`
        # 如果路径优于全局最优路径，则再增加`min_pheromone`
        # 如果路径优于当前最优路径，则再增加`min_pheromone`
        local_optimized_mark    = referee(local_opimized_transactions, 'request_first')
        global_optimized_mark   = referee(self.global_optimized_transactions, 'request_first')
        for car in self.cars_completed :
            paths           = self.get_paths(car.requests_transactions)
            current_mark    = referee(car.requests_transactions, 'request_first')
            # 例行公事
            for (u,v) in paths :
                self.pheromone_matrix[u,v] += min_pheromone
            # 如果大于全局最优，再加一点
            if current_mark >= global_optimized_mark :
                for (u,v) in paths :
                    self.pheromone_matrix[u,v] += min_pheromone
            # 如果还大于当前最优，再加一点
            if current_mark >= local_optimized_mark :
                for (u,v) in paths :
                    self.pheromone_matrix[u,v] += min_pheromone
        # 更新全局最优
        if local_optimized_mark > global_optimized_mark :
            self.global_optimized_transactions = local_opimized_transactions

    def get_paths(self, transactions) :
        '''
        将transactions转换成节点对(u,v)
        '''
        paths = list()
        for index in range(0, len(car.transactions)-1) :
            (depot_id, _)       = car.transactions[index]
            (next_depot_id, _)  = car.transactions[index+1]
            paths.append((depot_id, next_depot_id))
        # 最后一跳
        # (depot, requests)   = car.transactions[-1]
        # last_depot          = requests[0].to_depot
        # paths.append((depot, last_depot))
        return paths

    def referee(transactions, factor='request_first') :
        '''
        返回当前路径的评价指标
        '''
        mark = 0
        if factor == 'request_first' :
            for (depot, requests) in transactions :
                mark += len(requests)
        elif factor == 'people_first' :
            for (depot, requests) in transactions :
                for request in requests :
                    mark += request.seats
        return mark

    def next_requests(self, car) :
        '''
        利用轮盘法从邻域里面选取最合适的下一个站点, 比较规则为左闭右开
        返回类型：requests
        '''
        nerghbors, plans        = self.nerghborhood(car)
        roulette                = dict()
        cumulative_probability  = 0
        cumulative_pheromone    = 0
        from_depot              = car.location()
        next_depot              = None
        requests                = list()
        plan                    = list()
        if nerghbors == None :
            return None
        for (to_depot, requests) in nerghbors :
            cumulative_pheromone    = self.pheromone_matrix[from_depot, request.to_depot]
        for (to_depot, requests) in nerghbors :
            pheromone                           = self.pheromone_matrix[from_depot, to_depot]
            probability                         = pheromone / cumulative_pheromone
            cumulative_probability              = (cumulative_probability, cumulative_probability + probability)
            roulette[cumulative_probability]    = request
        # 轮盘针
        pointer = np.random.rand()
        # 轮盘法选择下一个目的地
        for (low_bound, up_bound) in roulette.keys() :
            if low_bound <= pointer < up_bound :
                next_depot = roulette[(low_bound, up_bound)].from_depot
        # 确定下一个目的地有哪些乘客上车
        for (depot, requests) in nerghbors :
            if next_depot == depot :
                requests.extend(requests)
        for (depot, p) in plans :
            if next_depot == depot :
                plan.extend(p)
        return requests, plan

    def nerghborhood(self, car) :
        '''
        选择当前车的邻域(指优化算法中邻域的概念)
        返回类型：Request 列表
        返回格式：transactions  : [(depot, [request1, request2, ...]), ...]
                    depots      : [(depot, [depot1, depot2, ...]), ...]
        条件：  1. 选择的Requests的需要座位数量是Car所能提供的
                2. 选择的Requests的时间窗口是Car能到达的
                3. 选择的Requests的以及车上的Requests都要符合QoS，服务时间不超过900s

        '''
        # 遍历所剩Request的列表，
        # 如果满足 :
        #           1. 此Request所需要的座位数，是我这台车所能提供的
        #           2. 此Request的等待窗口，是我这台车所能到达的，即我这台车能在Request的等待窗口到达其所在depot
        #           3. 我这台车去这个Reqeust的depot所需要的时间不超过900s (Qos time)
        # 则将此Request加入到邻域当中
        nerghbors       = dict()
        modified_plan   = dict()
        for request in self.requests_queue :
            if request.satisfied == False :
                if car.available_seats() > request.seats :
                    if request.available_start_time <= car.simulate_target_arrival_time(request) <= request.available_end_time :
                        # 计算加入此Request时的QoS，如果计算成功，QoS函数会返回重新规划的路径，否则返回None
                        # 如果计算成功，将对应站点的行车计划更新(这一步是为了避免后续的重复计算)
                        # 并将对应站点欲上车乘客记录下来
                        plan            = None # 行车计划，如果已经计算过，则直接提取，如果没有，初始化
                        extra_on_board  = None # 传给QoS计算人数
                        if request.from_depot in modified_plan.keys() :
                            plan = modified_plan[request.from_depot]
                        else :
                            plan = car.depots_queue.copy()
                        if request.from_depot in nerghbors.keys() :
                            extra_on_board = nerghbors[request.from_depot]
                        plan = car.QoS(request, plan, extra_on_board)
                        if plan :
                            modified_plan[request.from_depot] = plan
                            try :
                                nerghbors[request.from_depot].append(request)
                            except :
                                nerghbors[request.from_depot] = list()
                                nerghbors[request.from_depot].append(request)
        return list(zip(nerghbors.keys(), nerghbors.values())), list(zip(modified_plan.keys(), modified_plan.values()))
    
    def transactions_request_first(cars) :
        '''
        在判断路径优秀程度时，Request数量优先
        '''
        optimized       = None
        optimized_score = 0
        for car in cars :
            score = 0
            for (depot, requests) in car.requests_transactions :
                score += len(requests)
            if score > optimized_score :
                optimized_score = score
                optimized = car.requests_transactions
        return optimized

    def transactions_people_first(cars) :
        '''
        在判断路径优秀程度时，服务的人数数量优先
        '''
        optimized       = None
        optimized_score = 0
        for car in cars :
            score = 0
            for (depot, requests) in car.requests_transactions :
                for request in requests :
                    score += request.seats
            if score > optimized_score :
                optimized = car.requests_transactions
                optimized_score = score
        return optimized

    #def service_request_first(requests, available_seats) :
    #    '''
    #    Request 数量优先
    #    '''
    #    desitiny = list()
    #    sorted(requests, key=lambda x: x.seats)
    #    while(available_seats > 0 and len(requests)) :
    #        request = requests.pop(0)
    #        available_seats -= request.seats
    #        if available_seats < 0 :
    #            break
    #        desitiny.append(request)
    #    return desitiny

    #def service_people_first(requests, available_seats) :
    #    '''
    #    人数优先(贪心)
    #    '''
    #    pass

    def wheel(self, car) :
        '''
        每次有一辆车靠岸后，都要重新调用这个方法来确定先后顺序 (先到的车，有优先选择request的权利)
        返回类型: index, 当前car在`cars_queue`中的插入点
        寻找插入点，更新车状态
        '''
        # dock函数确定哪些乘客上车，哪些乘客下车，确定车辆容量
        # 然后搜索附近有无需要上车的乘客，如果有，将其插入到car的停靠站点中
        # 否则按原计划行驶。
        car.dock()
        requests, plan = self.next_requests(car)
        car.ready_to_get_on(requests, plan)
        if car.is_peak_hour() :
            for index,c in enumerate(self.cars_queue) :
                if car.timestamp() < c.timestamp() :
                    self.cars_queue.insert(index, car)
        else :
            self.cars_completed.append(car)

def construct() :
    '''
    将depots和 生成的图中的索引绑定起来,即每个depots对应矩阵中的一个索引
    返回类型：ndarray, Depot列表, Request列表
    # 地理分布范围：  2000m x 2000m

    '''
    # 生成一系列depots
    # Depot 数量：    100个

    # Request 数量：  1000个


    # 此处的Car 实际上相当于蚁群算法中的蚂蚁，所以Car的数量不是由多少车辆决定，而是由多少蚂蚁决定的。
    # 蚂蚁数量：  30个
   

    # 构建地理矩阵
    # 所有索引都按照标准从0开始
    matrix = np.zeros((len(depots), len(depots)), dtype=np.float64)
    for index,depot in enumerate(depots) :
        depot.index = index
    return matrix

if __name__ == '__main__' :
    #depots              = None
    #requests            = None
    #cars                = None
    #num_of_generation   = 30
    #aco                 = ACO(geo_matrix=construct_geo_matrix(depots), requests=requests, cars=cars, num_of_generation=num_of_generation)
    #aco.main()
