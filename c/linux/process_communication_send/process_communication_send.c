#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSGMAX 1024//消息的长度
struct msgmbuf
{
	long int mtype;//消息类型
	char mtext[MSGMAX];//消息数据
} sendbuf;
key_t key = 5678;//键值，将被用来与内核中其他消息队列现有的关键值相比较，比较之后，打开或访问操作依赖于msg_flags
int msg_flags = IPC_CREAT;//若内核不存在该队列，则创建它


int main()
{
	int msgid;//消息队列标识符
  printf("Write your msg:\n");
	msgid = msgget(key,msg_flags|0666);//获得消息函数
	if(msgid == -1)
	{
		printf("msgget error!\n");
    perror("msgget");
		exit(1);
	}
	fgets(sendbuf.mtext,MSGMAX,stdin);//键入消息
	sendbuf.mtype = 1;
	if(msgsnd(msgid,(void *)&sendbuf, MSGMAX, 0) == -1)//发送消息
	{
		printf("msgsnd error!\n");
		exit(1);
	}
	return 0;
}