#include "unix_socket.h"

int main(int argc, char *argv[])
{
    int client_fd;
    struct sockaddr_un client_sockaddr;
    struct sockaddr_un server_sockaddr;
    ssize_t num_read;
    char buf[BUFFSIZE];
    int ret, sock_len;

    memset(&client_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(buf, 0, BUFFSIZE);

    /* create unix domain stream socket for client */
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(client_fd == -1){
        perror("socket");
        goto fail;
    }

    /*  set client sockaddr and bind the file (not necessary),
     * unlink file first for bind succeed */
    // client_sockaddr.sun_family = AF_UNIX;
    // strcpy(client_sockaddr.sun_path, CLIENT_SOCK_PATH);
    sock_len = sizeof(client_sockaddr);
    // unlink(CLIENT_SOCK_PATH);
    // ret = bind(client_fd, (struct sockaddr *)&client_sockaddr, sock_len);
    // if(ret == -1){
    //     perror("bind");
    //     goto fail;
    // }

    /* set server sockaddr and connect to it */
    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SERVER_SOCK_PATH);
    ret = connect(client_fd, (struct sockaddr *)&server_sockaddr, sock_len);
    if(ret == -1){
        perror("connect");
        goto fail;
    }

    /* send data from stdin using read() */
    while((num_read = read(STDIN_FILENO, buf, BUFFSIZE)) > 0){
        if(write(client_fd, buf, num_read) != num_read){
            printf("partial/failed write.\n");
        }
    }

    if(num_read == -1){
        perror("read");
        goto fail;
    }

    return 0;

fail:
    return -1;
}