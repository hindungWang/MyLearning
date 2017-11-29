#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8888/*�˿�*/

int main(int argc, char *argv[])
{
	int s;										/*socket������*/
	FILE *fp;
	struct sockaddr_in server_addr;			/*��������ַ�ṹ*/
	size_t MAXLINE = 1024;/*��󳤶�*/
	char buf[1024]; ����/*���û����ڴ�*/
	int read_len = -1;   /*д��־*/
	int send_len = -1;  /*���ͱ�־*/
	bzero(buf, MAXLINE);/*����*/
	s = socket(AF_INET, SOCK_STREAM, 0); 		/*����һ����ʽ�׽���*/
	if(s < 0){									/*����*/
		printf("socket error\n");
		return -1;
	}
	if (argc <= 2)/*��ʽ����*/
	{
        printf("Usage ./client + server_addr + filename to send file\n");
				exit(0);
	}
	fp = fopen(argv[2], "r");/*���ļ��Զ���*/
	if(fp == NULL)/*���ļ�ʧ��*/
	{
		perror("open file failed!\n");
		exit(0);
	}

	/*���÷�������ַ*/
	bzero(&server_addr, sizeof(server_addr));	/*����*/
	server_addr.sin_family = AF_INET;					/*Э����*/
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);	/*���ص�ַ*/
	server_addr.sin_port = htons(PORT);				/*�������˿�*/

	/*���û�������ַ������͵�IP��ַתΪ����*/
	inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
	connect(s, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));/*���ӷ�����*/
	bzero(buf, MAXLINE);/*����*/

	read_len = fread(buf, sizeof(char), MAXLINE, fp);/*���ļ�*/
	while (read_len > 0 )//******
	{
		send_len = send(s, buf, read_len, 0);/*ѭ������*/
		if ( send_len < 0 )/*����*/
		{
			perror("Send file failed\n");
			exit(0);
		}
		bzero(buf, MAXLINE);/*����*/
		read_len = fread(buf, sizeof(char), 1024, fp);/*�������ļ�*/
	}
	fclose(fp);/*����ر��ļ�*/
	printf("file send ok!\n");/*������*/
	close(s);						/*�ر�socket����*/
	return 0;
}