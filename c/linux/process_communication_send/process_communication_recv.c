#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGMAX 1024//��Ϣ�ĳ���
struct msgmbuf
{
	long int mtype;//��Ϣ����
	char mtext[MSGMAX];
} receivebuf;

key_t key = 5678;
int msg_flags = IPC_CREAT;

int main()
{
	int msgid;
	long int re = 0;
	msgid = msgget(key,msg_flags|0666);//����Ϣ����
	if(msgid == -1)
	{
		printf("msgget error!\n");
    	perror("msgget");
		exit(1);
	}
	if(msgrcv(msgid,(void *)&receivebuf, MSGMAX, re, 0) == -1)//������Ϣ����
	{
		printf("msgrcv error!\n");
		exit(1);
	}
	printf("Receive : %s", receivebuf.mtext);
	if(msgctl(msgid, IPC_RMID, 0) == -1)//��Ϣ���ƺ�����IPC_RMIDִ���ں�ɾ������
	{
		printf("msgct(IPC_RMID)  failed!\n");
		exit(1);
	}
	return 0;
}