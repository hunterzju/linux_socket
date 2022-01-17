# Linux socket编程c示例代码
在linux中socket是一种进程间通信（IPC）方式，将数据在不同应用间交换。
linux中socket通信根据通信域（communication domain）可以分为三种：
* Unix domain: 同一主机内部进程间通信;
* IP domain：基于IPv4的跨主机进程间通信;

每个通信域下都有两种不同类型的socket：
* stream socket：面向连接的、可靠的、双向的字节流传输方式;
* datagram socket：datagram类型是无连接的、非可靠的报文传输方式。

[TODO]socket通信发送接收api：
* sendto()/recvfrom()
* send()/recv()
* sendmsg()/recvmsg()

