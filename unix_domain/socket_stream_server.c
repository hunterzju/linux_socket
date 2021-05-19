#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "unix_socket.h"

#define BACKLOG 5

int main(int argc, char *argv[])
{
    int ret=0;
    int sfd, cfd;
    struct sockaddr_un addr;
    char buf[BUFFSIZE];
    ssize_t num_read;

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sfd == -1){
        perror("socket");
        goto errout;
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    if(bind(sfd, (struct sockaddr_un *)&addr, sizeof(struct sockaddr_un)) == -1){
        perror("bind");
        goto errout;
    }

    if(listen(sfd, BACKLOG) == -1){
        perror("listen");
        goto errout;
    }

    for(;;){
        cfd = accept(sfd, NULL, NULL);
        if(cfd == -1){
            perror("accept");
            goto errout;
        }

        while((num_read = read(cfd, buf, BUFFSIZE)) > 0) {
            if(write(stdout, buf, num_read) != num_read){
                printf("partial/failed write.\n");
                goto errout;
            }
        }

        if(num_read == -1){
            perror("read");
            goto errout;
        }

        if(close(cfd) == -1){
            printf("close client fd %d fail.\n",cfd);
        }
    }

    return 0;

errout:
    return -1;
}

