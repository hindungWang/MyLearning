#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

#define MAXCHILD 2        //����߳���
static int alive=-1;
int i = 0;
                     //��׽ctrl+c�ź�

static void fun()
{
  while(alive)
  {
       printf("pthread executing��\n");//alive����ʱ���߳�ִ��
       sleep(1);
  }
}
static void sig()
{
     alive = 0;
     printf("\npthread exit!,�߳��˳���\n");//���߳��յ��źţ���alive=0,�����̷߳���ֹͣ����
     return ;
}

int main(int argc,char *argv[])
{
  alive=1;//��ʼΪ��
  pthread_t pthread[MAXCHILD];//�ߺ�����
  signal(SIGINT,sig);//����ź�


  for(i=0;i<MAXCHILD;i++)
   {
     pthread_create(&pthread[i],NULL,fun,NULL);//�����߳�
     printf("�߳�%d������\n",i);
   }

     //�ȴ��߳̽���
   for(i=0;i<MAXCHILD;i++)
   {
     pthread_join(pthread[i],NULL);//�����߳�
     printf("�߳�%d������\n",i);
   }

  return 0;
}