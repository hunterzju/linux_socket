#include "unix_socket.h"

#define TEST_DATA   "Hello world! --from client.\n"

int main(void)
{
    int client_fd;
    struct sockaddr_un server_sockaddr;
    char buf[BUFFSIZE];
    int ret;

    memset(&server_sockaddr, 0, sizeof(server_sockaddr));
    memset(&buf, 0, BUFFSIZE);

    /* create datagram socket fd */
    client_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(client_fd == -1){
        perror("SOCKET ERROR");
        goto fail;
    }

    /*setup unix sockaddr */
    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SERVER_SOCK_PATH);
    
    /* copy data to buf and send to server */
    strcpy(buf, TEST_DATA);
    printf("send data to server:%s.\n", buf);
    ret = sendto(client_fd, buf, strlen(buf), 0, (struct sockaddr*)&server_sockaddr, sizeof(server_sockaddr));
    if(ret == -1){
        perror("SENDTO ERROR");
        goto fail;
    }
    else{
        printf("Send data OK.\n");
    }

    /* close socket and exit */
    close(client_fd);
    return 0;

fail:
    if(client_fd != -1)
        close(client_fd);
    return -1;
}