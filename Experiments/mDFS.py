#-*- coding : UTF-8 -*-

import networkx as nx

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

def nonrecursive_modified_deep_first_search(G):
    '''
    This function is not recursive  which is different from real mDFS,
    this function is corresponds to Algorithm 2,
    actually, this function will never explore any edge twice,
    so when using construct strategy generate a placement order,
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

def recursive_modified_deep_first_search(G) :
    pass
