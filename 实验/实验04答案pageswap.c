#include<stdio.h>

//opt算法实现，ps数组存页面序列，pageCount页面总数，blockCount内存的物理块数 
void OPT(int ps[],int pageCount,int blockCount)
{        
 	int i; 
	int pb[100];  //物理内存， blockCount为块数 
	int pages=0;  //内存中的页面数 
	int zhkh=0;
	int j,k,l;
	int nopage=0;  //缺页次数 
	
	printf("0：最佳置换算法(OPT)\n"); 	
	
	for(i=0;i<blockCount;i++)//初始内存置-1代表空 
		pb[i]=-1; 
		
	for(i=0;i<pageCount;i++){   //按页面走向序列循环走每个页面 
		
		//1.在物理内存中找要访问的页 
		for(j=0;j<blockCount;j++){
			if(pb[j]==ps[i])//找到了
				break; 
		}
		if(j>=blockCount){//在内存中没找到要访问的页，缺页中断 
			nopage++;	//缺页中断数统计 
			 
			if(pages<blockCount){//现在内存空间还足够 
				pb[zhkh]=ps[i];  
				zhkh = (zhkh+1) % blockCount; 	//开始意向循环置 
				pages++;  //已占用页数 
				printf("%3d:",ps[i]);
				for(k=0;k<blockCount;k++)
					printf("%3d",pb[k]);
				printf("，缺页中断，内存空间足够，直接加载。\n"); 
			}else{//内存空间不足，采用置换算法 
	  			
	  			//用OPT算法找要被置换的页面 
	  			int fwwz = -1;  //记录内存页出现位置最远的页 ，zhkh记录下标 
				for(k=0;k<blockCount;k++){
					for(l=i+1;l<pageCount;l++)//向后找访问的 
						if(pb[k]==ps[l])	
							break;
					if(l>fwwz){
						fwwz = l; 	//记录访问位置 
						zhkh = k;								
					}						
				}//end for
				
				//要置换的物理内存块号在zhkh中 
				int tzhy;
				printf("%3d:",ps[i]);
				tzhy = pb[zhkh];  //保存刚置换的页 
				pb[zhkh] = ps[i];
				for(k=0;k<blockCount;k++)
					printf("%3d",pb[k]);
				printf("，缺页中断，内存空间不足，置换掉%2d页，再加载。\n",tzhy); 
				 
			}//end else 内存不足 			
		}else{
			printf("%3d:         ，页在内存中，未发生缺页中断，直接访问。\n", ps[i]);
		}//end else  在内存中找到要访问的页了，未发生缺页中断 
    
	}//end for 
	printf("OPT缺页次数为:%d\n",nopage);   
	printf("OPT缺页率为:%d/%d=%.2f%%\n\n",nopage,pageCount,(float)nopage/pageCount*100);   
     
} 

