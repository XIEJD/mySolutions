#-*- coding : UTF-8 -*-

'''
    构建算法，从有相无环图构建一种搜索策略

    References:
        [1] - Simpson, Michael, Venkatesh Srinivasan, and Alex Thomo.
                "Clearing contamination in large networks."
                IEEE Transactions on Knowledge and Data Engineering 28.6 (2016): 1435-1448.
    Authour:
        ExcitedX

    Date:
        08/02/2017

'''
import networkx as nx
import pandas as pd
#from operator import itemgetter
from networkx.algorithms import approximation as approx
import time


scc = list()
stack = list()
DFN = dict() #存放节点的遍历顺序
Low = dict() #存放最远可回溯节点的DFN
TimeStamp = 0
#call tarjan algorithm
def tarjan(node_s):
    '''
    tarjan(node_s, scc)

    Parameters:
        node_s - this is a node at which an edge start
        scc    - set consists of sccs and its elements are tuples or lists consist of nodes' id.

    Returns:
        scc, the strongly connected component set.

    '''
    global TimeStamp
    stack.append(node_s)
    index = TimeStamp + 1
    TimeStamp = TimeStamp + 1
    DFN[node_s] = index
    Low[node_s] = index
    for node_e in G.successors_iter(node_s):
        if node_e not in DFN.keys(): #nodes_e不在DFN的keys列表中，代表nodes_e没有被访问过
            tarjan(node_e)
            Low[node_s] = min(Low[node_s], Low[node_e])
        elif node_e in stack and DFN[node_e] < DFN[node_s]:
            Low[node_s] = DFN[node_e]
    if DFN[node_s] == Low[node_s]: # 如果当前节点只能回溯到自己
        _scc = list()
        while 1:
            node = stack.pop()
            _scc.append(node)
            if node_s == node:
                break
        scc.append(_scc)

def hasUnexploredIncomingEdges(G, stack_edges, node) :
    '''
    判断node是否有不在stack_edges中的入边

    Parameters :
        G - DAG or DAGs
        stack_edges - list, edges has been explored.
        node - current node

    Return :
        True, if has unexplored incoming edges.
        False, if has no unexplored incoming edges.
    '''
    for in_edge in G.in_edges(node) :
        if in_edge not in stack_edges :
            return True
    return False

def mDFSO(G):
    '''
    This function is not recursive  which is different from real mDFS,
    this function is corresponds to Algorithm 2,
    actually, this function will never explore any edge twice,
    so when using construct strategy generate an placement order,
    it is naturally an optimized construct strategy.

    Parameters:
        G - a DAG or many DAGs

    Return:
        stack_edges - list, an edges order explored by DFS algorithm.
    '''
    stack_nodes = list()
    stack_edges = list()
    out_nodes = dict()
    nodes_visited = set()
    for node in G.nodes():
        if G.in_edges(node) :
            continue
        stack_nodes.append(node)
        while stack_nodes :
            current_node = stack_nodes[-1]
            if current_node not in nodes_visited :
                #如果存在感染的入边，则强制终止这条路径的搜索
                if hasUnexploredIncomingEdges(G, stack_edges, current_node) :
                    stack_nodes.pop()
                    continue
                nodes_visited.add(current_node)
                out_nodes[current_node] = G.successors_iter(current_node)
                try :
                    next_node = next(out_nodes[current_node])
                    if next_node not in stack_nodes :
                        stack_nodes.append(next_node)
                    stack_edges.append((current_node, next_node))
                except StopIteration :
                    stack_nodes.pop()
            else :
                try :
                    next_node = next(out_nodes[current_node])
                    if next_node not in stack_nodes :
                        stack_nodes.append(next_node)
                    stack_edges.append((current_node, next_node))
                except StopIteration :
                    stack_nodes.pop()
    return stack_edges

