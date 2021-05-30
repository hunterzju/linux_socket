CC := gcc
CFLAGS := -g

stream_server:
	$(CC) $(CFLAGS) -o stream_server socket_stream_server.c

stream_client:
	$(CC) $(CFLAGS) -o stream_client socket_stream_client.c 

datagram_server:
	$(CC) $(CFLAGS) -o datagram_server socket_datagram_server.c 

datagram_client:
	$(CC) $(CFLAGS) -o datagram_client socket_datagram_client.c 

all: stream_server stream_client datagram_server datagram_client

.PHYON: clean
clean:
	rm -f stream* datagram*