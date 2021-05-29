stream_server:
	gcc -o stream_server socket_stream_server.c

stream_client:
	gcc -o stream_client socket_stream_client.c 

all: stream_server stream_client

.PHYON: clean
clean:
	rm -f stream*