def imDFSO(G):
    '''
    this is improved mDFSO algorithm
    this function can process directed graph which consists of cycles
    and then break cycles, this function convert a directed graph into
    a directed acyclic graph and return edges order explored by DFS algorithm

    Parameters:
        G - a directed graph or many directed graphs

    Return:
        stack_edges - list, an edges order explored by DFS algorithm.
        stack_backward_edges - list, all backward edges in DFS tree.
    '''
    stack_nodes = list()
    stack_edges = list()
    stack_backward_edges = list()
    out_nodes = dict()
    nodes_visited = set()
    for index,node in enumerate(G.nodes()) :
        stack_nodes.append(node)
        while stack_nodes :
            current_node = stack_nodes[-1]
            if current_node not in nodes_visited :
                #如果存在感染的入边，则强制终止这条路径的搜索
                #if hasUnexploredIncomingEdges(G, stack_edges + stack_backward_edges, current_node) :
                #    stack_nodes.pop()
                #    continue
                nodes_visited.add(current_node)
                out_nodes[current_node] = G.successors_iter(current_node)
                try :
                    next_node = next(out_nodes[current_node])
                    if next_node not in stack_nodes :
                        stack_nodes.append(next_node)
                        stack_edges.append((current_node, next_node))
                    else :
                        stack_backward_edges.append((current_node, next_node))
                except StopIteration :
                    stack_nodes.pop()
            else :
                try :
                    next_node = next(out_nodes[current_node])
                    if next_node not in stack_nodes :
                        stack_nodes.append(next_node)
                        stack_edges.append((current_node, next_node))
                    else :
                        stack_backward_edges.append((current_node, next_node))
                except StopIteration :
                    stack_nodes.pop()
    return stack_edges, stack_backward_edges


def construct(edges, s) :
    '''
    This function corresponds to the Algorithm 3.

    Parameters :
        G - DAG or DAGs
        edges - an edges order explored by mDFS algorithms.
        s - number of searchers.

    Return :
        sigma - Multi-D list, a search strategy sigma = (V1,V2,V3,...,Vt), V is a set consist of s nodes.
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

#PROCEDURES
#Graph
G = nx.DiGraph()
#G.add_nodes_from(['a','b','c','d','e','f'])
#G.add_edges_from([('a','b'),('e','a'),('a','d'),('b','c'),('c','f'),('b','e'),('d','e'),('e','f')])

data = pd.read_table('/Users/xjd/Desktop/experiments/datasets/epinions.txt')
G = nx.from_pandas_dataframe(data, 'Source', 'Target',create_using=nx.DiGraph())
msG = max(nx.weakly_connected_component_subgraphs(G), key=len)  #从G中找出最大弱连通图
#print('最大弱连通图边数',len(msG.edges()))
#scc_gen = nx.strongly_connected_components(G)
#scc_list = list()
#for scc in scc_gen :
#    if (len(scc) > 1) :
#        scc_list.append(scc)
#sccG = msG.subgraph(scc_list[0])
##去边清环
#fas = list()
#while not nx.is_directed_acyclic_graph(sccG):
#    _fas = list()
#    sccs_gen = nx.strongly_connected_component_subgraphs(sccG)
#    for scc in sccs_gen :
#        if len(scc.nodes()) > 1 :
#            print('size of scc',len(scc.nodes()))
#            while 1 :
#                try :
#                    arc = nx.find_cycle(scc)
#                    scc.remove_edge(*arc[0])
#                    fas.append(arc[0])
#                except :
#                    break
#    fas.extend(_fas)
#    sccG.remove_edges_from(_fas)
#    print(len(_fas))

#_, cyc_edges = imDFSO(G)
#G.remove_edges_from(cyc_edges)
#print(nx.is_directed_acyclic_graph(G))
#print(connectivity(G))
#nx.draw_networkx(G, pos=nx.shell_layout(G))
#plt.show()

fas = fas(msG)
print('fas length : ',len(fas))
msG.remove_edges_from(fas)
print('number of the rest edges',len(msG.edges()))
print('The final graph is DAG ? ',nx.is_directed_acyclic_graph(msG))



