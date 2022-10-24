#include <stdio.h>

#define N 5
#define M 3
/*N������, M��Դ��*/

/*�Ӻ�������*/                           
void ShowSystemStatus();         //��ʾ��ǰϵͳ�еĽ�����Դ����״̬ 
void Banker(int ,int *);          //���м��㷨
int SafeCheck();                  //��ȫ����㷨
void ShowMenue();                 //��ʾ�˵� 

/*ȫ�ֱ���*/
int Availiable[M]={3,3,2};              //��ʼ״̬��ϵͳ������Դ����Availiable                       
int Max[N][M]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};  //�����̶Ը���Դ�����������Max����         
int Allocation[N][M]={{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};  //��������ռ�и���Դ����Allocation����  
int Need[N][M];     //�����̻���Ҫ����Դ��Need����       
  
/*������*/
int main()
{	
	int i,j;
	int process=0;                           //��������Ľ��̺� 0 - N-1 
	int decide=0;                            //���м��㷨�ķ���ֵ
	int Request[3]={0,0,0};                  //�����������Դ����
		 
	//1.����Need���� 
	for(i=0;i<N;i++)
		for(j=0;j<M;j++)
			Need[i][j] = Max[i][j] - Allocation[i][j];

    //2.ѭ���ȴ�����������Դ 
    while(1){
    	/* 1) ��ʾϵͳ��ǰ״̬*/
    	ShowSystemStatus();	
    	
    	/* 2)�������������Դ*/
    	ShowMenue();	
		scanf("%d",&process);
		if(process==-1){
            //���ð�ȫ����㷨���м��	
	        if(SafeCheck() == 0) 
                 printf("��ǰ״̬����ȫ��\n");
            else
                 printf("��ǰ״̬��ȫ��\n");
	    }
	    else if(process>=0 && process<=N-1){
      	    printf("�˽����������Դ(A, B, C)��Ŀ��(��ʽ�磺1 0 2): ");
      	    scanf("%d%d%d",&Request[0],&Request[1],&Request[2]);
  	  			
		    /* 3)�����м��㷨�ж��Ƿ��ܹ����з���*/	  
	  	    Banker(process, Request);
        }
        else{
            printf("��������,�˳�ϵͳ��");
			return 0;
        } 
    } //while 1
}
void ShowMenue()
{
    printf("\nϵͳ�˵���\n");
    printf("     0-%2d  ��������Ľ��̺š�\n", N-1);
    printf("     -1    ��ȫ�㷨��⵱ǰ״̬�Ƿ�ȫ��\n");
    printf("     ����  �˳�ϵͳ��\n");
    printf("�����룺");
} 
//��ʾϵͳ״̬ 
void ShowSystemStatus()
{
	int i,j; 
	printf("\n�˿�ϵͳ��Դ״̬��\n");
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

//���м��㷨   p���̺�  R�������� 
void Banker(int p,int *R)
{ 
	int i,j;
	
	/* 1���жϸý���������Դ���Ƿ���ڳ�ʼʱ��������������*/
	//��������ߣ������㣬��� ������ʧ�ܣ��˽��̹���ԭ��Ϊ���������Դ������������������������������ 
	printf("RequestP%d(", p); //��� 
	for(i=0;i<M;i++){
 		printf("%d,",R[i]);
    }	
	for(i=0;i<M;i++){		
 		if(R[i] > Need[p][i]){
            printf("\b)>NeedP%d(", p);//���
	        for(i=0;i<M;i++){
 		        printf("%d,",Need[p][i]);
            }
            printf("\b);\n");	 			  
			printf("����ʧ�ܣ��˽��̹���ԭ��Ϊ���������Դ����������������������\n");
			return;
        }
	}
	printf("\b)<=NeedP%d(", p);//���
	for(i=0;i<M;i++){
 		printf("%d,",Need[p][i]);
    }
	printf("\b);\n");
    	
	/* 2���ж��������Դ�Ƿ����ϵͳ���ṩ����Դ����*/
	//��������ߣ������㣬��� ������ʧ�ܣ��˽��̹���ԭ��Ϊ���������Դ����ĳ����Դ����ϵͳ���ṩ����Դ������������ 
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
		     printf("����ʧ�ܣ��˽��̹���ԭ��Ϊ���������Դ����ĳ����Դ����ϵͳ���ṩ����Դ����\n");
		     return;
		  } 
	}
	printf("\b)<=Availiable(");
	for(i=0;i<M;i++){
 		printf("%d,",Availiable[i]);
    }
	printf("\b);\n");
	
 	/* 3�����ŷ�����Դ*/
	/* ���䣨������Դ���������������ʾ��ϵͳ��״̬*/
 	printf("���ŷ�����Դ��\n");
    for(j=0;j<M;j++){
    	Availiable[j] = Availiable[j] - R[j];   //����ϵͳ������Դ 
    	Allocation[p][j] =  Allocation[p][j] + R[j];  //���Ӹý����ѷ���
		Need[p][j] = Need[p][j] - R[j];   //���»�����Դ�� 
    } 
    
	/* ��ʾϵͳ��ǰ״̬*/
	ShowSystemStatus();
	
    // 4�����ð�ȫ����㷨���м��	
    //����ȫ���ָ�ԭ��״̬����� ������ʧ�ܣ��ָ����䣬�˽��̹���ԭ��Ϊ�������������룬ϵͳ�����벻��ȫ״̬���� 
    //��ȫ�����������ɹ�����Դ�ѷ��䣡�� 
	if(SafeCheck() == 0){ 
        printf("����ʧ�ܣ��ָ����䣬�˽��̹���ԭ��Ϊ�������������룬ϵͳ�����벻��ȫ״̬��\n");
        //�ָ�ԭ���������Դ
	    for(j=0;j<M;j++){
	    	Availiable[j] = Availiable[j] + R[j];   //�ָ�ϵͳ������Դ 
	  		Allocation[p][j] =  Allocation[p][j] - R[j];  //���ָ��ý����ѷ���
			Need[p][j] = Need[p][j] + R[j];   //�ָ�������Դ�� 
	    }
    } 
    else
	    printf("����ɹ�����Դ�ѷ��䣡\n");
}

