#include <stdio.h>

#define N 5
#define M 3
/*N进程数, M资源数*/

/*子函数声明*/                           
void ShowSystemStatus();         //显示当前系统中的进程资源分配状态 
void Banker(int ,int *);          //银行家算法
int SafeCheck();                  //安全检测算法
void ShowMenue();                 //显示菜单 

/*全局变量*/
int Availiable[M]={3,3,2};              //初始状态，系统可用资源向量Availiable                       
int Max[N][M]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};  //各进程对各资源的最大需求量Max矩阵         
int Allocation[N][M]={{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};  //各进程已占有各资源数量Allocation矩阵  
int Need[N][M];     //各进程还需要的资源量Need矩阵       
  
/*主函数*/
int main()
{	
	int i,j;
	int process=0;                           //发出请求的进程号 0 - N-1 
	int decide=0;                            //银行家算法的返回值
	int Request[3]={0,0,0};                  //进程申请的资源向量
		 
	//1.计算Need矩阵 
	for(i=0;i<N;i++)
		for(j=0;j<M;j++)
			Need[i][j] = Max[i][j] - Allocation[i][j];

    //2.循环等待进程请求资源 
    while(1){
    	/* 1) 显示系统当前状态*/
    	ShowSystemStatus();	
    	
    	/* 2)输入进程请求资源*/
    	ShowMenue();	
		scanf("%d",&process);
		if(process==-1){
            //调用安全检测算法进行检测	
	        if(SafeCheck() == 0) 
                 printf("当前状态不安全！\n");
            else
                 printf("当前状态安全！\n");
	    }
	    else if(process>=0 && process<=N-1){
      	    printf("此进程申请各资源(A, B, C)数目，(格式如：1 0 2): ");
      	    scanf("%d%d%d",&Request[0],&Request[1],&Request[2]);
  	  			
		    /* 3)用银行家算法判断是否能够进行分配*/	  
	  	    Banker(process, Request);
        }
        else{
            printf("放弃申请,退出系统！");
			return 0;
        } 
    } //while 1
}
void ShowMenue()
{
    printf("\n系统菜单：\n");
    printf("     0-%2d  发出请求的进程号。\n", N-1);
    printf("     -1    安全算法检测当前状态是否安全。\n");
    printf("     其他  退出系统。\n");
    printf("请输入：");
} 
//显示系统状态 
void ShowSystemStatus()
{
	int i,j; 
	printf("\n此刻系统资源状态：\n");
	printf("         Max      Allocation     Need     Availiable\n");
	printf("      A   B   C   A   B   C   A   B   C   A   B   C\n");
	for(i=0;i<N;i++)
	{
		printf("P%d  ", i);
		for(j=0;j<M;j++)
			printf("%3d ", Max[i][j]);
		for(j=0;j<M;j++)
			printf("%3d ", Allocation[i][j]);
		for(j=0;j<M;j++)
			printf("%3d ", Need[i][j]);
		if(i==0)
			for(j=0;j<M;j++)
				printf("%3d ", Availiable[j]);	
		printf("\n");
	}
}

//银行家算法   p进程号  R请求向量 
void Banker(int p,int *R)
{ 
	int i,j;
	
	/* 1）判断该进程申请资源量是否大于初始时其申明的需求量*/
	//满足继续走，不满足，输出 “申请失败，此进程挂起，原因为：申请的资源量大于其声明的需求量！”，返回 
	printf("RequestP%d(", p); //输出 
	for(i=0;i<M;i++){
 		printf("%d,",R[i]);
    }	
	for(i=0;i<M;i++){		
 		if(R[i] > Need[p][i]){
            printf("\b)>NeedP%d(", p);//输出
	        for(i=0;i<M;i++){
 		        printf("%d,",Need[p][i]);
            }
            printf("\b);\n");	 			  
			printf("申请失败，此进程挂起，原因为：申请的资源量大于其声明的需求量！\n");
			return;
        }
	}
	printf("\b)<=NeedP%d(", p);//输出
	for(i=0;i<M;i++){
 		printf("%d,",Need[p][i]);
    }
	printf("\b);\n");
    	
	/* 2）判断申请的资源是否大于系统可提供的资源总量*/
	//满足继续走，不满足，输出 “申请失败，此进程挂起，原因为：申请的资源中有某种资源大于系统可提供的资源量！”，返回 
	printf("RequestP%d(", p);
	for(i=0;i<M;i++){
 		printf("%d,",R[i]);
    }
	for(j=0;j<M;j++)
	{
		  if(R[j] > Availiable[j]){
          	 printf("\b)>Availiable(");
	         for(i=0;i<M;i++){
 		        printf("%d,",Availiable[i]);
             }
             printf("\b);\n"); 
		     printf("申请失败，此进程挂起，原因为：申请的资源中有某种资源大于系统可提供的资源量！\n");
		     return;
		  } 
	}
	printf("\b)<=Availiable(");
	for(i=0;i<M;i++){
 		printf("%d,",Availiable[i]);
    }
	printf("\b);\n");
	
 	/* 3）试着分配资源*/
	/* 分配（更新资源分配情况）后，再显示下系统新状态*/
 	printf("试着分配资源：\n");
    for(j=0;j<M;j++){
    	Availiable[j] = Availiable[j] - R[j];   //减少系统可用资源 
    	Allocation[p][j] =  Allocation[p][j] + R[j];  //增加该进程已分配
		Need[p][j] = Need[p][j] - R[j];   //更新还需资源数 
    } 
    
	/* 显示系统当前状态*/
	ShowSystemStatus();
	
    // 4）调用安全检测算法进行检测	
    //不安全，恢复原来状态，输出 “申请失败，恢复分配，此进程挂起，原因为：若满足其申请，系统将进入不安全状态！” 
    //安全，输出“申请成功，资源已分配！” 
	if(SafeCheck() == 0){ 
        printf("申请失败，恢复分配，此进程挂起，原因为：若满足其申请，系统将进入不安全状态！\n");
        //恢复原来分配的资源
	    for(j=0;j<M;j++){
	    	Availiable[j] = Availiable[j] + R[j];   //恢复系统可用资源 
	  		Allocation[p][j] =  Allocation[p][j] - R[j];  //增恢复该进程已分配
			Need[p][j] = Need[p][j] + R[j];   //恢复还需资源数 
	    }
    } 
    else
	    printf("申请成功，资源已分配！\n");
}

/* 	算法功能：安全检测算法，实现较复杂，本实验中直接给出了，请仔细阅读 
	输入参数：直接读取的全局变量
	返回值：0 代表不安全    1  代表安全
*/ 
int SafeCheck(){
    int Finish[N]={0,0,0,0,0};           //标记各进程是否安全运行完毕,Finish数组 
	int Work[M]={0,0,0};                 //用于安全检查的工作向量Work 
	int i,j,k,ii,jj;
	
    /* 4）安全检查算法，检查系统是否处于安全状态*/
	for(i=0;i<M;i++){  //置work = Availiable 
	  Work[i] = Availiable[i];
	}

	//4-1打印检测过程标题 
	printf("使用安全检测算法进行安全检测，检测过程如下：\n");
	printf("        Work        Need      Allocation     W+A     Finish\n");
	printf("      A   B   C   A   B   C   A   B   C   A   B   C     \n");
	
	//4-2分配测试 
	while(1){
		 /*4-2-1寻找用此刻系统中没有运行完的进程*/
		for(i=0;i<N;i++){
	 		if(Finish[i]==0){   //没运行完的 
	 			//判断所有资源是否能满足进程i 
				for(j=0;j<M;j++){ 
					if(Need[i][j]>Work[j])
						  break;
				}
				if(j>=M){ //进程i所需资源数现在都能满足
					//打印检测过程 - Work Need Allocation
					printf("P%d  ", i);
					for(k=0;k<M;k++)
						printf("%3d ",Work[k]);
					for(k=0;k<M;k++)
						printf("%3d ",Need[i][k]);
					for(k=0;k<M;k++)
						printf("%3d ",Allocation[i][k]);										 
					
					//分给进程i，让它运行，结束并回收它的资源
					for(k=0;k<M;k++)	 
						Work[k] = Work[k] + Allocation[i][k];		
					Finish[i] = 1;	//置进程i运行完毕。	
					
					//打印检测过程 - Work+Allocation
					for(k=0;k<M;k++)
						printf("%3d ",Work[k]);	
					//打印检测过程 - Finish
					printf("  %3d\n", Finish[i]);	
						
					break;		//本次找到了，跳出for	
				}//end if j>=M 
			}//end if 
	 	}//end for 
	 	if(i>=N){	//没找到，则检查是否全运行完了 
		 	for(ii=0;ii<N;ii++)
		 		if(Finish[ii] != 1)
		 			break;	//存在没完成的进程
			if(ii<N){  //存在没完成的进程,处理 - 恢复现场 

				//返回拒绝分配原因
				return 0; //失败
			}else{ //都运行完了，分配资源成功 
				break;  //跳出while循环。 
			} 
		}//end if		
	}//end while
	return 1;  //成功
}
