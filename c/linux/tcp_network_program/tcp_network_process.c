#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>

void pid_to_str(char *a, pid_t p)//���䴦����
{
	int pid;
	pid = p;
	a[0] = pid / 10000 % 10 + '0';
	a[1] = pid / 1000 % 10 + '0';
	a[2] = pid / 100 % 10 + '0';
	a[3] = pid / 10 % 10 + '0';
	a[4] = pid / 1 % 10 + '0';
}
/*�ͻ��˵Ĵ������*/
void process_conn_client(int s)
{
	ssize_t size = 0;
	char buffer[1024];							/*���ݵĻ�����*/

	char pstr[5];
	pid_t pid = getpid();
	pid_to_str(pstr, pid);
	int i, j, k = 0;

	for(;;)
	{									/*ѭ���������*/
		/*�ӱ�׼�����ж�ȡ���ݷŵ�������buffer��*/
		size = read(0, buffer, 1024);

		if(size > 0)
		{							/*��������*/
			for( i = 0; ; ++i)
			{
				if(buffer[i] == '\n')
				{
					j = i;
					for( ;j < i + 5; ++j)
					{
						buffer[j] = pstr[k++];
					}
					k = 0;
					i = 0;
					break;
				}
			}
			size += 4;
			write(s, buffer, size);				/*���͸�������*/
			size = read(s, buffer, 1024);		/*�ӷ�������ȡ����*/
			write(1, buffer, size);				/*д����׼���*/
		}
	}
}
/*�������Կͻ��˵Ĵ���*/
void process_conn_server(int s)
{
	ssize_t size = 0;
	char buffer[1024];							/*���ݵĻ�����*/
	ssize_t i = 0;
	for(;;)
	{									/*ѭ���������*/
		size = read(s, buffer, 1024);			/*���׽����ж�ȡ���ݷŵ�													������buffer��*/
		if(size == 0)
		{							/*û������*/
			return;
		}
		printf("receive client ");
		for(i = size - 5; i < size ; ++i)
		{
			printf("%c",buffer[i]);
		}
		printf("'s data:\n");
		for(i = 0; i < size - 5; i ++)
		{
			printf("%c",buffer[i]);
		}
		printf("\n");
		/*������Ӧ�ַ���Ϊ���յ��ͻ����ֽڵ�����*/
		sprintf(buffer, "%d bytes altogether\n", size);
		write(s, buffer, strlen(buffer)+1);/*�����ͻ���*/
	}
}