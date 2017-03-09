import numpy as np

rounds = 10000000
u1 = u2 = 0
sigma1 = sigma2 = 1 #标准正态分布
x = np.random.randn(1,rounds)[0]
y = np.random.randn(1,rounds)[0]
count = 0

def fun(x,y) :
    return (x**2+y**2-1)**3 - (x**2)*(y**2)
# 随机产生大量标准正态分布数，测试是否(x^2 + y^2 -1)^3 - x^2 x y^2 <= 0
for i in range(0,rounds) :
    if fun(x[i],y[i]) <= 0 :
        count = count + 1

print(count/rounds)





