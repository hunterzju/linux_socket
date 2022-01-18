/*
 * @Description: file content
 * @Author: hunterzju
 * @Date: 2022-01-16 19:46:10
 * @LastEditors: `${env:USERNAME}`
 * @LastEditTime: 2022-01-18 09:10:47
 * @FilePath: /linux_socket/ip_domain/tcp_client.c
 */
#include "ip_socket.h"

int main(int argc, char* argv[])
{
    int client_fd;
    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;
    ssize_t num_read, idx;
    char buf[BUFFSIZE];
    int ret, sock_len;

    sock_len = sizeof(struct sockaddr_in);
    memset(&client_addr, 0, sock_len);
    memset(&server_addr, 0, sock_len);
    memset(buf, 0, BUFFSIZE);

    // init fd for tcp(ip stream socket)
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("CREATE SOCKET FD FAIL");
        goto fail;
    }

    // init socket address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    ret = connect(client_fd, (struct sockaddr *)&server_addr, sock_len);
    if (ret == -1) {
        perror("connect");
        goto fail;
    }

    // send data from stdin using read()
    while((num_read = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if (write(client_fd, buf, num_read) != num_read) {
            printf("partial write failed\n");
        }
    }

    if (num_read == -1) {
        perror("READ FAIL");
        goto fail;
    }

    return 0;

fail:
    if (client_fd)
        close(client_fd);
    return -1;
}