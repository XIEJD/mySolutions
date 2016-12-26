#-*- coding:utf-8 -*-

'''
    Data structure and algorithms for sorting problem.

    Include:
        bin sort - TODO: refactor code, reduce the loops.

    Author:
        ExcitedX

    Date:
        2016.12.26
'''

class bins :
    '''
    Bins
    - for the use of the algorithm presented in fas.py, this may be a little different from the classical bin sort algorithm
    the sturcture of bins is {bin1:list(), bin2:list(), ...}

    Parameters :
        start - the start index of bin
        step - the interval of each step
        end - the end index of bin 
    '''

    def __init__(self, tuples, start, end, step, idxfield=0) :
        self.start = start
        self.step = step
        self.end = end
        self.maps = dict()
        self.sources = list()       #  the sources and sinks bin are not in the bins, they are the reserve bins at the head and tail
        self.sinks = list()         #
        self.bins = {index : list() for index in range(start, end, step)}
        self.__initSort(tuples, idxfield)

    def __initSort(self, tuples, idxfield=0) :
        '''
        Oh no.

        Parameters:
            tuples - the data to be sorted which are tuples
            idxfield - the field to be indexed, the value of that field is the index of bins

        Return:
            None
        '''
        self.increSort(tuples,idxfield)
        for (t1, t2) in tuples :
            binid = (t1,t2)[idxfield]
            self.maps[(t1,t2)[abs(idxfield-1)]] = binid     # I don't like the abs(idxfield-1) to make 1 the 0 and make 0 the 1. Can anybody give an advice?
        self.upper = self.maxidx()                          # the maximum index of bins which are not empty
        self.lower = self.minidx()


    def increSort(self, incretuples, idxfield=0) :
        '''
        Incremental sort, this function will not sort all of the data in bins,
        but only sort the given incremental tuples 

        Parameters:
            incretuples - incremental tuples to be sorted
            idxfield - the field to be indexed, the value of that field is the index of bins, defualt is 0

        Return:
            None
        '''
        for (t1,t2) in incretuples : 
            binid = (t1,t2)[idxfield]
            value = (t1,t2)[abs(idxfield-1)]
            self.bins[binid].append(value)                  # put the value into bin
            self.maps[value] = binid                        # record the bin's index the value stored
        self.__boundary()                                   # update the maximum index and minimum index


    def remove(self, items) :
        '''
        Remove items from bins.
        the items is not tuples, it's a list, I know exactly the bins' id where items are

        Parameters:
            items - list consists of items to be removed

        Return:
            None
        '''
        for item in items :
            self.bins[self.maps[item]].remove(item)
            del self.maps[item]
        self.__boundary()                                                       # update the boundaries

    def move(self, items, howto=-1) :
        '''
        Move the item from the nth bin to (n+howto)th bin

        Parameters:
            items - the item to be moved
            howto - Number, if negtive , then the item is moved to smaller bins, vice-versa

        Return:
            None
        '''
        for item in items :
            try :
                index = self.maps[item]
            except :
                continue
            if index+howto < self.start :
                del self.maps[items]
                self.sinks.append(item)                                         # out of the lower boundary, add the item to the sinks
            elif index+howto > self.end :
                del self.maps[item]
                self.sources.append(item)
            else :
                self.bins[index+howto].append(item)                       # copy first
                self.bins[index].remove(item)                             # then delete
                self.maps[item] = self.maps[item] + howto                           # update maps information
        self.__boundary()

    def empty(self) :
        return True if len(self.maps)+len(self.sinks)+len(self.sources) == 0 else False

    def maxidx(self) :
        '''
        Find the maximum index of bins

        Parameters:
            None

        Return:
            Maximum index, Integer
        '''
        try :
            return max(self.maps.values())
        except :
            return None

    def minidx(self) :
        '''
        Find the minimum index of bins

        Parameters:
            None

        Return:
            Minimum index, Integer
        '''
        try :
            return min(self.maps.values())
        except :
            return None

    def __boundary(self) :
        '''
        Get the min and max index of bins which are not empty.
        This function will search the bins not empty from start and end

        Parameters:
            None

        Return:
            None
        '''
        self.upper = self.maxidx()
        self.lower = self.minidx()

    def result(self) :
        '''
        Output the result

        Parameters:
            None

        Return:
            sorted sequence, list
        '''
        self.seq = list()
        for i in range(self.lower, self.upper+self.step, self.step) :
            for j in range(0, len(self.bins[i]), 1) :
                self.seq.append(self.bins[i][j])
        return self.seq
    
    def maxPop(self) :
        '''
        pop one of the maximum bin's items
        '''
        node = self.bins[self.maxidx()].pop()
        del self.maps[node]
        self.__boundary()
        return node


if __name__ == '__main__' :
    buckets = bins([(1,5),(2,4),(3,3),(4,2),(5,1)], 1, 6, 1)
    buckets.remove([5])
    buckets.remove([1])
    print(buckets.result())
    print('max index:', buckets.maxidx())
    print('min index:', buckets.minidx())
    buckets.increSort([(5,8)])
    print(buckets.result())
    print('max index:', buckets.maxidx())
    print('min index:', buckets.minidx())
    buckets.move([8],-4)
    print(buckets.result())
    print('max index:', buckets.maxidx())
    print('min index:', buckets.minidx())
