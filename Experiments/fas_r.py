# -*- coding:UTF-8 -*-

'''
Refactor of fas.py

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

    Parameters:
        diG - directed graph, networkx.DiGraph.

    Returns:
        FAS, feedback arc set, tuple list.
    '''
    st = time.time()
    # init the bins
    buckets = list()
    sinks = list()
    sources = list()
    for node in diG.nodes() :
        indegree = diG.in_degree(node)
        outdegree = diG.out_degree(node)
        # classify, sources, sinks and others
        if indegree == 0 :
            sources.append(node)
        elif outdegree == 0 :
            sinks.append(node)
        else :
            d = outdegree - indegree
            buckets.append((d, node))
    buckets = bins(buckets,3-len(diG),len(diG)-3,1)
    et_init = time.time()
    print(et_init-st, 'init bins time length.')
    # generate the sequence
    s1 = list()
    s2 = list()
    s1.extend(sources)
    s2.extend(sinks)
    while not buckets.empty() :
        while len(buckets.sinks) > 0 :
            node = buckets.sinks.pop()
            innodes = diG.predecessors(node)
            buckets.move(innodes)
            s2.append(node)
        while len(buckets.sources) > 0 :
            node = buckets.sources.pop()
            s1.append(node)                     # actually, the sources have no incident edges
        node = buckets.maxPop()
        innodes = diG.predecessors(node)
        buckets.move(innodes)
        s1.append(node)
    s2.reverse()
    s1.extend(s2)
    et_generate = time.time()
    print(et_generate-et_init, 'generate the sequence time length.')
    # find all leftward edges
    cmpidx = dict()                             # store the indexes of each node
    fset = list()
    for index,node in enumerate(s1) :
        cmpidx[node] = index
    for node in s1 :
        outnodes = diG.successors(node)
        for outnode in outnodes :
            if cmpidx[node] < cmpidx[outnode] :
                fset.append((node, outnode))
    et_fas = time.time()
    print(et_fas-et_generate, 'find all left forward edges time length.')
    # sometimes the left forward edges is more than the right forward edges. Return the smallest set.
    copy = diG.copy()
    if len(fset) > copy.size()/2 :
        copy.remove_edges_from(fset)
        return copy.edges()
    else :
        return fset

if __name__ == '__main__' :
    data = pd.read_table('/Users/xjd/Desktop/experiments/datasets/wiki-Vote.txt')
    G = nx.from_pandas_dataframe(data, 'Source', 'Target', create_using=nx.DiGraph())
    msG = max(nx.weakly_connected_component_subgraphs(G), key=len)
    fas = fas(msG)
    msG.remove_edges_from(fas)
    print(len(fas), 'the feedback arc set length.')
    print('The final graph is DAG ? ', nx.is_directed_acyclic_graph(msG))
