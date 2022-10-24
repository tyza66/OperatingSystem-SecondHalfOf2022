#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#define N 5
typedef int buffer_item;
struct v{  int i;};
buffer_item buffer[N];	//������ 
buffer_item out=0, in=0;	//���������ɻ��ζ��У�out��ͷָ�룬in��βָ�� 
HANDLE mutex, empty, full;	//�ź��� 

//�����߽��� 
DWORD WINAPI producer(PVOID Param)
{
    int nextp;
    struct v data = *(struct v *)Param;   //data.i�������߽��̱�� 
    srand((unsigned)time(NULL) + data.i + 1);	//��ʼ����������� 
    while (1){
        Sleep(rand()%1000+2000);	//����һ��2-3s��ģ������һ����Ʒ��Ҫ��ʱ�� 
		 
        nextp = rand();	//����һ����Ʒ��������һ���������ģ�� 
        
		WaitForSingleObject(empty, INFINITE);	//���п�λ 
        WaitForSingleObject(mutex, INFINITE);	//�Ȼ������ 
        
        //���뻺�� 
        buffer[in] = nextp;
        in=(in+1) % N;
       	printf("������ %d ������Ʒ %d ���������˻���أ�\n", data.i, nextp);   
		 
        ReleaseMutex(mutex);	//�ͷŻ��� 
        ReleaseSemaphore(full, 1, NULL);	//��Ʒ+1���������� 
    }
}

//�����߽��� 
DWORD WINAPI consumer(PVOID Param)
{
    int nextc;
    struct v data = *(struct v *)Param;  //data.i�����߽��̱�� 
    srand((unsigned)time(NULL) + data.i + 101);  //��ʼ����������� 
    while (1){      
        WaitForSingleObject(full, INFINITE);	//���в�Ʒ 
        WaitForSingleObject(mutex, INFINITE);	//�Ȼ��� 
        
        //�ӻ�������ȡ 
        nextc = buffer[out];
        out = (out+1) % N;
        printf("������ %d ȡ����Ʒ %d ���������ˣ�\n", data.i, nextc);
            
        ReleaseMutex(mutex);	//�ͷŻ��� 
        ReleaseSemaphore(empty, 1, NULL);	//��Ʒ-1���������� 
        
        Sleep(rand()%1000+2000);  //����һ��(2-3s)��ģ������һ����Ʒ��Ҫ��ʱ�� 
    }
}
 
int main(int argc,char *argv[])
{
    /*��ʼ��*/
    int sleeptime,pnum,cnum;	//ʱ�䣬�����߽������������߽������� 
    DWORD *ThreadIdP, *ThreadIdC, i;  //���洴�����̲����� 
    struct v *countP, *countC;  //���洴�����̲�����
    HANDLE *ThreadHandleP, *ThreadHandleC; //handle�Ǿ�����ͣ�����ϵͳҪ����Ͳ�����Щ��Դ������ͨ��������ҵ���Ӧ����Դ�� 
    
    //srand((unsigned)time(NULL));
    sleeptime=20000;	//�������Ǻ��������ǹ�ͬ����һ��ʱ�� 
    pnum=3;	//�����߽������� 
    cnum=3;	//�����߽������� 
    
    ThreadHandleP=(HANDLE *)malloc(pnum * sizeof(HANDLE));	//�������߳̾������ 
    ThreadHandleC=(HANDLE *)malloc(cnum * sizeof(HANDLE));	//�������߳̾������ 
    
	//���������ߺ������߽��̵Ĳ���
	ThreadIdP=(DWORD *)malloc(pnum * sizeof(DWORD));	 
    ThreadIdC=(DWORD *)malloc(cnum * sizeof(DWORD));	
    countP=(struct v *)malloc(pnum * sizeof(struct v));
    countC=(struct v *)malloc(cnum * sizeof(struct v));   
    
	//�����ź��� 
    mutex=CreateMutex(NULL, FALSE, NULL);	//����һ�������� 
    empty=CreateSemaphore(NULL, N, N, NULL);  //������Դ�ź��� ���������п�λ���� 
    full=CreateSemaphore(NULL, 0, N, NULL);  //������Դ�ź��� ���������в�Ʒ���� 
    
    /*�����������̣߳��������߶������ߣ����Գ��Ե��������ߺ͵��������ߣ�������Ϊ1*/
    for(i=0;i<pnum;i++){
        countP[i].i=i+1;
        ThreadHandleP[i]=CreateThread(NULL, 0, producer, &countP[i], 0, &ThreadIdP[i]);
    }
    
    /*���������߽���*/
    for(i=0;i<cnum;i++){
        countC[i].i=i+1;
        ThreadHandleC[i]=CreateThread(NULL, 0, consumer, &countC[i], 0, &ThreadIdC[i]);
    }
    
    /*����һ��*/
    Sleep(sleeptime);	//���������ߣ��߳�ִ�У�ʱ�䵽���������˳����̶߳��˳��� 
    
    getchar();
    
	/*�˳�*/
    return 0;
}
