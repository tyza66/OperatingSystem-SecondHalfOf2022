//ʵ��1 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

HANDLE a, b, c, d, e, f, g;   //�ź��� 

struct v { int i; };

DWORD WINAPI p1(PVOID Param)
{
    printf("S1\n");
    ReleaseSemaphore(a, 1, NULL);     //��a 
    ReleaseSemaphore(b, 1, NULL);     //��b 
}

DWORD WINAPI p2(PVOID Param)
{
    WaitForSingleObject(a,INFINITE);  //��a 
    printf("S2\n");
    ReleaseSemaphore(c, 1, NULL);     //��c
    ReleaseSemaphore(d, 1, NULL);     //��d
}

DWORD WINAPI p3(PVOID Param)
{
    WaitForSingleObject(b,INFINITE);  //��b
    printf("S3\n");
    ReleaseSemaphore(e, 1, NULL);   //��e
}

DWORD WINAPI p4(PVOID Param)
{
    WaitForSingleObject(c,INFINITE);     //��c
    printf("S4\n");
    ReleaseSemaphore(f, 1, NULL);   //��f
}

DWORD WINAPI p5(PVOID Param)
{
    WaitForSingleObject(d,INFINITE);     //��d
    printf("S5\n");
    ReleaseSemaphore(g, 1, NULL);   //��f
}

DWORD WINAPI p6(PVOID Param)
{
    WaitForSingleObject(e,INFINITE);     //��e
    WaitForSingleObject(f,INFINITE);     //��f
    WaitForSingleObject(g,INFINITE);     //��g
    printf("S6\n");
}

int main(int argc,char *argv[])
{
    int sleeptime = 10000;	//���̹߳���ʱ�� 
    DWORD ThreadIdP1, ThreadIdP2, ThreadIdP3, ThreadIdP4, ThreadIdP5, ThreadIdP6;
    struct v countP1, countP2, countP3, countP4, countP5, countP6;
    HANDLE ThreadHandleP1, ThreadHandleP2, ThreadHandleP3, ThreadHandleP4, ThreadHandleP5, ThreadHandleP6;	
	
    a = CreateSemaphore(NULL, 0, 1, NULL);    //������ͨ�ź���a 
    b = CreateSemaphore(NULL, 0, 1, NULL);    //������ͨ�ź���b
    c = CreateSemaphore(NULL, 0, 1, NULL);    //������ͨ�ź���c
    d = CreateSemaphore(NULL, 0, 1, NULL);    //������ͨ�ź���d
    e = CreateSemaphore(NULL, 0, 1, NULL);    //������ͨ�ź���e
    f = CreateSemaphore(NULL, 0, 1, NULL);    //������ͨ�ź���f
    g = CreateSemaphore(NULL, 0, 1, NULL);    //������ͨ�ź���g

 	countP1.i=1; countP2.i=2; countP3.i=3; countP4.i=4; countP5.i=5; countP6.i=6; 
 	ThreadHandleP1 = CreateThread(NULL, 0, p1, &countP1, 0, &ThreadIdP1);         //�����߳�ģ�����p1 
  	ThreadHandleP2 = CreateThread(NULL, 0, p2, &countP2, 0, &ThreadIdP2);         //�����߳�ģ�����p2
  	ThreadHandleP3 = CreateThread(NULL, 0, p3, &countP3, 0, &ThreadIdP3);         //�����߳�ģ�����p3
  	ThreadHandleP4 = CreateThread(NULL, 0, p4, &countP4, 0, &ThreadIdP4);         //�����߳�ģ�����p4
  	ThreadHandleP5 = CreateThread(NULL, 0, p5, &countP5, 0, &ThreadIdP5);         //�����߳�ģ�����p5
  	ThreadHandleP6 = CreateThread(NULL, 0, p6, &countP6, 0, &ThreadIdP6);         //�����߳�ģ�����p6

    Sleep(sleeptime);   //�����������һ��ʱ�� 
    
    return 0;
}
