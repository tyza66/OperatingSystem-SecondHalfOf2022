#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

HANDLE s1, s2;   //�ź��� 

struct v { int i; };

DWORD WINAPI Driver(PVOID Param)
{   
	while(1){          
		WaitForSingleObject(s1,INFINITE);  //�ȹ����ź�s1 
		printf("��������\n");	Sleep(500); 	//ģ����������ʱ�� 
		printf("������ʻ\n");	Sleep(2000); 
		printf("ͣ��\n");		Sleep(500); 
		ReleaseSemaphore(s2, 1, NULL);     //����ͣ���ź�s2
	}  
}
DWORD WINAPI Seller(PVOID Param)
{
	while(1){
		printf("�س���\n");		Sleep(500);
		ReleaseSemaphore(s1, 1, NULL);     //���ѹس����ź�s1	
		printf("��Ʊ\n"); 		Sleep(2000);
		WaitForSingleObject(s2,INFINITE);  //��ͣ���ź�s2 
		printf("������\n"); 	Sleep(500);        
    }
}
int main(int argc,char *argv[])
{
    int sleeptime = 30000;	//���̹߳���ʱ�� 
    DWORD ThreadIdDriver, ThreadIdSeller;
    struct v countDriver, countSeller;
    HANDLE ThreadHandleDriver, ThreadHandleSeller;
    
    s1 = CreateSemaphore(NULL, 0, 1, NULL);    //�����ź���s1
    s2 = CreateSemaphore(NULL, 0, 1, NULL);    //�����ź���s2

 	countDriver.i=1; countSeller.i=2; 
 	ThreadHandleDriver = CreateThread(NULL, 0, Driver, &countDriver, 0, &ThreadIdDriver);         //�����߳�ģ�����Driver 
  	ThreadHandleSeller = CreateThread(NULL, 0, Seller, &countSeller, 0, &ThreadIdSeller);         //�����߳�ģ�����Seller

    Sleep(sleeptime);   //���̹߳����̲߳�����ģ�����Driver��Sellerͬ�� 
    
    return 0;
}
