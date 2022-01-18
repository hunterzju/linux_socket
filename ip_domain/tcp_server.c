/*
 * @Description: file content
 * @Author: hunterzju
 * @Date: 2022-01-16 19:46:16
 * @LastEditors: `${env:USERNAME}`
 * @LastEditTime: 2022-01-17 22:27:15
 * @FilePath: /linux_socket/ip_domain/tcp_server.c
 */
#include "ip_socket.h"

int main(void) 
{
    int server_fd, client_fd;
    struct sockaddr_in  server_addr;
    struct sockaddr_in  client_addr;
    int sock_len, ret;
    ssize_t num_bytes, idx;
    char buf[BUFFSIZE];
    char cli_addr_str[INET_ADDRSTRLEN];

    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    memset(buf, 0, BUFFSIZE);

    // init socket fd
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == -1) {
        perror("CREATE FD FAIL");
        goto fail;
    }

    // init socket addr
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);
    
    // bind addr to fd
    sock_len = sizeof(struct sockaddr_in);
    ret = bind(server_fd, (struct sockaddr *)&server_addr, sock_len);
    if (ret == -1) {
        perror("BIND FAIL");
        goto fail;
    }

    // listen for client socket
    ret = listen(server_fd, BACKLOG);
    if (ret == -1) {
        perror("LISTEN FAIL");
        goto fail;
    }

    // accept and receive data
    sock_len = sizeof(struct sockaddr_in);
    for (;;) {
        // accept
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &sock_len);
        if (client_fd == -1) {
            perror("ACCEPT FAIL");
            goto fail;
        }
        // receive data
        while ((num_bytes = read(client_fd, buf, BUFFSIZE)) > 0) {
            if (write(STDOUT_FILENO, buf, num_bytes) != num_bytes) {
                printf("partial/failed write.\n");
                goto fail;
            }
        }

        if (num_bytes == -1) {
            perror("READ FAIL");
            goto fail;
        }

        if (close(client_fd) == -1) {
            printf("close client fd %d fail.\n", client_fd);
        }
    }

    return 0;

fail:
    if (client_fd)
        close(client_fd);
    close(server_fd);
}