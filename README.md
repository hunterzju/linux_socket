# Linux socket编程c示例代码
在linux中socket是一种进程间通信（IPC）方式，将数据在不同应用间交换。
linux中socket通信根据通信域（communication domain）可以分为三种：
* Unix domain: 同一主机内部进程间通信;
* IPv4 domain：基于IPv4的跨主机进程间通信;
* IPv6 domain：基于IPv6的跨主机进程间通信。

每个通信域下都有两种不同类型的socket：
* stream socket：面向连接的可靠双向传输;
* datagram socket：无连接的非可靠传输。

