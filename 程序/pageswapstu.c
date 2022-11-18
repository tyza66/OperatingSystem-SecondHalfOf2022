#include<stdio.h>

//opt算法实现，ps数组存页面序列，pageCount页面总数，blockCount内存的物理块数 
void OPT(int ps[],int pageCount,int blockCount)
{        
	//算法
	 
	//printf("OPT缺页次数为:%d\n",nopage);   
	//printf("OPT缺页率为:%d/%d=%.2f%%\n\n",nopage,pageCount,(float)nopage/pageCount*100);   
     
} 

//FIFO算法实现，ps数组存页面序列，pageCount页面总数，blockCount内存的物理块数 
void FIFO(int ps[],int pageCount,int blockCount)
{        
 	//算法
	  
	//printf("FIFO缺页次数为:%d\n",nopage);   
	//printf("FIFO缺页率为:%d/%d=%.2f%%\n\n",nopage,pageCount,(float)nopage/pageCount*100);   
     
}

//LRU中用特殊栈实现 
int stack[100];  //特殊栈,栈最大元素个数等于进程分配物理块数 
int top=0; //指栈顶的上一个元素

//特殊栈的入栈操作,先从栈中删除要入的元素，然后再入栈顶 
int push(int x)
{
	int i,j;
	if(top<=0){//空栈直接入 
		stack[top]=x;
		top++;
	}else{
		for(i=0;i<top;i++)
			if(x == stack[i])
				break;
		if(i<top){//要入栈的元素在栈中：先删元素，再入x 
			for(j=i+1;j<top;j++) //元素下移 
				stack[j-1]=stack[j];
			stack[top-1]=x;  //入栈 
		}else{  //不在栈中：直接入栈 
			stack[top]=x; 
			top++;
		}		
	}

	return 1;
}

//取栈底 
int getbottom(){
	int x;
	int i;
	x = stack[0];
	for(i=1;i<top;i++)
		stack[i-1]=stack[i];
	top--;
	return x;
}
 
//LRU算法实现，ps数组存页面序列，pageCount页面总数，blockCount内存的物理块数 
void LRU(int ps[],int pageCount,int blockCount)
{        
 	//算法 
 	
	//printf("LRU缺页次数为:%d\n",nopage);   
	//printf("LRU缺页率为:%d/%d=%.2f%%\n\n",nopage,pageCount,(float)nopage/pageCount*100);   
     
}

main()
{   
	int pageCount,blockCount,i,ps[100];
	int ch;

	// 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1 -1
    printf("输入进程访问的页面走向序列（-1结束）:");
	i=0;
	scanf("%d",&ps[i]); 
    while(ps[i]!=-1){
		i++; 
		scanf("%d",&ps[i]);
    }
    pageCount = i;
    
	printf("输入进程分配的内存物理块数:");   // 3
	scanf("%d",&blockCount);   
	
	i=1;
	while(i){
		printf("请选择使用的页面置换算法（0: OPT, 1: FIFO, 2: LRU, -1: 退出）：");
		scanf("%d",&ch);
		switch(ch){
			case 0: OPT(ps, pageCount, blockCount); break; 
			case 1: FIFO(ps, pageCount, blockCount); break;
			case 2: LRU(ps, pageCount, blockCount); break;
			default: i=0; break;
		} 
	}
}
