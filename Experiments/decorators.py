# -*- coding : UTF-8 -*-

import time
from functools import wraps

def timer(func) :
    @wraps(func)
    def _wrapped_func(*args, **kw) :
        start = time.time()
        func(*args, **kw)
        end = time.time()
        print('运行时间：', func.__name__, end - start)
    return _wrapped_func

@timer
def func() :
    pass

if __name__ == '__main__' :
    func()
