#ifndef UNIX_SOCKET_H
#define UNIX_SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SERVER_SOCK_PATH "/tmp/server.sock"
#define CLIENT_SOCK_PATH "/tmp/client.sock"

#define BUFFSIZE    1024

#endif