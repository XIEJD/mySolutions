#-*- coding:utf-8 -*-

'''
    Data structure and algorithms for sorting problem.

    Include:
        bin sort

    Author:
        ExcitedX

    Date:
        2016.12.21
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

    def __init__(self, start, end, step) :
        self.start = start
        self.step = step
        self.end = end
        self.bins = {index : list() for index in range(start, end, step)}
        self.maps = None

    def initSort(self, tuples, idxfield=0) :
        '''
        Init the bins according to the given tuples, I don't want to init it in the __init__,
        I want to sort the data just when I call it.

        Parameters:
            tuples - the data to be sorted which are tuples
            idxfield - the field to be indexed, the value of that field is the index of bins

        Return:
            None
        '''
        self.increSort(tuples,idxfield)
        for (t1, t2) in incretuples :
            binid = (t1,t2)[idxfield]
            self.maps[(t1,t2)[abs(idxfield-1)]] = binid     # I don't like the abs(idxfield-1) to make 1 the 0 and make 0 the 1. Can anybody give an advice?


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
            self.bins[binid].append(value)
            self.maps[value] = binid

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
            del self.bins[self.maps[item]]
            del self.maps[item]

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
            self.bins[self.maps[item]+howto] = self.bins[self.maps[item]]       # copy first
            del self.bins[self.maps[item]]                                      # then delete
            self.maps[item] = self.maps[item] + howto                           # update maps information

    def isEmpty(self) :
        return True if len(self.maps) == 0 else False










