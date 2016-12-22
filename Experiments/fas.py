#-*- coding:UTF-8 -*-

'''
    FAS, Feedback arc set.

    Reference:
        Eades P, Lin X, Smyth W F. A fast and effective heuristic for the feedback arc set problem[J]. Information Processing Letters, 1993, 47(6): 319-323.

    Author:
        ExcitedX

    Date:
        2016.12.17
'''

import pandas as pd
import networkx as nx
import time

class Tools :

    def fas(self,diG) :
        '''
        This is the implementation of the referenced algorithm, utilizing the pandas module and networkx module to accelerate the processing for big data set.
        This implementation is ugly, if you have better scheme, please open an issue or pull request.
    
        Parameters :
            diG - directed graph, networkX.DiGraph()
    
        Return :
            fset - tuple list, feedback arc set
        '''
        st = time.time()
        self.bins = dict([(l,dict()) for l in range(3-len(diG), len(diG)-2)])  
        # nodes are not sinks or sources will store in this list according to the value of outdegree-indegree
        self.sinks = list()                                                 # nodes are sinks
        self.sources = list()                                               # nodes are sources
        s1 = list()      
        s2 = list()
        self.maxidx = 0                                                     # the bin's index of the max(outindegree-indegree)
        self.minidx = 3-diG.__len__()
        self.nodeidx = dict()                                               # the bin's index of each node, exclude the sources and sinks
        fset = list()                                                       # the feedback arc set
        # init the basic information for generating the sequence
        for node in diG.nodes() :
            indegree = diG.in_degree(node)
            outdegree = diG.out_degree(node)
            if indegree is 0 :
                self.sources.append(node)
                self.nodeidx[node] = None
            elif outdegree is 0 :
                self.sinks.append(node)
                self.nodeidx[node] = None
            else :
                d = outdegree - indegree
                if self.maxidx < d :
                    self.maxidx = d
                self.bins[d][node] = outdegree                              # I think there will not produce any sources in the following steps.
                self.nodeidx[node] = d
        et_init = time.time()
        print(et_init-st,'init bins time length.')
        # generate the sequence greedily
        # I suppose that the d=outdegree-indegree is always smaller and smaller, so there will not appear source any more but sinks.
        while len(self.bins[self.maxidx]) > 0 :
            #s2.extend(self.sinks)
            #self.sinks.clear()
            while len(self.sinks) > 0 :                                                 
                node = self.sinks.pop()                                     # selecte a sink and concatenate it with the s1
                s2.append(node)
                innodes = diG.predecessors(node)
                self._update(innodes)                                       # update the information in bins, sinks and nodeidx
            s1.extend(self.sources)
            self.sources.clear()
            (maxnode, od) = self.bins[self.maxidx].popitem()                # find the max(outdegree-indegree) and concatenate it with s1
            self.nodeidx[maxnode] = None
            s1.append(maxnode)
            innodes = diG.predecessors(maxnode)                             # find all in nodes and update their value in bins
            self._update(innodes)                                           # update the information in bins sinks and nodeidx
        s2.extend(self.sinks)
        s2.reverse()
        s1.extend(s2)
        et_generate = time.time()
        print(et_generate-et_init,'generate the sequence time length.')
        # find all left forward edges
        cmpidx = dict()                                                     # reverse the key, value pair of s1, for the convenience of comparision
        for index,node in enumerate(s1) :
            cmpidx[node] = index
        for node in s1 :
            outnodes = diG.successors(node)
            for onode in outnodes :
                if cmpidx[node] < cmpidx[onode] :
                    fset.append((node, onode))
        et_fas = time.time()
        print(et_fas-et_generate, 'find all left forward edges time length.')
        # sometimes the left forward edges is more than the right forward edges, so we should return the smallest set.
        # a lazy method
        diGcopy = diG.copy()
        if len(fset) > diGcopy.size()/2 :
            diGcopy.remove_edges_from(fset)
            return diGcopy.edges()
        else :
            return fset
    
    def _update(self,nodes) :
        for node in nodes :
            if self.nodeidx[node] is not None :                                                         # if the node has been removed, then skip it
                if self.bins[self.nodeidx[node]][node] - 1 is 0 :
                    self.sinks.append(node)
                    del self.bins[self.nodeidx[node]][node]
                    self.nodeidx[node] = None
                else :
                    self.bins[self.nodeidx[node]-1][node] = self.bins[self.nodeidx[node]][node] - 1     # else put it in the following bin whose binidx = od-1 
                    del self.bins[self.nodeidx[node]][node]                                             # remove the node from the original bin
                    self.nodeidx[node] = self.nodeidx[node] - 1                                         # update the value of nodeidx.
        while len(self.bins[self.maxidx]) <= 0 and self.maxidx > self.minidx:                           # update the value of maxidx
                self.maxidx = self.maxidx - 1

if __name__ == '__main__' :
    data = pd.read_table('/Users/xjd/Desktop/experiments/datasets/wiki-Vote.txt')
    G = nx.from_pandas_dataframe(data, 'Source', 'Target',create_using=nx.DiGraph())            
    msG = max(nx.weakly_connected_component_subgraphs(G), key=len)                              # find max weakly connected component subgraph in G
    tools = Tools()
    fas = tools.fas(msG)                                                                        # find fas
    msG.remove_edges_from(fas)                                                      
    print(len(fas),'the feedback arc set length.')
    print('The final graph is DAG ? ',nx.is_directed_acyclic_graph(msG))                        # verify the graph is a DAG or not, after excluding the fas
