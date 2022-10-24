#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

struct v
{
    int i;
};

int b1,b2;	//缓冲区b1,b2 

HANDLE e1,f1,e2,f2;	//普通信号量定义

//进程PA 
DWORD WINAPI PA(PVOID Param)
{
    struct v data=*(struct v *)Param;
    int t,i=0; 
    while (i<4)
    {
    	Sleep(800);	//挂起，随机时长，模拟读取时间 
    	t = rand()%10000;	//生产读取的数 	
        
        WaitForSingleObject(e1,INFINITE);	//P(empty);等empty信号量，这里没用，使用示例而已 
        
        printf("PA进程从磁盘读取记录：%d，并放入缓冲区1\n", t); 
        b1 = t;  //读取的记录存入缓冲区1 
		Sleep(1100);
		 
		ReleaseSemaphore(f1,1,NULL);	//V(full);,普通信号量用这个，唤，这里没用，使用示例而已  
		i++;
    }
}

//进程PB 
DWORD WINAPI PB(PVOID Param)
{
    struct v data=*(struct v *)Param;
    int t,i=0; 
    while (i<4)
    {
    	WaitForSingleObject(f1,INFINITE);
    	
    	t = b1;  //从缓冲区1中读取记录 
    	printf("                 PB进程从缓冲区读取记录：%d\n", t);
		Sleep(900);
		
		ReleaseSemaphore(e1,1,NULL);
		
		
		
		
		WaitForSingleObject(e2,INFINITE);
		
    	b2 = t;  //把读取的记录存到缓冲区2中 
    	printf("                 PB进程把%d存到缓冲区2中\n", t); 
		Sleep(1300);
		
		ReleaseSemaphore(f2,1,NULL);
		     
		i++;
    }
}

//进程PC 
DWORD WINAPI PC(PVOID Param)
{
    struct v data=*(struct v *)Param;
    int t,i=0; 
    while (i<4)
    {
    	WaitForSingleObject(f2,INFINITE);
    	
    	t = b2;  //从缓冲区2中读取记录 
    	printf("                                                           PC进程从缓冲区2读取并打印记录：%d\n", t);
		Sleep(600);
		
		ReleaseSemaphore(e2,1,NULL);
		
		  
		i++;
    }
}

int main(int argc,char *argv[])
{  
    int sleeptime;	//挂起时长 
    DWORD ThreadIdA, ThreadIdB, ThreadIdC, i;
    struct v countA, countB, countC;
    HANDLE ThreadHandleA, ThreadHandleB, ThreadHandleC; //handle是句柄类型，操作系统要管理和操作这些资源，都是通过句柄来找到对应的资源。 
    
    b1=0;	b2=0;  
    sleeptime=20000;	//主线程挂起时长  
    
	//创建信号量 
    e1=CreateSemaphore(NULL,1,1,NULL);  //创建普通信号量
    f1=CreateSemaphore(NULL,0,1,NULL);	//创建普通信号量
    e2=CreateSemaphore(NULL,1,1,NULL);  //创建普通信号量
    f2=CreateSemaphore(NULL,0,1,NULL);	//创建普通信号量
    
    /*用线程同步，模拟进程同步，创建PA，PB, PC线程*/
    /*创建PA线程1*/
 	countA.i=1;
 	ThreadHandleA=CreateThread(NULL, 0, PA, &countA, 0, &ThreadIdA);
    
    /*创建PB线程2*/   
	countB.i=2;
	ThreadHandleB=CreateThread(NULL, 0, PB, &countB, 0, &ThreadIdB);
	
	/*创建PC线程2*/   
	countC.i=2;
	ThreadHandleC=CreateThread(NULL, 0, PC, &countC, 0, &ThreadIdC);
    
    /*同步一会*/
    Sleep(sleeptime);	//主线程挂起，PA，PB,PC子线程同步，时间到，主程序退出，子线程都退出。 
    
	/*退出*/
    return 0;
}
