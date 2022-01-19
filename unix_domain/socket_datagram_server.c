#include "unix_socket.h"

int main(void)
{
    int server_fd;
    struct sockaddr_un server_sockaddr;
    struct sockaddr_un client_sockaddr;
    int sock_len;
    char buf[BUFFSIZE];
    ssize_t bytes_cnt;
    int ret;

    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(&client_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(&buf, 0, BUFFSIZE);

    /* create unix domain socket */
    server_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(server_fd == -1){
        perror("SOCKET ERROR");
        goto fail;
    }

    /* setup server unix sockaddr */
    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SERVER_SOCK_PATH);
    sock_len = sizeof(server_sockaddr);
    unlink(SERVER_SOCK_PATH);
    ret = bind(server_fd, (struct sockaddr *)&server_sockaddr, sock_len);
    if(ret == -1){
        perror("bind error.");
        goto fail;
    }

    /* read data from client */
    for(;;){
        printf("waiting to recvdata ...\n");
        bytes_cnt = recvfrom(server_fd, buf, BUFFSIZE, 0, (struct sockaddr*)&client_sockaddr, (socklen_t *)&sock_len);
        if(bytes_cnt == -1){
            perror("recvfrom error");
            goto fail;
        }
        else{
            printf("received data: %s\n", buf);
        }
        ret = sendto(server_fd, buf, bytes_cnt, 0, (struct sockaddr *)&client_sockaddr, (socklen_t)sock_len);
        if (ret == -1) {
            perror("send fail");
            goto fail;
        }
    }

    close(server_fd);
    return 0;

fail:
    if(server_fd != -1)
        close(server_fd);
    return -1;
}
