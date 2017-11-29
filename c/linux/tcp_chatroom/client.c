#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXBUF 1024//信息大小

int main(int argc, char **argv)
{
    int sockfd, len;
    struct sockaddr_in dest;
    char buffer[MAXBUF + 1];
    if (argc != 3)
    {
		printf(" error format,it must be:\n\t\t%s IP port\n",argv[0]);//输入出错
		exit(EXIT_FAILURE);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {//申请一个套接字		perror("Socket");
		exit(errno);
    }
    printf("socket created\n");


    bzero(&dest, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(atoi(argv[2]));
    if (inet_aton(argv[1], (struct in_addr *) &dest.sin_addr.s_addr) == 0)
    {
		perror(argv[1]);	exit(errno);
    }
    if (connect(sockfd, (struct sockaddr *) &dest, sizeof(dest))==-1)//建立连接
    {
		perror("Connect ");
		exit(errno);
    }
    printf("****************连接成功*********************\n");

	pid_t pid;
	if(-1==(pid=fork()))
	{
		perror("fork");exit(EXIT_FAILURE);
	}
	else if (pid==0)
	{
		while (1)
		{
			bzero(buffer, MAXBUF + 1);
			len = recv(sockfd, buffer, MAXBUF, 0);
			if (len > 0)
				printf("**********收到信息*****************:\n'%s'\n",buffer);
			else if(len < 0)
			{
				perror("recv");
				break;
			}
			else
			{
				printf("the other one close ,quit\n");
				break;
			}
		}
	}
	else
	{
		while (1)
		{
			bzero(buffer, MAXBUF + 1);
			printf("**********请输入发送的信息*****************:\n");
			fgets(buffer, MAXBUF, stdin);
			if (!strncasecmp(buffer, "quit", 4))
			{
				printf(" i will quit!\n");
				break;
			}
			len = send(sockfd, buffer, strlen(buffer) - 1, 0);
			if (len < 0)
			{
				perror("send");
				break;
			}
		}
	}
    close(sockfd);
    return 0;
}