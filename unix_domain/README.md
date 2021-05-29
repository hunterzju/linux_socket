# Unix Domain Socket通信
包含了Unix Domain下stream和datagram两种通信方式代码示例：
## Stream socket
server端：unix_domain/socket_stream_client.c
client端：unix_domain/socket_stream_server.c
测试：
```bash
make clean; make all
./stream_server             # 开启服务端监听
./stream_client < test.txt  # 客户端连接，并将test.txt中内容重定向到stdin发送给服务端
```
### 注意：
1. server端`accept()`函数和client端`connect()`函数中`len`参数需要初始化，否则在会出现Invalid argument error；
2. client端是否bind到sockaddr不影响和server端通信；

## Datagram socket



## Todolist
[] socket通信中各种读写接口补充，比如`read()`,`write()`,`sendmsg()`,`recvmsg()`等；
[] client是否bind到sockaddr的区别？
[] stream方式中len参数必须初始化原因？