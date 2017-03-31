# Iterative Development

> * author : XJD
> * date : 2017-3-30
> * email : xiejidong888@qq.com

---
## Mixin

> **Open Problems in Graph Searching**
>
> Reference : Bonato A, Yang B. Graph searching and related problems[M]//Handbook of Combinatorial Optimization. Springer New York, 2013: 1511-1558.
>
> 1. The problem of determining the edge search number is NP-complete. 
> This problem remains NP-complete for graphs with a maximum vertex degree of 3. 
> However, whether the problem remains NP-complete for planar graphs is still unknown. 
> In fact, the complexity of determining the search number of planar graphs in all search games is unknown.
> 2. The problems of designing efficient polynomial time approximation algorithms for computing the search number of all search games are wide open. 
> There are only few results for special classes of graphs. 
> For example, .n log n time 2-approximation algorithm for computing the pathwidth (or node search number) of outerplanar graphs.
> 3. Finding good lower bounds for search numbers is a challenge for all search games mentioned in this chapter. There are few results for lower bounds.
> 4. Whether there is a modified version of the directed treewidth that has an exact min-max theorem with the search number in the associated game remains an open problem
> [Directed tree-width](#)
> 5. ...

* **概念(What)**

     1. `Botnets` : 俗称僵尸网络，指控制者采用某种手段，将互联网上大量主机感染bot程序(僵尸程序)，从而将受感染主机供控制者使用以达到某种目的(比如DDOS)
        * 由 一个botmaster，一个或多个C&C，多个bots 组成
        * bot 具有感染性

* **为什么要这样设计模型(Why)**

    1. 为什么要用这种模型(其和原模型的区别有什么意义？) ?

    2. 限制条件有什么意义？

    3. 优化目标有什么意义？

    4. graph searching 问题在此模型上有哪些性质 ?
        * search-width 的上下届 ？
        * monotonicity ?

* **为什么要设计这样的算法**

    1. 问题有多难 ？算法设计出来有什么好处 ？

    2. 算法设计时的难点在哪 ？

    3. 算法评价指标 ？ 为什么用这种评价指标 ？


## Modeling 

1. **Definition 1** : ***meta status*** of $$nodes$$ in $$ G $$
    * `contaminated`
    * `cleaned`
    * `guarded`

2. **Definition 2** : ***meta status*** of $$edges$$ in $$G$$
    * `contaminated`
    * `limited`
    * `cleaned`

3. **Definition 3** : ***meta operations*** of $$searchers$$ in $$G$$
    * `place`
    * `clean`
    * `wait`
    * `interupt` : 这个操作是为在允许重复感染情况下准备的

4. **Properties Definitions**
    * monotonicity : 当所有 $$searchers$$ 的 `clean` 操作得到的结果都为 `cleaned` 时，证明这个图是单调的
    * cost : 所有 $$searchers$$ 的 `wait` 操作的时长加起来，就是算法损耗。
    * 所有 $$searchers$$ 的 `clean` 操作之和大于等于点的权重之和

#### 带点权有向无环图

1. **Move Strategy** : $$searchers$$ 的移动规则

    1. normal strategy

            STEP(G, S) :
                for s in S :
                    if C is empty :
                        break
                    if s is clean_over :
                        next_node = C.pop()
                        if next_node has no incomming edges from contaminated nodes :
                            place(s, ->next_node)
                            clean(s.w)
                        else :
                            continue

    2. limited strategy

            STEP(G, S, LE) :
                for s in S :
                    if C is empty :
                        break
                    if s is clean_over :
                        if has_LimitedEdges(s) :
                            next_node = nearest_LimitedEdge(s)
                            place(s, ->next_node)
                            clean(s.w)
                        else :
                            wait(s)

    3. exclusive strategy

            STEP(G, S) :
                for s in S :
                    if C is empty :
                        break
                    if s is clean_over :
                        next_node = C.pop()
                        if next_node has no incomming edges from contaminated nodes & there exist a path has no searcher to next_node :
                            place(s, ->next_node)
                            clean(s.w)
                        else :
                            continue

2. **Model Properties** : 模型性质
    * search-width 的下界 或 上界 (搜索完图所需要的最小 $$searchers$$ 的数量)
    * NP-hard
    * monotonicity (单调性)


#### 带点权有向图

> **How to handle cycles ?**
>
> 1. breaking cycles. 在开始算法前，先找到图的FAS集，将之从图中移除，使有向图转化为有向无环图。
> 2. guarding key nodes. 在开始算法前，先找到图中的关键点集，当有searchers驻守在点集上的点时，图中的环会被阻塞，从而可以用有向无环图的方法处理这个图。

1. **Breaking cycles**

    * 思路和原论文思路一样，计算 FAS 后，从图中去环，应用DAG的算法。



2. **Guarding key nodes** : 将 searchers 分为两类：1、cleaners。2、guarders。

    * Full guarded : 预先将所有 key nodes 驻守 guarders.

    * Partial guarded : 运行时驻守，保证一定范围内的点不被重复感染。

