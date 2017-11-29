#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>

void pid_to_str(char *a, pid_t p)//ｐｉｄ处理函数
{
	int pid;
	pid = p;
	a[0] = pid / 10000 % 10 + '0';
	a[1] = pid / 1000 % 10 + '0';
	a[2] = pid / 100 % 10 + '0';
	a[3] = pid / 10 % 10 + '0';
	a[4] = pid / 1 % 10 + '0';
}
/*客户端的处理过程*/
void process_conn_client(int s)
{
	ssize_t size = 0;
	char buffer[1024];							/*数据的缓冲区*/

	char pstr[5];
	pid_t pid = getpid();
	pid_to_str(pstr, pid);
	int i, j, k = 0;

	for(;;)
	{									/*循环处理过程*/
		/*从标准输入中读取数据放到缓冲区buffer中*/
		size = read(0, buffer, 1024);

		if(size > 0)
		{							/*读到数据*/
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
			write(s, buffer, size);				/*发送给服务器*/
			size = read(s, buffer, 1024);		/*从服务器读取数据*/
			write(1, buffer, size);				/*写到标准输出*/
		}
	}
}
/*服务器对客户端的处理*/
void process_conn_server(int s)
{
	ssize_t size = 0;
	char buffer[1024];							/*数据的缓冲区*/
	ssize_t i = 0;
	for(;;)
	{									/*循环处理过程*/
		size = read(s, buffer, 1024);			/*从套接字中读取数据放到													缓冲区buffer中*/
		if(size == 0)
		{							/*没有数据*/
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
		/*构建响应字符，为接收到客户端字节的数量*/
		sprintf(buffer, "%d bytes altogether\n", size);
		write(s, buffer, strlen(buffer)+1);/*发给客户端*/
	}
}