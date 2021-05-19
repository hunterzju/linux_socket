#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "unix_socket.h"

int main(int argc, char *argv[])
{
    int ret;
    struct sockaddr_un addr;
    int sfd;
    ssize_t num_read;
    char buf[BUFFSIZE];

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sfd == -1){
        perror("socket");
        goto errout;
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path)-1);

    if(connect(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1){
        perror("connect");
        goto errout;
    }

    while((num_read == read(stdin, buf, BUFFSIZE)) > 0){
        if(write(sfd, buf, num_read) != num_read){
            printf("partial/failed write.\n");
        }
    }

    if(num_read == -1){
        perror("read");
        goto errout;
    }

    return 0;

errout:
    return -1;
}