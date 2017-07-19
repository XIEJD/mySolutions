# 青蛙跳台阶(牛客网-剑指offer)
# 青蛙每次能跳1阶，或2阶
# 现有n个台阶，有多少种跳法

def jump_floor(number):
    """
    这实际上任然是一个依赖于前两项的数列
    如果需要计算第 n 个阶梯时可能的情况，
    有两种情况可以到达 第 n 个阶梯
        1. 一步从第n-1阶跳到第n阶
        2. 一步从第n-2阶跳到第n阶
    所以 f(n) = f(n-1) + f(n-2)
    """
    return number if number <= 2 else jump_floor(number-1) + jump_floor(number-2)

if __name__ == '__main__':
    print(jump_floor(10))
