# -*- coding:UTF-8 -*-

'''
Restructure of fas.py

Author:
    ExcitedX

Date:
    2016.12.22
'''

import pandas as pd
import networkx as nx
import time
from binsort import bins

def fas(diG) :
    '''
    balabalabala, I don't want to write the document.

    Returns:
        FAS, feedback arc set 
    '''
    # init the bins
    buckets = bins()
    sinks = list()
    sources = list()


    # generate the sequence

    # find all leftward edges