/* 	�㷨���ܣ���ȫ����㷨��ʵ�ֽϸ��ӣ���ʵ����ֱ�Ӹ����ˣ�����ϸ�Ķ� 
	���������ֱ�Ӷ�ȡ��ȫ�ֱ���
	����ֵ��0 ������ȫ    1  ����ȫ
*/ 
int SafeCheck(){
    int Finish[N]={0,0,0,0,0};           //��Ǹ������Ƿ�ȫ�������,Finish���� 
	int Work[M]={0,0,0};                 //���ڰ�ȫ���Ĺ�������Work 
	int i,j,k,ii,jj;
	
    /* 4����ȫ����㷨�����ϵͳ�Ƿ��ڰ�ȫ״̬*/
	for(i=0;i<M;i++){  //��work = Availiable 
	  Work[i] = Availiable[i];
	}

	//4-1��ӡ�����̱��� 
	printf("ʹ�ð�ȫ����㷨���а�ȫ��⣬���������£�\n");
	printf("        Work        Need      Allocation     W+A     Finish\n");
	printf("      A   B   C   A   B   C   A   B   C   A   B   C     \n");
	
	//4-2������� 
	while(1){
		 /*4-2-1Ѱ���ô˿�ϵͳ��û��������Ľ���*/
		for(i=0;i<N;i++){
	 		if(Finish[i]==0){   //û������� 
	 			//�ж�������Դ�Ƿ����������i 
				for(j=0;j<M;j++){ 
					if(Need[i][j]>Work[j])
						  break;
				}
				if(j>=M){ //����i������Դ�����ڶ�������
					//��ӡ������ - Work Need Allocation
					printf("P%d  ", i);
					for(k=0;k<M;k++)
						printf("%3d ",Work[k]);
					for(k=0;k<M;k++)
						printf("%3d ",Need[i][k]);
					for(k=0;k<M;k++)
						printf("%3d ",Allocation[i][k]);										 
					
					//�ָ�����i���������У�����������������Դ
					for(k=0;k<M;k++)	 
						Work[k] = Work[k] + Allocation[i][k];		
					Finish[i] = 1;	//�ý���i������ϡ�	
					
					//��ӡ������ - Work+Allocation
					for(k=0;k<M;k++)
						printf("%3d ",Work[k]);	
					//��ӡ������ - Finish
					printf("  %3d\n", Finish[i]);	
						
					break;		//�����ҵ��ˣ�����for	
				}//end if j>=M 
			}//end if 
	 	}//end for 
	 	if(i>=N){	//û�ҵ��������Ƿ�ȫ�������� 
		 	for(ii=0;ii<N;ii++)
		 		if(Finish[ii] != 1)
		 			break;	//����û��ɵĽ���
			if(ii<N){  //����û��ɵĽ���,���� - �ָ��ֳ� 

				//���ؾܾ�����ԭ��
				return 0; //ʧ��
			}else{ //���������ˣ�������Դ�ɹ� 
				break;  //����whileѭ���� 
			} 
		}//end if		
	}//end while
	return 1;  //�ɹ�
}
