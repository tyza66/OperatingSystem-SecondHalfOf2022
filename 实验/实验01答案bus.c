#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

HANDLE s1, s2;   //信号量 

struct v { int i; };

DWORD WINAPI Driver(PVOID Param)
{   
	while(1){          
		WaitForSingleObject(s1,INFINITE);  //等关门信号s1 
		printf("启动车辆\n");	Sleep(500); 	//模拟启动工作时长 
		printf("正常行驶\n");	Sleep(2000); 
		printf("停车\n");		Sleep(500); 
		ReleaseSemaphore(s2, 1, NULL);     //发已停车信号s2
	}  
}
DWORD WINAPI Seller(PVOID Param)
{
	while(1){
		printf("关车门\n");		Sleep(500);
		ReleaseSemaphore(s1, 1, NULL);     //发已关车门信号s1	
		printf("售票\n"); 		Sleep(2000);
		WaitForSingleObject(s2,INFINITE);  //等停车信号s2 
		printf("开车门\n"); 	Sleep(500);        
    }
}
int main(int argc,char *argv[])
{
    int sleeptime = 30000;	//主线程挂起时长 
    DWORD ThreadIdDriver, ThreadIdSeller;
    struct v countDriver, countSeller;
    HANDLE ThreadHandleDriver, ThreadHandleSeller;
    
    s1 = CreateSemaphore(NULL, 0, 1, NULL);    //创建信号量s1
    s2 = CreateSemaphore(NULL, 0, 1, NULL);    //创建信号量s2

 	countDriver.i=1; countSeller.i=2; 
 	ThreadHandleDriver = CreateThread(NULL, 0, Driver, &countDriver, 0, &ThreadIdDriver);         //创建线程模拟进程Driver 
  	ThreadHandleSeller = CreateThread(NULL, 0, Seller, &countSeller, 0, &ThreadIdSeller);         //创建线程模拟进程Seller

    Sleep(sleeptime);   //主线程挂起，线程并发，模拟进程Driver和Seller同步 
    
    return 0;
}
