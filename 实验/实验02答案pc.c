#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#define N 5
typedef int buffer_item;
struct v{  int i;};
buffer_item buffer[N];	//缓冲区 
buffer_item out=0, in=0;	//缓冲区构成环形队列，out队头指针，in队尾指针 
HANDLE mutex, empty, full;	//信号量 

//生产者进程 
DWORD WINAPI producer(PVOID Param)
{
    int nextp;
    struct v data = *(struct v *)Param;   //data.i是生产者进程编号 
    srand((unsigned)time(NULL) + data.i + 1);	//初始化随机数种子 
    while (1){
        Sleep(rand()%1000+2000);	//挂起一会2-3s，模拟生成一个产品需要的时间 
		 
        nextp = rand();	//生成一个产品，这里用一个随机数来模拟 
        
		WaitForSingleObject(empty, INFINITE);	//等有空位 
        WaitForSingleObject(mutex, INFINITE);	//等缓冲可用 
        
        //加入缓冲 
        buffer[in] = nextp;
        in=(in+1) % N;
       	printf("生产者 %d 生产产品 %d ，并加入了缓冲池！\n", data.i, nextp);   
		 
        ReleaseMutex(mutex);	//释放缓冲 
        ReleaseSemaphore(full, 1, NULL);	//产品+1，唤消费者 
    }
}

//消费者进程 
DWORD WINAPI consumer(PVOID Param)
{
    int nextc;
    struct v data = *(struct v *)Param;  //data.i消费者进程编号 
    srand((unsigned)time(NULL) + data.i + 101);  //初始化随机数种子 
    while (1){      
        WaitForSingleObject(full, INFINITE);	//等有产品 
        WaitForSingleObject(mutex, INFINITE);	//等缓冲 
        
        //从缓冲区中取 
        nextc = buffer[out];
        out = (out+1) % N;
        printf("消费者 %d 取出产品 %d ，并消费了！\n", data.i, nextc);
            
        ReleaseMutex(mutex);	//释放缓冲 
        ReleaseSemaphore(empty, 1, NULL);	//产品-1，唤生产者 
        
        Sleep(rand()%1000+2000);  //挂起一会(2-3s)，模拟消费一个产品需要的时间 
    }
}
 
int main(int argc,char *argv[])
{
    /*初始化*/
    int sleeptime,pnum,cnum;	//时间，生产者进程数，消费者进程数。 
    DWORD *ThreadIdP, *ThreadIdC, i;  //保存创建进程参数用 
    struct v *countP, *countC;  //保存创建进程参数用
    HANDLE *ThreadHandleP, *ThreadHandleC; //handle是句柄类型，操作系统要管理和操作这些资源，都是通过句柄来找到对应的资源。 
    
    //srand((unsigned)time(NULL));
    sleeptime=20000;	//生产者们和消费者们共同运行一段时间 
    pnum=3;	//生产者进程总数 
    cnum=3;	//消费者进程总数 
    
    ThreadHandleP=(HANDLE *)malloc(pnum * sizeof(HANDLE));	//生产者线程句柄数组 
    ThreadHandleC=(HANDLE *)malloc(cnum * sizeof(HANDLE));	//消费者线程句柄数组 
    
	//创建生产者和消费者进程的参数
	ThreadIdP=(DWORD *)malloc(pnum * sizeof(DWORD));	 
    ThreadIdC=(DWORD *)malloc(cnum * sizeof(DWORD));	
    countP=(struct v *)malloc(pnum * sizeof(struct v));
    countC=(struct v *)malloc(cnum * sizeof(struct v));   
    
	//创建信号量 
    mutex=CreateMutex(NULL, FALSE, NULL);	//创建一个互斥体 
    empty=CreateSemaphore(NULL, N, N, NULL);  //创建资源信号量 ，缓冲区中空位数量 
    full=CreateSemaphore(NULL, 0, N, NULL);  //创建资源信号量 ，缓冲区中产品数量 
    
    /*创建生产者线程，多生产者多消费者，可以尝试单个生产者和单个消费者，即个数为1*/
    for(i=0;i<pnum;i++){
        countP[i].i=i+1;
        ThreadHandleP[i]=CreateThread(NULL, 0, producer, &countP[i], 0, &ThreadIdP[i]);
    }
    
    /*创建消费者进程*/
    for(i=0;i<cnum;i++){
        countC[i].i=i+1;
        ThreadHandleC[i]=CreateThread(NULL, 0, consumer, &countC[i], 0, &ThreadIdC[i]);
    }
    
    /*并行一会*/
    Sleep(sleeptime);	//主程序休眠，线程执行，时间到，主程序退出，线程都退出。 
    
    getchar();
    
	/*退出*/
    return 0;
}
