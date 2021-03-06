/*
 * @Description: ip socket domain example header file.
 * @Author: hunterzju
 * @Date: 2022-01-16 20:00:07
 * @LastEditors: `${env:USERNAME}`
 * @LastEditTime: 2022-01-17 22:18:08
 * @FilePath: /linux_socket/ip_domain/ip_socket.h
 */

#ifndef IP_SOCKET_H_
#define IP_SOCKET_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>

#define BUFFSIZE    128

#define SERVER_PORT 50001

#define BACKLOG     5

#endif