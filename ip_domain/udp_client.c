/*
 * @Description: file content
 * @Author: hunterzju
 * @Date: 2022-01-16 19:45:55
 * @LastEditors: `${env:USERNAME}`
 * @LastEditTime: 2022-01-17 14:39:31
 * @FilePath: /linux_socket/ip_domain/udp_client.c
 */

#include "ip_socket.h"

int main(int argc, char *argv[])
{
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int server_fd;
    int addr_len;
    size_t msg_len;
    ssize_t num_bytes, idx;
    char resp_buf[BUFFSIZE];

    if (argc < 3 || strcmp(argv[1], "--help") == 0) {
        printf("%s host-address msg\n", argv[0]);
    }

    // init client socket
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd == -1) {
        perror("CLIENT CREATE SOCKET FAIL");
        goto fail;
    }

    // init server_addr
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        perror("INET_PTON FAIL");
        goto fail;
    }

    addr_len = sizeof(struct sockaddr_in);
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    // send and receive data
    for (idx = 2; idx < argc; idx++) {
        msg_len = strlen(argv[idx]);
        if (sendto(server_fd, argv[idx], msg_len, 0, (struct sockaddr *)&server_addr,
            sizeof(struct sockaddr_in)) != msg_len) {
            perror("SEND FAIL");
            goto fail;
        }

        num_bytes = recvfrom(server_fd, resp_buf, BUFFSIZE, 0, (struct sockaddr *)&server_addr, &addr_len);
        if(num_bytes == -1) {
            perror("RECEIVE ERROR");
            goto fail;
        }
        printf("Response to port %d - data %d: %.*s\n",
                server_addr.sin_port, idx-1, (int)num_bytes, resp_buf);
    }

    return 0;

fail:
    if (server_fd != -1)
        close(server_fd);
    return -1;
}