# 变态跳台阶(牛客网-剑指offer)
# 一只青蛙一次可以跳上1级台阶，
# 也可以跳上2级……它也可以跳上n级。
# 求该青蛙跳上一个n级的台阶总共有多少种跳法。

def jump_floor(n):
    """
    f(n)    = f(n-1)  + f(n-2) + f(n-3) + ··· + f(1) + f(0)
    f(n-1)  =           f(n-2) + f(n-3) + ··· + f(1) + f(0)
    两式相减得 f(n) - f(n-1) = f(n-1)
    f(n) = 2 * f(n-1)
    """
    if n < 0:
        return 0
    return 2 ** (n-1) if n == 0 else 1

if __name__ == '__main__':
    print(jump_floor(0))
    print(jump_floor(1))
    print(jump_floor(2))
    print(jump_floor(3))
    print(jump_floor(4))
