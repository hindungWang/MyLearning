#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8888/*端口*/

int main(int argc, char *argv[])
{
	int s;										/*socket描述符*/
	FILE *fp;
	struct sockaddr_in server_addr;			/*服务器地址结构*/
	size_t MAXLINE = 1024;/*最大长度*/
	char buf[1024]; 　　/*设置缓冲内存*/
	int read_len = -1;   /*写标志*/
	int send_len = -1;  /*发送标志*/
	bzero(buf, MAXLINE);/*清零*/
	s = socket(AF_INET, SOCK_STREAM, 0); 		/*建立一个流式套接字*/
	if(s < 0){									/*出错*/
		printf("socket error\n");
		return -1;
	}
	if (argc <= 2)/*格式错误*/
	{
        printf("Usage ./client + server_addr + filename to send file\n");
				exit(0);
	}
	fp = fopen(argv[2], "r");/*打开文件以读出*/
	if(fp == NULL)/*打开文件失败*/
	{
		perror("open file failed!\n");
		exit(0);
	}

	/*设置服务器地址*/
	bzero(&server_addr, sizeof(server_addr));	/*清零*/
	server_addr.sin_family = AF_INET;					/*协议族*/
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);	/*本地地址*/
	server_addr.sin_port = htons(PORT);				/*服务器端口*/

	/*将用户输入的字符串类型的IP地址转为整型*/
	inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
	connect(s, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));/*连接服务器*/
	bzero(buf, MAXLINE);/*清零*/

	read_len = fread(buf, sizeof(char), MAXLINE, fp);/*读文件*/
	while (read_len > 0 )//******
	{
		send_len = send(s, buf, read_len, 0);/*循环发送*/
		if ( send_len < 0 )/*出错*/
		{
			perror("Send file failed\n");
			exit(0);
		}
		bzero(buf, MAXLINE);/*清零*/
		read_len = fread(buf, sizeof(char), 1024, fp);/*继续读文件*/
	}
	fclose(fp);/*读完关闭文件*/
	printf("file send ok!\n");/*发送完*/
	close(s);						/*关闭socket链接*/
	return 0;
}