## QMuduo
### 模型
* 基于reactor模型，使用tcpconnection类进行连接管理
* 一个线程里面放入一个loop 并且使用一个主loop进行accpet
* 其他的loop负责管理各个socket的连接读写
* 使用Buffer来进行消息的读入和写出，并通过readFd和writeFd与系统函数进行连接（因为系统的读写速率不够 所以使用buffer进行缓存）
* logger模仿log4j进行书写 
* 使用config类可以对日志进行配置 通过yaml文件进行配置 
* 对thread进行封装，分别封装了原始的pthread以及c++11thread 和一些常用的锁
* 使用单例对线程池进行管理
* 封装httpserver以及echoserver
### 使用
    sh muduo_build.sh
    ./bin/muduo_test (回显：新开一个端口： telnet ip 端口 进行检验)
    ./bin/http_test
    ./bin/config_test (配置类的使用方法可以看test如何使用)
### 依赖
* yaml-cpp库（config使用）

### 测压
    ab -n 10000 -c 1000 http://192.168.3.156:4000/