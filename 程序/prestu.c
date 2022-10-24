//实验1 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

HANDLE a, b, c, d, e, f, g;   //信号量 

struct v { int i; };

DWORD WINAPI p1(PVOID Param)
{
    printf("S1\n");
    ReleaseSemaphore(a, 1, NULL);     //唤a 
    ReleaseSemaphore(b, 1, NULL);     //唤b 
}

DWORD WINAPI p2(PVOID Param)
{
    WaitForSingleObject(a,INFINITE);  //等a 
    printf("S2\n");
    ReleaseSemaphore(c, 1, NULL);     //唤c
    ReleaseSemaphore(d, 1, NULL);     //唤d
}

DWORD WINAPI p3(PVOID Param)
{
    WaitForSingleObject(b,INFINITE);  //等b
    printf("S3\n");
    ReleaseSemaphore(e, 1, NULL);   //唤e
}

DWORD WINAPI p4(PVOID Param)
{
    WaitForSingleObject(c,INFINITE);     //等c
    printf("S4\n");
    ReleaseSemaphore(f, 1, NULL);   //唤f
}

DWORD WINAPI p5(PVOID Param)
{
    WaitForSingleObject(d,INFINITE);     //等d
    printf("S5\n");
    ReleaseSemaphore(g, 1, NULL);   //唤f
}

DWORD WINAPI p6(PVOID Param)
{
    WaitForSingleObject(e,INFINITE);     //等e
    WaitForSingleObject(f,INFINITE);     //等f
    WaitForSingleObject(g,INFINITE);     //等g
    printf("S6\n");
}

int main(int argc,char *argv[])
{
    int sleeptime = 10000;	//主线程挂起时长 
    DWORD ThreadIdP1, ThreadIdP2, ThreadIdP3, ThreadIdP4, ThreadIdP5, ThreadIdP6;
    struct v countP1, countP2, countP3, countP4, countP5, countP6;
    HANDLE ThreadHandleP1, ThreadHandleP2, ThreadHandleP3, ThreadHandleP4, ThreadHandleP5, ThreadHandleP6;	
	
    a = CreateSemaphore(NULL, 0, 1, NULL);    //创建普通信号量a 
    b = CreateSemaphore(NULL, 0, 1, NULL);    //创建普通信号量b
    c = CreateSemaphore(NULL, 0, 1, NULL);    //创建普通信号量c
    d = CreateSemaphore(NULL, 0, 1, NULL);    //创建普通信号量d
    e = CreateSemaphore(NULL, 0, 1, NULL);    //创建普通信号量e
    f = CreateSemaphore(NULL, 0, 1, NULL);    //创建普通信号量f
    g = CreateSemaphore(NULL, 0, 1, NULL);    //创建普通信号量g

 	countP1.i=1; countP2.i=2; countP3.i=3; countP4.i=4; countP5.i=5; countP6.i=6; 
 	ThreadHandleP1 = CreateThread(NULL, 0, p1, &countP1, 0, &ThreadIdP1);         //创建线程模拟进程p1 
  	ThreadHandleP2 = CreateThread(NULL, 0, p2, &countP2, 0, &ThreadIdP2);         //创建线程模拟进程p2
  	ThreadHandleP3 = CreateThread(NULL, 0, p3, &countP3, 0, &ThreadIdP3);         //创建线程模拟进程p3
  	ThreadHandleP4 = CreateThread(NULL, 0, p4, &countP4, 0, &ThreadIdP4);         //创建线程模拟进程p4
  	ThreadHandleP5 = CreateThread(NULL, 0, p5, &countP5, 0, &ThreadIdP5);         //创建线程模拟进程p5
  	ThreadHandleP6 = CreateThread(NULL, 0, p6, &countP6, 0, &ThreadIdP6);         //创建线程模拟进程p6

    Sleep(sleeptime);   //多个进程运行一段时间 
    
    return 0;
}
