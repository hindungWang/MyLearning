#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8888								/*�����˿ڵ�ַ*/

int main(int argc, char *argv[])
{
	int s;										/*sΪsocket������*/
	struct sockaddr_in server_addr;			/*��������ַ�ṹ*/
	pid_t pid = getpid();
	printf("your client pid : %d\n", pid);
	s = socket(AF_INET, SOCK_STREAM, 0); 		/*����һ����ʽ�׽��� */
	if(s < 0){									/*����*/
		printf("socket error\n");
		return -1;
	}

	/*���÷�������ַ*/
	bzero(&server_addr, sizeof(server_addr));	/*����*/
	server_addr.sin_family = AF_INET;					/*Э����*/
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);	/*���ص�ַ*/
	server_addr.sin_port = htons(PORT);				/*�������˿�*/

	/*���û�������ַ������͵�IP��ַתΪ����*/
	inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
	/*���ӷ�����*/
	connect(s, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));
	process_conn_client(s);						/*�ͻ��˴������*/
	close(s);									/*�ر�����*/
	return 0;
}