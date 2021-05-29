#include "unix_socket.h"

#define BACKLOG 5

int main(int argc, char *argv[])
{
    int server_fd, client_fd;
    struct sockaddr_un server_sockaddr;
    struct sockaddr_un client_sockaddr;
    char buf[BUFFSIZE];
    ssize_t num_read;
    int sock_len;
    int ret;

    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(&client_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(buf, 0, BUFFSIZE);

    /* create unix domain stream socket */
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(server_fd == -1){
        perror("socket");
        goto fail;
    }

    /*  set sockaddr and bind the file,
     * unlink file first for bind succeed */
    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SERVER_SOCK_PATH);
    sock_len = sizeof(server_sockaddr);
    unlink(SERVER_SOCK_PATH);
    ret = bind(server_fd, (struct sockaddr *)&server_sockaddr, sock_len);
    if(ret == -1){
        perror("bind");
        goto fail;
    }

    /* listen for client socket */
    ret = listen(server_fd, BACKLOG);
    if(ret == -1){
        perror("listen");
        goto fail;
    }

    /* accept client */
    for(;;){
        // sock_len need to be initilized, or accept will return invalid argument error
        client_fd = accept(server_fd, (struct sockaddr *)&client_sockaddr, (socklen_t *)&sock_len);     
        if(client_fd == -1){
            perror("accept");
            close(client_fd);
            goto fail;
        }

        /* get the name of the connected socket (if client bind to a sockpath) */
        sock_len = sizeof(client_sockaddr);
        ret = getpeername(client_fd, (struct sockaddr *)&client_sockaddr, (socklen_t *)&sock_len);
        if(ret){
            perror("getpeername");
            goto fail;
        }
        else{
            printf("client socket name: %s\n", client_sockaddr.sun_path);
        }

        /* receive data from client socket */
        while((num_read = read(client_fd, buf, BUFFSIZE)) > 0) {
            if(write(STDOUT_FILENO, buf, num_read) != num_read){
                printf("partial/failed write.\n");
                goto fail;
            }
        }

        if(num_read == -1){
            perror("read");
            goto fail;
        }

        if(close(client_fd) == -1){
            printf("close client fd %d fail.\n",client_fd);
        }
    }

    return 0;

fail:
    if(client_fd)
        close(client_fd);
    close(server_fd);
    return -1;
}

