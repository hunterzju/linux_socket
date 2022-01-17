CC := gcc
CFLAGS := -g

tcp_server:
	$(CC) $(CFLAGS) -o tcp_server tcp_server.c

tcp_client:
	$(CC) $(CFLAGS) -o tcp_client tcp_client.c 

udp_server:
	$(CC) $(CFLAGS) -o udp_server udp_server.c 

udp_client:
	$(CC) $(CFLAGS) -o udp_client udp_client.c 

all: tcp_server tcp_client udp_server udp_client

.PHYON: clean
clean:
	rm -f tcp_client tcp_server udp_client udp_server *.o