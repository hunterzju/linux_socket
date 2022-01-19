#include "unix_socket.h"

#define TEST_DATA   "Hello world! --from client.\n"

int main(void)
{
    int client_fd;
    struct sockaddr_un server_sockaddr;
    struct sockaddr_un client_sockaddr;
    char buf[BUFFSIZE];
    int ret;
    int sock_len, num_bytes;

    memset(&server_sockaddr, 0, sizeof(server_sockaddr));
    memset(&client_sockaddr, 0, sizeof(client_sockaddr));
    memset(&buf, 0, BUFFSIZE);

    /* create datagram socket fd */
    client_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(client_fd == -1){
        perror("SOCKET ERROR");
        goto fail;
    }

    /* setup client unix sockaddr */
    client_sockaddr.sun_family = AF_UNIX;
    strcpy(client_sockaddr.sun_path, CLIENT_SOCK_PATH);
    if (bind(client_fd, (struct sockaddr *)&client_sockaddr, sizeof(client_sockaddr)) == -1) {
        perror("BIND SOCKET FAIL");
        goto fail;
    }

    /* setup server unix sockaddr */
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
    sock_len = sizeof(struct sockaddr_un);
    num_bytes = recvfrom(client_fd, buf, sizeof(TEST_DATA), 0, (struct sockaddr *)&server_sockaddr, &sock_len);
    if (num_bytes <= 0) {
        perror("REVEIVE FAIL");
        goto fail;
    }
    else{
        printf("Receive data: %s\n", buf);
    }


    /* close socket and exit */
    close(client_fd);
    return 0;

fail:
    if(client_fd != -1)
        close(client_fd);
    return -1;
}