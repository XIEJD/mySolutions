#-*- coding : UTF-8 -*-

import networkx as nx

def construct_strategy(edges, s) :
    '''
    This function corresponds to the Algorithm 3.

    Parameters :
        G - DAG or DAGs
        edges - an edges order explored by mDFS algorithms.
        s - number of searchers.

    Return :
        sigma - Multi-D list, a search strategy sigma = (V1,V2,V3,...,Vt), V is a set consists of s nodes or less.
    '''
    sigma = list()
    V = set()
    for (index,(node_s, node_e)) in enumerate(edges) :
        if (node_s not in V) or (node_e not in V) :
            V.add(node_s)
            V.add(node_e)
        try :
            node_next = edges[index+1][0]
        except :
            node_next = None
        if len(V) == s or ((node_e is not node_next) and (s - len(V) < 2)) :
            sigma.append(V)
            V = set()
    return sigma

