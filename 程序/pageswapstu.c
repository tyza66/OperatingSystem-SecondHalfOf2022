#include<stdio.h>

//opt�㷨ʵ�֣�ps�����ҳ�����У�pageCountҳ��������blockCount�ڴ��������� 
void OPT(int ps[],int pageCount,int blockCount)
{        
	//�㷨
	 
	//printf("OPTȱҳ����Ϊ:%d\n",nopage);   
	//printf("OPTȱҳ��Ϊ:%d/%d=%.2f%%\n\n",nopage,pageCount,(float)nopage/pageCount*100);   
     
} 

//FIFO�㷨ʵ�֣�ps�����ҳ�����У�pageCountҳ��������blockCount�ڴ��������� 
void FIFO(int ps[],int pageCount,int blockCount)
{        
 	//�㷨
	  
	//printf("FIFOȱҳ����Ϊ:%d\n",nopage);   
	//printf("FIFOȱҳ��Ϊ:%d/%d=%.2f%%\n\n",nopage,pageCount,(float)nopage/pageCount*100);   
     
}

//LRU��������ջʵ�� 
int stack[100];  //����ջ,ջ���Ԫ�ظ������ڽ��̷���������� 
int top=0; //ָջ������һ��Ԫ��

//����ջ����ջ����,�ȴ�ջ��ɾ��Ҫ���Ԫ�أ�Ȼ������ջ�� 
int push(int x)
{
	int i,j;
	if(top<=0){//��ջֱ���� 
		stack[top]=x;
		top++;
	}else{
		for(i=0;i<top;i++)
			if(x == stack[i])
				break;
		if(i<top){//Ҫ��ջ��Ԫ����ջ�У���ɾԪ�أ�����x 
			for(j=i+1;j<top;j++) //Ԫ������ 
				stack[j-1]=stack[j];
			stack[top-1]=x;  //��ջ 
		}else{  //����ջ�У�ֱ����ջ 
			stack[top]=x; 
			top++;
		}		
	}

	return 1;
}

//ȡջ�� 
int getbottom(){
	int x;
	int i;
	x = stack[0];
	for(i=1;i<top;i++)
		stack[i-1]=stack[i];
	top--;
	return x;
}
 
//LRU�㷨ʵ�֣�ps�����ҳ�����У�pageCountҳ��������blockCount�ڴ��������� 
void LRU(int ps[],int pageCount,int blockCount)
{        
 	//�㷨 
 	
	//printf("LRUȱҳ����Ϊ:%d\n",nopage);   
	//printf("LRUȱҳ��Ϊ:%d/%d=%.2f%%\n\n",nopage,pageCount,(float)nopage/pageCount*100);   
     
}

main()
{   
	int pageCount,blockCount,i,ps[100];
	int ch;

	// 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1 -1
    printf("������̷��ʵ�ҳ���������У�-1������:");
	i=0;
	scanf("%d",&ps[i]); 
    while(ps[i]!=-1){
		i++; 
		scanf("%d",&ps[i]);
    }
    pageCount = i;
    
	printf("������̷�����ڴ��������:");   // 3
	scanf("%d",&blockCount);   
	
	i=1;
	while(i){
		printf("��ѡ��ʹ�õ�ҳ���û��㷨��0: OPT, 1: FIFO, 2: LRU, -1: �˳�����");
		scanf("%d",&ch);
		switch(ch){
			case 0: OPT(ps, pageCount, blockCount); break; 
			case 1: FIFO(ps, pageCount, blockCount); break;
			case 2: LRU(ps, pageCount, blockCount); break;
			default: i=0; break;
		} 
	}
}