//FIFO算法实现，ps数组存页面序列，pageCount页面总数，blockCount内存的物理块数 
void FIFO(int ps[],int pageCount,int blockCount)
{        
 	int i; 
	int pb[100];  //物理内存， blockCount为块数 
	int pages=0;  //内存中的页面数 
	int zhkh=0;
	int j,k,l;
	int nopage=0;  //缺页次数 
	
	printf("1：先进先出置换算法(FIFO)\n"); 
	
	for(i=0;i<blockCount;i++)//初始内存置-1代表空 
		pb[i]=-1; 
		
	for(i=0;i<pageCount;i++){   //按页面走向序列循环走每个页面 
		
		//1.在物理内存中找要访问的页 
		for(j=0;j<blockCount;j++){
			if(pb[j]==ps[i])//找到了
				break; 
		}
		if(j>=blockCount){//在内存中没找到要访问的页，缺页中断 
			nopage++;	//缺页中断数统计 
			 
			if(pages<blockCount){//现在内存空间还足够 
				pb[zhkh]=ps[i];  
				zhkh = (zhkh+1) % blockCount; 	//开始意向循环置 
				pages++;  //已占用页数 
				printf("%3d:",ps[i]);
				for(k=0;k<blockCount;k++)
					printf("%3d",pb[k]);
				printf("，缺页中断，内存空间足够，直接加载。\n"); 
			}else{//内存空间不足，采用置换算法 
	  			
	  			//用FIFO算法找要被置换的页面 	
				//要置换的物理内存块号在zhkh中
				int tzhy; 
				printf("%3d:",ps[i]);
				tzhy =  pb[zhkh]; //暂存要置换掉的页 
				pb[zhkh] = ps[i];
				zhkh = (zhkh+1) % blockCount; 	//FIFO循环位置指针即可 
				for(k=0;k<blockCount;k++)
					printf("%3d",pb[k]);
				printf("，缺页中断，内存空间不足，置换掉%2d页，再加载。\n",tzhy); 
				 
			}//end else 内存不足 			
		}else{
			printf("%3d:         ，页在内存中，未发生缺页中断，直接访问。\n", ps[i]);
		}//end else  在内存中找到要访问的页了，未发生缺页中断 
    
	}//end for 
	printf("FIFO缺页次数为:%d\n",nopage);   
	printf("FIFO缺页率为:%d/%d=%.2f%%\n\n",nopage,pageCount,(float)nopage/pageCount*100);   
     
}

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
 	int i; 
	int pb[100];  //物理内存， blockCount为块数 
	int pages=0;  //内存中的页面数 
	int zhkh=0;
	int j,k,l;
	int nopage=0;  //缺页次数 

	
	printf("2：最近最久未使用置换算法(LRU)\n"); 
	
	for(i=0;i<blockCount;i++)//初始内存置-1代表空 
		pb[i]=-1; 
		
	for(i=0;i<pageCount;i++){   //按页面走向序列循环走每个页面 
		
		//1.在物理内存中找要访问的页 
		for(j=0;j<blockCount;j++){
			if(pb[j]==ps[i])//找到了
				break; 
		}
		if(j>=blockCount){//在内存中没找到要访问的页，缺页中断 
			nopage++;	//缺页中断数统计 
			 
			if(pages<blockCount){//现在内存空间还足够 
				pb[zhkh]=ps[i];  
				zhkh = (zhkh+1) % blockCount; 	//开始意向循环置 
				pages++;  //已占用页数 
				
				//LRU 加载的页面入栈
				push(ps[i]);
				
				printf("%3d:",ps[i]);
				for(k=0;k<blockCount;k++)
					printf("%3d",pb[k]);
				printf("，缺页中断，内存空间足够，直接加载。\n"); 
			}else{//内存空间不足，采用置换算法 
	  			
	  			//用LRU算法找要被置换的页面 	
				int zhyh = getbottom();  //取栈底，获得要置换出去的页号 
				//要置换的物理内存块号在zhkh中 
				for(k=0;k<blockCount;k++)
					if(pb[k]==zhyh){
						zhkh=k;
						break;
					}						 
				
				printf("%3d:", ps[i]);
				pb[zhkh] = ps[i];
				
				push(ps[i]); 	//LRU,加载页面入栈 
				
				for(k=0;k<blockCount;k++)
					printf("%3d",pb[k]);
				printf("，缺页中断，内存空间不足，置换掉%2d页，再加载。\n",zhyh); 
				 
			}//end else 内存不足 			
		}else{
			printf("%3d:         ，页在内存中，未发生缺页中断，直接访问。\n", ps[i]);
			push(ps[i]); 	//LRU,访问页面入栈 
		}//end else  在内存中找到要访问的页了，未发生缺页中断 
    
	}//end for 
	printf("LRU缺页次数为:%d\n",nopage);   
	printf("LRU缺页率为:%d/%d=%.2f%%\n\n",nopage,pageCount,(float)nopage/pageCount*100);   
     
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
