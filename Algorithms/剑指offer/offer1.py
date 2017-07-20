# 重建二叉树(牛客网-剑指offer)
# 前序遍历结果：1 2 4 7 3 5 6 8
# 中序遍历结果：4 7 2 1 5 3 8 6
# 根据上面结果，重建二叉树

class Node:
    def __init__(self, value, left_child, right_child):
        self.value = value
        self.left_child = left_child
        self.right_child = right_child


PRE = [1,2,4,7,3,5,6,8]
MID = [4,7,2,1,5,3,8,6]


def reconstruct(pre, mid):
    # 当前根
    value   = pre.pop(0)
    left    = None
    right   = None

    if len(mid):
        mid_index       = mid.index(value)
        left_children   = mid[:mid_index]
        right_children  = mid[mid_index+1:]
        if len(left_children):
            left = reconstruct(pre[:mid_index], left_children)

        if len(right_children):
            right = reconstruct(pre[mid_index:], right_children)
    
    if value is not None:
        return Node(value, left, right) 


def pre_traverse(node):
    if node is None:
        return 
    print(node.value)
    pre_traverse(node.left_child)
    pre_traverse(node.right_child)


def mid_traverse(node):
    if node is None:
        return 
    mid_traverse(node.left_child)
    print(node.value)
    mid_traverse(node.right_child)


def post_traverse(node):
    if node is None:
        return 
    post_traverse(node.left_child)
    post_traverse(node.right_child)
    print(node.value)

if __name__ == '__main__':
    root = reconstruct(PRE, MID)
    print('前序遍历')
    pre_traverse(root)
    print('中序遍历')
    mid_traverse(root)
    print('后序遍历')
    post_traverse(root)


