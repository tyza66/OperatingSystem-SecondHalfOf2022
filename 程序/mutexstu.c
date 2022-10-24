#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#define BUFFER_SIZE 5
typedef int buffer_item;
 
struct v
{
    int i;
};
 
buffer_item b;	//共享变量，临界资源 
HANDLE mutex;	//互斥信号量 
//HANDLE empty,full;	//普通信号量定义,这里没用，只是定义示例而已

//进程PA 
DWORD WINAPI PA(PVOID Param)
{
    struct v data=*(struct v *)Param;
    int i=1;
    while (i<=10)   //999999 
    {
        Sleep(rand()%101*10);	//挂起，随机时长，模拟运行中其他工作时间 
        
        //WaitForSingleObject(empty,INFINITE);	//wait(empty);等empty信号量，这里没用，使用示例而已 
        WaitForSingleObject(mutex,INFINITE);	//等缓冲可用，wait(mutex)
        
        //修改缓冲 
        b++;  
		printf("PA b++, %d\n", b); 
		 
        ReleaseMutex(mutex);	//释放缓冲，互斥性信号量的signal(mutex)
		//ReleaseSemaphore(full,1,NULL);	//signal(full);,普通信号量用这个，唤，这里没用，使用示例而已  
		i++;
    }
}

//进程PB 
DWORD WINAPI PB(PVOID Param)
{
    struct v data=*(struct v *)Param;
    int i=1;
    while (i<=10)
    {
        Sleep(rand()%101*8);  //等待随机时长，模拟

        WaitForSingleObject(mutex,INFINITE);	//等缓冲，wait(mutex)
        
        //修改缓冲 
        b--;
        printf("PB b--, %d\n", b);
            
        ReleaseMutex(mutex);	//释放缓冲，互斥性信号量的signal(mutex) 
        i++;
    }
}
 
int main(int argc,char *argv[])
{  
    int sleeptime;	//挂起时长 
    DWORD ThreadIdP, ThreadIdC, i;
    struct v countP, countC;
    HANDLE ThreadHandleP, ThreadHandleC; //handle是句柄类型，操作系统要管理和操作这些资源，都是通过句柄来找到对应的资源。 
    
    b=0;	//共享变量初始值为0  
    sleeptime=20000;	//主线程挂起时长  
    
	//创建信号量 
    mutex=CreateMutex(NULL,FALSE,NULL);	//创建一个互斥体 
    //empty=CreateSemaphore(NULL,BUFFER_SIZE,BUFFER_SIZE,NULL);  //创建普通信号量empty，这里没用，使用示例而已 
    //full=CreateSemaphore(NULL,0,BUFFER_SIZE+1,NULL);	//创建普通信号量full，这里没用，使用示例而已 
    
    /*用线程同步，模拟进程同步，创建PA，PB线程*/
    /*创建PA线程1*/
 	countP.i=1;
 	ThreadHandleP=CreateThread(NULL, 0, PA, &countP, 0, &ThreadIdP);
    
    /*创建PB线程2*/   
	countC.i=2;
	ThreadHandleC=CreateThread(NULL, 0, PB, &countC, 0, &ThreadIdC);
    
    /*同步一会*/
    Sleep(sleeptime);	//主线程挂起，PA，PB子线程同步，时间到，主程序退出，子线程都退出。 
    
	/*退出*/
    return 0;
}
