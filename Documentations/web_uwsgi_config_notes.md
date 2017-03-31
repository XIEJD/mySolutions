#uWSGI Configurations

> 今天配置django+uWSGI(无nginx)的时候，碰到了很多坑，总结一下。

1. 基本设置

    http-socket = 127.0.0.1:8000
    chdir       = /Users/xjd/Desktop/work_or_die/shareif
    wsgi-file   = shareif/wsgi.py
    processes   = 4
    threads     = 2
    stats       = 127.0.0.1:3031
    buffer-size = 65536

其中注意`http-socket`这个是你的网页入口，不是`stats`(这个在运行uWSGI时，终端会显示这个地址，别把它当入口！)

2. 静态文件
    
    #添加属性 
    static-map  = /static=/Users/xjd/Desktop/work_or_die/shareif/static

注意第二个等号两边不能有空格，否则无效！！
