all: server_tcp client_tcp server_udp client_udp

tcp: server_tcp client_tcp

udp: server_udp client_udp

server_tcp: TCP/server_tcp.c
	gcc -o server_tcp TCP/server_tcp.c

client_tcp: TCP/client_tcp.c
	gcc -o client_tcp TCP/client_tcp.c

server_udp: UDP/server_udp.c
	gcc -o server_udp UDP/server_udp.c

client_udp: UDP/client_udp.c
	gcc -o client_udp UDP/client_udp.c


clean:
	rm -f server_tcp client_tcp server_udp client_udp