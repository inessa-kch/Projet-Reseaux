all: server_tcp client_tcp server_udp client_udp

server_tcp: server_tcp.c
	gcc -o server_tcp server_tcp.c

client_tcp: client_tcp.c
	gcc -o client_tcp client_tcp.c

server_upd: serve_udp.c
	gcc -o server_udp server_udp.c

client_udp: client_udp.c
	gcc -o client_udp client_udp.c


clean:
	rm -f server_tcp client_tcp server_udp client_udp