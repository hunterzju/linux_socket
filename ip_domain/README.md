# IP Domain Socket通信
包含了IP Domain下stream和datagram两种通信方式代码示例：
## [TODO]Stream socket(TCP)
server端：ip_domain/tcp_client.c
client端：unix_domain/tcp_server.c
测试：
```bash
make clean; make all
./tcp_server                  # 开启服务端监听
./tcp_client 127.0.0.1 hello  # 客户端连接，并将test.txt中内容重定向到stdin发送给服务端
```
### 注意：
1. server端`accept()`函数和client端`connect()`函数中`len`参数需要初始化，否则在会出现Invalid argument error；
2. client端是否bind到sockaddr不影响和server端通信；

## Datagram socket(UDP)
server端：ip_domain/udp_server.c
client端：ip_domain/udp_client.c
测试：
```bash
make clean; make all
./udp_server                    # 开启服务端监听
./udp_client 127.0.0.1 hello    # 客户端连接，并发送测试数据
```


## Todolist
- [*] 补充TCP连接例程；
- [] socket通信中各种读写接口补充，比如`read()`,`write()`,`sendmsg()`,`recvmsg()`等；
- [] socket()创建的`fd`，`sockaddr`的作用，以及`bind()`的作用梳理；
