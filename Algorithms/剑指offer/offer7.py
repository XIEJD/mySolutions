# 矩形覆盖(牛客网-剑指offer)
# 我们可以用2*1的小矩形横着或者竖着去覆盖更大的矩形。
# 请问用n个2*1的小矩形无重叠地覆盖一个2*n的大矩形，
# 总共有多少种方法？

def rect_cover(n):
    """
    又是斐波那契数列
    """
    if n < 0:
        return 'Fuck {}.'.format(n)
    return n if n <= 3 else rect_cover(n-1) + rect_cover(n-2)

if __name__ == '__main__':
    print(rect_cover(1))
    print(rect_cover(2))
    print(rect_cover(3))
    print(rect_cover(4))
    print(rect_cover(10))
