#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

#define MAXCHILD 2        //最多线程数
static int alive=-1;
int i = 0;
                     //捕捉ctrl+c信号

static void fun()
{
  while(alive)
  {
       printf("pthread executing！\n");//alive＝１时子线程执行
       sleep(1);
  }
}
static void sig()
{
     alive = 0;
     printf("\npthread exit!,线程退出！\n");//主线程收到信号，将alive=0,向子线程发送停止命令
     return ;
}

int main(int argc,char *argv[])
{
  alive=1;//初始为１
  pthread_t pthread[MAXCHILD];//线号数组
  signal(SIGINT,sig);//检测信号


  for(i=0;i<MAXCHILD;i++)
   {
     pthread_create(&pthread[i],NULL,fun,NULL);//开启线程
     printf("线程%d启动！\n",i);
   }

     //等待线程结束
   for(i=0;i<MAXCHILD;i++)
   {
     pthread_join(pthread[i],NULL);//结束线程
     printf("线程%d结束！\n",i);
   }

  return 0;
}