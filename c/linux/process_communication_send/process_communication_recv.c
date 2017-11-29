#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGMAX 1024//消息的长度
struct msgmbuf
{
	long int mtype;//消息类型
	char mtext[MSGMAX];
} receivebuf;

key_t key = 5678;
int msg_flags = IPC_CREAT;

int main()
{
	int msgid;
	long int re = 0;
	msgid = msgget(key,msg_flags|0666);//打开消息队列
	if(msgid == -1)
	{
		printf("msgget error!\n");
    	perror("msgget");
		exit(1);
	}
	if(msgrcv(msgid,(void *)&receivebuf, MSGMAX, re, 0) == -1)//接收信息函数
	{
		printf("msgrcv error!\n");
		exit(1);
	}
	printf("Receive : %s", receivebuf.mtext);
	if(msgctl(msgid, IPC_RMID, 0) == -1)//消息控制函数，IPC_RMID执行内核删除队列
	{
		printf("msgct(IPC_RMID)  failed!\n");
		exit(1);
	}
	return 0;
}