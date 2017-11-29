all:client server					#all规则，它依赖于client和server规则

client:tcp_network_process.o tcp_network_client.o	#client规则，生成客户端可执行程序
	gcc -o client tcp_network_process.o tcp_network_client.o
server:tcp_network_process.o tcp_network_server.o	#server规则，生成服务器端可执行程序
	gcc -o server tcp_network_process.o tcp_network_server.o	
tcp_process.o:						#tcp_process.o规则，生成tcp_process.o
	gcc -c tcp_network_process.c -o tcp_network_process.o
clean:								#清理规则，删除client、server和中间文件
	rm -f client server *.o
