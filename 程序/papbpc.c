#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

struct v
{
    int i;
};

int b1,b2;	//������b1,b2 

HANDLE e1,f1,e2,f2;	//��ͨ�ź�������

//����PA 
DWORD WINAPI PA(PVOID Param)
{
    struct v data=*(struct v *)Param;
    int t,i=0; 
    while (i<4)
    {
    	Sleep(800);	//�������ʱ����ģ���ȡʱ�� 
    	t = rand()%10000;	//������ȡ���� 	
        
        WaitForSingleObject(e1,INFINITE);	//P(empty);��empty�ź���������û�ã�ʹ��ʾ������ 
        
        printf("PA���̴Ӵ��̶�ȡ��¼��%d�������뻺����1\n", t); 
        b1 = t;  //��ȡ�ļ�¼���뻺����1 
		Sleep(1100);
		 
		ReleaseSemaphore(f1,1,NULL);	//V(full);,��ͨ�ź������������������û�ã�ʹ��ʾ������  
		i++;
    }
}

//����PB 
DWORD WINAPI PB(PVOID Param)
{
    struct v data=*(struct v *)Param;
    int t,i=0; 
    while (i<4)
    {
    	WaitForSingleObject(f1,INFINITE);
    	
    	t = b1;  //�ӻ�����1�ж�ȡ��¼ 
    	printf("                 PB���̴ӻ�������ȡ��¼��%d\n", t);
		Sleep(900);
		
		ReleaseSemaphore(e1,1,NULL);
		
		
		
		
		WaitForSingleObject(e2,INFINITE);
		
    	b2 = t;  //�Ѷ�ȡ�ļ�¼�浽������2�� 
    	printf("                 PB���̰�%d�浽������2��\n", t); 
		Sleep(1300);
		
		ReleaseSemaphore(f2,1,NULL);
		     
		i++;
    }
}

//����PC 
DWORD WINAPI PC(PVOID Param)
{
    struct v data=*(struct v *)Param;
    int t,i=0; 
    while (i<4)
    {
    	WaitForSingleObject(f2,INFINITE);
    	
    	t = b2;  //�ӻ�����2�ж�ȡ��¼ 
    	printf("                                                           PC���̴ӻ�����2��ȡ����ӡ��¼��%d\n", t);
		Sleep(600);
		
		ReleaseSemaphore(e2,1,NULL);
		
		  
		i++;
    }
}

int main(int argc,char *argv[])
{  
    int sleeptime;	//����ʱ�� 
    DWORD ThreadIdA, ThreadIdB, ThreadIdC, i;
    struct v countA, countB, countC;
    HANDLE ThreadHandleA, ThreadHandleB, ThreadHandleC; //handle�Ǿ�����ͣ�����ϵͳҪ����Ͳ�����Щ��Դ������ͨ��������ҵ���Ӧ����Դ�� 
    
    b1=0;	b2=0;  
    sleeptime=20000;	//���̹߳���ʱ��  
    
	//�����ź��� 
    e1=CreateSemaphore(NULL,1,1,NULL);  //������ͨ�ź���
    f1=CreateSemaphore(NULL,0,1,NULL);	//������ͨ�ź���
    e2=CreateSemaphore(NULL,1,1,NULL);  //������ͨ�ź���
    f2=CreateSemaphore(NULL,0,1,NULL);	//������ͨ�ź���
    
    /*���߳�ͬ����ģ�����ͬ��������PA��PB, PC�߳�*/
    /*����PA�߳�1*/
 	countA.i=1;
 	ThreadHandleA=CreateThread(NULL, 0, PA, &countA, 0, &ThreadIdA);
    
    /*����PB�߳�2*/   
	countB.i=2;
	ThreadHandleB=CreateThread(NULL, 0, PB, &countB, 0, &ThreadIdB);
	
	/*����PC�߳�2*/   
	countC.i=2;
	ThreadHandleC=CreateThread(NULL, 0, PC, &countC, 0, &ThreadIdC);
    
    /*ͬ��һ��*/
    Sleep(sleeptime);	//���̹߳���PA��PB,PC���߳�ͬ����ʱ�䵽���������˳������̶߳��˳��� 
    
	/*�˳�*/
    return 0;
}
