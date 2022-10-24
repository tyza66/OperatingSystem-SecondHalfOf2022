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
 
buffer_item b;	//����������ٽ���Դ 
HANDLE mutex;	//�����ź��� 
//HANDLE empty,full;	//��ͨ�ź�������,����û�ã�ֻ�Ƕ���ʾ������

//����PA 
DWORD WINAPI PA(PVOID Param)
{
    struct v data=*(struct v *)Param;
    int i=1;
    while (i<=10)   //999999 
    {
        Sleep(rand()%101*10);	//�������ʱ����ģ����������������ʱ�� 
        
        //WaitForSingleObject(empty,INFINITE);	//wait(empty);��empty�ź���������û�ã�ʹ��ʾ������ 
        WaitForSingleObject(mutex,INFINITE);	//�Ȼ�����ã�wait(mutex)
        
        //�޸Ļ��� 
        b++;  
		printf("PA b++, %d\n", b); 
		 
        ReleaseMutex(mutex);	//�ͷŻ��壬�������ź�����signal(mutex)
		//ReleaseSemaphore(full,1,NULL);	//signal(full);,��ͨ�ź������������������û�ã�ʹ��ʾ������  
		i++;
    }
}

//����PB 
DWORD WINAPI PB(PVOID Param)
{
    struct v data=*(struct v *)Param;
    int i=1;
    while (i<=10)
    {
        Sleep(rand()%101*8);  //�ȴ����ʱ����ģ��

        WaitForSingleObject(mutex,INFINITE);	//�Ȼ��壬wait(mutex)
        
        //�޸Ļ��� 
        b--;
        printf("PB b--, %d\n", b);
            
        ReleaseMutex(mutex);	//�ͷŻ��壬�������ź�����signal(mutex) 
        i++;
    }
}
 
int main(int argc,char *argv[])
{  
    int sleeptime;	//����ʱ�� 
    DWORD ThreadIdP, ThreadIdC, i;
    struct v countP, countC;
    HANDLE ThreadHandleP, ThreadHandleC; //handle�Ǿ�����ͣ�����ϵͳҪ����Ͳ�����Щ��Դ������ͨ��������ҵ���Ӧ����Դ�� 
    
    b=0;	//���������ʼֵΪ0  
    sleeptime=20000;	//���̹߳���ʱ��  
    
	//�����ź��� 
    mutex=CreateMutex(NULL,FALSE,NULL);	//����һ�������� 
    //empty=CreateSemaphore(NULL,BUFFER_SIZE,BUFFER_SIZE,NULL);  //������ͨ�ź���empty������û�ã�ʹ��ʾ������ 
    //full=CreateSemaphore(NULL,0,BUFFER_SIZE+1,NULL);	//������ͨ�ź���full������û�ã�ʹ��ʾ������ 
    
    /*���߳�ͬ����ģ�����ͬ��������PA��PB�߳�*/
    /*����PA�߳�1*/
 	countP.i=1;
 	ThreadHandleP=CreateThread(NULL, 0, PA, &countP, 0, &ThreadIdP);
    
    /*����PB�߳�2*/   
	countC.i=2;
	ThreadHandleC=CreateThread(NULL, 0, PB, &countC, 0, &ThreadIdC);
    
    /*ͬ��һ��*/
    Sleep(sleeptime);	//���̹߳���PA��PB���߳�ͬ����ʱ�䵽���������˳������̶߳��˳��� 
    
	/*�˳�*/
    return 0;
}
