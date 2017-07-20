# 斐波那契数列(牛客网-剑指offer)
# 输出斐波那契数列的第n项

def fibo(n):
    return n if n <= 1 else fibo(n-2) + fibo(n-1)

if __name__ == '__main__':
    print(fibo(0))
    print(fibo(1))
    print(fibo(2))
    print(fibo(10))
