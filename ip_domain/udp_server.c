/*
 * @Description: file content
 * @Author: hunterzju
 * @Date: 2022-01-16 19:46:02
 * @LastEditors: `${env:USERNAME}`
 * @LastEditTime: 2022-01-17 14:12:05
 * @FilePath: /linux_socket/ip_domain/udp_server.c
 */

#include "ip_socket.h"
#include <ctype.h>

int main(void)
{
    int server_fd;
    struct sockaddr_in  server_addr;
    struct sockaddr_in  client_addr;
    int len;
    ssize_t num_btyes, idx;
    char buf[BUFFSIZE];
    char cli_addr_str[INET_ADDRSTRLEN];

    // init socket fd
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(server_fd == -1) {
        perror("SOCKET ERROR");
        goto fail;
    }

    // init socket addr
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);

    // bind socket fd and addr
    if(bind(server_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in))) {
        perror("BIND SOCKET ERROR");
        goto fail;
    }

    // receive data
    for(;;) {
        len = sizeof(struct sockaddr_in);
        num_btyes = recvfrom(server_fd, buf, BUFFSIZE, 0, (struct sockaddr *)&client_addr, &len);

        if (num_btyes == -1) {
            perror("RECEIVE DATA FAIL");
            goto fail;
        }

        if (inet_ntop(AF_INET, &client_addr.sin_addr, cli_addr_str, INET_ADDRSTRLEN) == NULL){
            printf("Cloud't convert client address to string.\n");
        }
        else {
            printf("Server received %ld bytes from (%s, %u)\n",
                    (long)num_btyes, cli_addr_str, ntohs(client_addr.sin_port));
        }

        for(idx = 0; idx < num_btyes; idx++) {
            buf[idx] = toupper((unsigned char) buf[idx]);
        }

        if (sendto(server_fd, buf, num_btyes, 0, (struct sockaddr *) &client_addr, len) != num_btyes) {
            perror("SEND TO CLIENT ERROR");
            goto fail;
        }
    }

    return 0;

fail:
    if(server_fd != -1)
        close(server_fd);
    return -1;

}