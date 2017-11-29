#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8888						/*���͡������Ķ˿�*/
#define BACKLOG 2						/*���ö��г���*/

int main(int argc, char *argv[])
{
	int ss,sc;		/*ssΪ��������socket��������scΪ�ͻ��˵�socket������*/
	struct sockaddr_in server_addr;	/*��������ַ�ṹ*/
	struct sockaddr_in client_addr;	/*�ͻ��˵�ַ�ṹ*/
	int err;							/*����ֵ*/
	FILE *fp;					/*�ļ�ָ��*/
	int MAXLINE = 1024;			/*���buf����*/
	char buf[1024];							/*���û����ڴ�*/
	int recv_len = -1;����������/*���ձ�־*/
	int write_len = -1;				/*д��־*/
	bzero(buf, MAXLINE);

	/*����һ����ʽ�׽���*/
	ss = socket(AF_INET, SOCK_STREAM, 0);
	if(ss < 0){							/*����*/
		printf("socket error\n");
		return -1;
	}
	if (argc <= 1)/*��ʽ����*/
	{
        printf("Usage ./server + filename to receave file\n");
				exit(0);
	}

	if((fp = fopen(argv[1], "w")) == NULL)/*���ļ�*/
	{
		perror("Create file failed!\n");
		exit(0);
	}
	/*���÷�������ַ*/
	bzero(&server_addr, sizeof(server_addr));			/*����*/
	server_addr.sin_family = AF_INET;					/*Э����*/
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);	/*���ص�ַ*/
	server_addr.sin_port = htons(PORT);				/*�������˿�*/

	/*�󶨵�ַ�ṹ���׽���������*/
	err = bind(ss, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(err < 0)
	{			/*����*/
		printf("bind error\n");
		return -1;
	}

	/*��������*/
	err = listen(ss, BACKLOG);
	if(err < 0)
	{							/*����*/
		printf("listen error\n");
		return -1;
	}

		/*�����ļ�*/
		socklen_t addrlen = sizeof(struct sockaddr);

		sc = accept(ss, (struct sockaddr*)&client_addr, &addrlen);
		/*���տͻ�������*/
		if(sc < 0)
		{							/*����*/
			printf("Accept socket failed\n");
			exit(0);
		}
		while (recv_len = recv(sc, buf, MAXLINE, 0))/*��������client������*/
		{
			if(recv_len < 0)/*����*/
			{
				printf("Recieve Data From Server Failed!\n");
				break;
			}
			printf("#");
			write_len = fwrite(buf, sizeof(char), recv_len, fp);/*д�뱾��*/
			if (write_len < recv_len)/*����*/
			{
				printf("Write file failed\n");
				break;
			}
			bzero(buf,MAXLINE);/*����*/
		}
		printf("\nFinish Recieve\n");/*�������*/
		fclose(fp);/*�ر��ļ�*/
		close(sc);/*�ر�����*/
		close(ss);/*�ر�socket����*/
		return 0;
}