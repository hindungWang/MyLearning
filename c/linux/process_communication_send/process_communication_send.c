#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSGMAX 1024//��Ϣ�ĳ���
struct msgmbuf
{
	long int mtype;//��Ϣ����
	char mtext[MSGMAX];//��Ϣ����
} sendbuf;
key_t key = 5678;//��ֵ�������������ں���������Ϣ�������еĹؼ�ֵ��Ƚϣ��Ƚ�֮�󣬴򿪻���ʲ���������msg_flags
int msg_flags = IPC_CREAT;//���ں˲����ڸö��У��򴴽���


int main()
{
	int msgid;//��Ϣ���б�ʶ��
  printf("Write your msg:\n");
	msgid = msgget(key,msg_flags|0666);//�����Ϣ����
	if(msgid == -1)
	{
		printf("msgget error!\n");
    perror("msgget");
		exit(1);
	}
	fgets(sendbuf.mtext,MSGMAX,stdin);//������Ϣ
	sendbuf.mtype = 1;
	if(msgsnd(msgid,(void *)&sendbuf, MSGMAX, 0) == -1)//������Ϣ
	{
		printf("msgsnd error!\n");
		exit(1);
	}
	return 0;
}