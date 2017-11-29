#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXBUF 1024//最大信息容量

int main(int argc, char *argv[])
{
    int pid;//pid号
    int sockfd, new_fd;//定义socket描述符
    socklen_t len;//socket状态
    struct sockaddr_in my_addr, their_addr;//地址
    unsigned int myport, lisnum;
    char buf[MAXBUF + 1];

    if (argv[2])
		myport = atoi(argv[2]);//字符转数字
    else
		myport = 7575;//否则默认端口为7575

    if (argv[3])
		lisnum = atoi(argv[3]);//监听选项
	else
		lisnum = 5;//否则默认为5

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)//建立一个套接字连接
    {
		perror("socket");//出错
		exit(EXIT_FAILURE);
    }

    bzero(&my_addr, sizeof(my_addr));//清空
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(myport);
    if (argv[1])
		my_addr.sin_addr.s_addr = inet_addr(argv[1]);
    else
		my_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr))== -1)//绑定
    {
		perror("bind");
		exit(EXIT_FAILURE);
    }

    if (listen(sockfd,lisnum ) == -1)//监听
    {
		perror("listen");
		exit(EXIT_FAILURE);
    }
    printf("***************欢迎来到聊天室！****************\n");
    printf("*****************等待接入...****************\n");

    len = sizeof(struct sockaddr);
    if ((new_fd =accept(sockfd, (struct sockaddr *) &their_addr,&len)) == -1)//接收出错
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    else//否则建立成功
        printf("server: got connection from %s, port %d, socket %d\n",inet_ntoa(their_addr.sin_addr),ntohs(their_addr.sin_port), new_fd);

	if(-1==(pid=fork()))
	{
		perror("fork");exit(EXIT_FAILURE);
	}
	else if( pid == 0)
	{
		while (1)
		{
			bzero(buf, MAXBUF + 1);
			printf("**********请输入发送的信息*****************:\n");
			fgets(buf, MAXBUF, stdin);//输入信息以发送
			if (!strncasecmp(buf, "quit", 4))
			{
				printf("close the connect!\n");
				break;
			}
			len = send(new_fd, buf, strlen(buf) - 1, 0);//发送
	  		if (len < 0)
			 {
				printf("message'%s' send failure!errno code is %d,errno message is '%s'\n",
				buf, errno, strerror(errno));
				break;
			}
		}
	}
	else
	{
		while(1)
		{
			bzero(buf, MAXBUF + 1);
			len = recv(new_fd, buf, MAXBUF, 0);//接收信息
			if (len > 0)
				printf("**********收到信息*****************:\n'%s'\n",buf);
			else if (len < 0)
			{
				printf("recv failure!errno code is %d,errno message is '%s'\n",
				errno, strerror(errno));
				break;
			}
			else
			{
				printf("the other one close quit\n");
				break;
			}
		}
	}
	close(new_fd);//关闭连接
	close(sockfd);
    	return 0;
}