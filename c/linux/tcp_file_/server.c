#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8888						/*发送、监听的端口*/
#define BACKLOG 2						/*设置队列长度*/

int main(int argc, char *argv[])
{
	int ss,sc;		/*ss为服务器的socket描述符，sc为客户端的socket描述符*/
	struct sockaddr_in server_addr;	/*服务器地址结构*/
	struct sockaddr_in client_addr;	/*客户端地址结构*/
	int err;							/*返回值*/
	FILE *fp;					/*文件指针*/
	int MAXLINE = 1024;			/*最大buf长度*/
	char buf[1024];							/*设置缓冲内存*/
	int recv_len = -1;　　　　　/*接收标志*/
	int write_len = -1;				/*写标志*/
	bzero(buf, MAXLINE);

	/*建立一个流式套接字*/
	ss = socket(AF_INET, SOCK_STREAM, 0);
	if(ss < 0){							/*出错*/
		printf("socket error\n");
		return -1;
	}
	if (argc <= 1)/*格式错误*/
	{
        printf("Usage ./server + filename to receave file\n");
				exit(0);
	}

	if((fp = fopen(argv[1], "w")) == NULL)/*打开文件*/
	{
		perror("Create file failed!\n");
		exit(0);
	}
	/*设置服务器地址*/
	bzero(&server_addr, sizeof(server_addr));			/*清零*/
	server_addr.sin_family = AF_INET;					/*协议族*/
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);	/*本地地址*/
	server_addr.sin_port = htons(PORT);				/*服务器端口*/

	/*绑定地址结构到套接字描述符*/
	err = bind(ss, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(err < 0)
	{			/*出错*/
		printf("bind error\n");
		return -1;
	}

	/*设置侦听*/
	err = listen(ss, BACKLOG);
	if(err < 0)
	{							/*出错*/
		printf("listen error\n");
		return -1;
	}

		/*接收文件*/
		socklen_t addrlen = sizeof(struct sockaddr);

		sc = accept(ss, (struct sockaddr*)&client_addr, &addrlen);
		/*接收客户端连接*/
		if(sc < 0)
		{							/*出错*/
			printf("Accept socket failed\n");
			exit(0);
		}
		while (recv_len = recv(sc, buf, MAXLINE, 0))/*接收来自client的数据*/
		{
			if(recv_len < 0)/*出错*/
			{
				printf("Recieve Data From Server Failed!\n");
				break;
			}
			printf("#");
			write_len = fwrite(buf, sizeof(char), recv_len, fp);/*写入本地*/
			if (write_len < recv_len)/*出错*/
			{
				printf("Write file failed\n");
				break;
			}
			bzero(buf,MAXLINE);/*清零*/
		}
		printf("\nFinish Recieve\n");/*传输完成*/
		fclose(fp);/*关闭文件*/
		close(sc);/*关闭链接*/
		close(ss);/*关闭socket链接*/
		return 0;
}