#include<stdio.h>

//FCFS算法实现，ts数组存磁道序列，trackCount磁道总数，currTrack当前磁头所在磁道 
void FCFS(int ts[],int trackCount, int currTrack)
{        
 	int i,mv; 
	int totalMoveTrack = 0; //总移动磁道数 
	printf("0：先来先服务磁盘调度算法(FCFS)\n"); 
	
	printf("从%d号磁道开始\n", currTrack); 
	printf("被访问的下一个磁道号\t移动距离(磁道数)\n"); 
	
	for(i=0;i<trackCount;i++){   //按磁道序列依次访问每个磁道 
		mv = abs(currTrack - ts[i]);	//计算移动距离 
		
		printf("%d\t\t\t%d\n", ts[i], mv);	//输出过程 
		
		totalMoveTrack += mv; //记入总数 
		currTrack = ts[i];	//置这个磁道为当前磁道，这时可以访问这个磁道 
	}//end for
	   
	printf("平均寻到长度:%d/%d=%.2f\n\n", totalMoveTrack, trackCount, (float)totalMoveTrack/trackCount);     
}

//SSTF算法实现，ts数组存磁道序列，trackCount磁道总数，currTrack当前磁头所在磁道 
void SSTF(int ts[],int trackCount, int currTrack)
{        
 	//请在此处补充代码模拟SSTF算法。 
}

//SCAN算法实现，ts数组存磁道序列，trackCount磁道总数，currTrack当前磁头所在磁道 
void SCAN(int ts[],int trackCount, int currTrack)
{        
 	//请在此处补充代码模拟SCAN算法。  
}

//CSCAN算法实现，ts数组存磁道序列，trackCount磁道总数，currTrack当前磁头所在磁道 
void CSCAN(int ts[],int trackCount, int currTrack)
{        
 	//请在此处补充代码模拟CSCAN算法。 
}

main()
{   
	int i, ts[100];
	int ch, trackCount;
	int currTrack; 

	//书上例子：磁道序列：55 58 39 18 90 160 150 38 184 -1，当前磁道：100，递增 
	//习题例子2：磁道序列：23 376 205 132 19 61 190 398 29 4 18 40 -1，当前磁道：100，递减 
    printf("输入进程访问的磁道序列（-1结束）:");
	i=0;
	scanf("%d",&ts[i]); 
    while(ts[i]!=-1){
		i++; 
		scanf("%d",&ts[i]);
    }
    trackCount = i;  
    
    printf("请输入磁头所在的磁道:");
	scanf("%d",&currTrack); 
	
	i=1;
	while(i){
		printf("请选择使用的调度算法（0: FCFS, 1: SSTF, 2: SCAN, 3: CSCAN, -1: 退出）：");
		scanf("%d",&ch);
		switch(ch){
			case 0: FCFS(ts, trackCount, currTrack); break; 
			case 1: SSTF(ts, trackCount, currTrack); break;
			case 2: SCAN(ts, trackCount, currTrack); break;
			case 3: CSCAN(ts, trackCount, currTrack); break;
			default: i=0; break;
		} 
	}
}
