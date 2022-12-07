#include<stdio.h>

//opt�㷨ʵ�֣�ps�����ҳ�����У�pageCountҳ��������blockCount�ڴ��������� 
void OPT(int ps[],int pageCount,int blockCount)
{        
 	int i; 
	int pb[100];  //�����ڴ棬 blockCountΪ���� 
	int pages=0;  //�ڴ��е�ҳ���� 
	int zhkh=0;
	int j,k,l;
	int nopage=0;  //ȱҳ���� 
	
	printf("0������û��㷨(OPT)\n"); 	
	
	for(i=0;i<blockCount;i++)//��ʼ�ڴ���-1����� 
		pb[i]=-1; 
		
	for(i=0;i<pageCount;i++){   //��ҳ����������ѭ����ÿ��ҳ�� 
		
		//1.�������ڴ�����Ҫ���ʵ�ҳ 
		for(j=0;j<blockCount;j++){
			if(pb[j]==ps[i])//�ҵ���
				break; 
		}
		if(j>=blockCount){//���ڴ���û�ҵ�Ҫ���ʵ�ҳ��ȱҳ�ж� 
			nopage++;	//ȱҳ�ж���ͳ�� 
			 
			if(pages<blockCount){//�����ڴ�ռ仹�㹻 
				pb[zhkh]=ps[i];  
				zhkh = (zhkh+1) % blockCount; 	//��ʼ����ѭ���� 
				pages++;  //��ռ��ҳ�� 
				printf("%3d:",ps[i]);
				for(k=0;k<blockCount;k++)
					printf("%3d",pb[k]);
				printf("��ȱҳ�жϣ��ڴ�ռ��㹻��ֱ�Ӽ��ء�\n"); 
			}else{//�ڴ�ռ䲻�㣬�����û��㷨 
	  			
	  			//��OPT�㷨��Ҫ���û���ҳ�� 
	  			int fwwz = -1;  //��¼�ڴ�ҳ����λ����Զ��ҳ ��zhkh��¼�±� 
				for(k=0;k<blockCount;k++){
					for(l=i+1;l<pageCount;l++)//����ҷ��ʵ� 
						if(pb[k]==ps[l])	
							break;
					if(l>fwwz){
						fwwz = l; 	//��¼����λ�� 
						zhkh = k;								
					}						
				}//end for
				
				//Ҫ�û��������ڴ�����zhkh�� 
				int tzhy;
				printf("%3d:",ps[i]);
				tzhy = pb[zhkh];  //������û���ҳ 
				pb[zhkh] = ps[i];
				for(k=0;k<blockCount;k++)
					printf("%3d",pb[k]);
				printf("��ȱҳ�жϣ��ڴ�ռ䲻�㣬�û���%2dҳ���ټ��ء�\n",tzhy); 
				 
			}//end else �ڴ治�� 			
		}else{
			printf("%3d:         ��ҳ���ڴ��У�δ����ȱҳ�жϣ�ֱ�ӷ��ʡ�\n", ps[i]);
		}//end else  ���ڴ����ҵ�Ҫ���ʵ�ҳ�ˣ�δ����ȱҳ�ж� 
    
	}//end for 
	printf("OPTȱҳ����Ϊ:%d\n",nopage);   
	printf("OPTȱҳ��Ϊ:%d/%d=%.2f%%\n\n",nopage,pageCount,(float)nopage/pageCount*100);   
     
} 

//FIFO�㷨ʵ�֣�ps�����ҳ�����У�pageCountҳ��������blockCount�ڴ��������� 
void FIFO(int ps[],int pageCount,int blockCount)
{        
 	int i; 
	int pb[100];  //�����ڴ棬 blockCountΪ���� 
	int pages=0;  //�ڴ��е�ҳ���� 
	int zhkh=0;
	int j,k,l;
	int nopage=0;  //ȱҳ���� 
	
	printf("1���Ƚ��ȳ��û��㷨(FIFO)\n"); 
	
	for(i=0;i<blockCount;i++)//��ʼ�ڴ���-1����� 
		pb[i]=-1; 
		
	for(i=0;i<pageCount;i++){   //��ҳ����������ѭ����ÿ��ҳ�� 
		
		//1.�������ڴ�����Ҫ���ʵ�ҳ 
		for(j=0;j<blockCount;j++){
			if(pb[j]==ps[i])//�ҵ���
				break; 
		}
		if(j>=blockCount){//���ڴ���û�ҵ�Ҫ���ʵ�ҳ��ȱҳ�ж� 
			nopage++;	//ȱҳ�ж���ͳ�� 
			 
			if(pages<blockCount){//�����ڴ�ռ仹�㹻 
				pb[zhkh]=ps[i];  
				zhkh = (zhkh+1) % blockCount; 	//��ʼ����ѭ���� 
				pages++;  //��ռ��ҳ�� 
				printf("%3d:",ps[i]);
				for(k=0;k<blockCount;k++)
					printf("%3d",pb[k]);
				printf("��ȱҳ�жϣ��ڴ�ռ��㹻��ֱ�Ӽ��ء�\n"); 
			}else{//�ڴ�ռ䲻�㣬�����û��㷨 
	  			
	  			//��FIFO�㷨��Ҫ���û���ҳ�� 	
				//Ҫ�û��������ڴ�����zhkh��
				int tzhy; 
				printf("%3d:",ps[i]);
				tzhy =  pb[zhkh]; //�ݴ�Ҫ�û�����ҳ 
				pb[zhkh] = ps[i];
				zhkh = (zhkh+1) % blockCount; 	//FIFOѭ��λ��ָ�뼴�� 
				for(k=0;k<blockCount;k++)
					printf("%3d",pb[k]);
				printf("��ȱҳ�жϣ��ڴ�ռ䲻�㣬�û���%2dҳ���ټ��ء�\n",tzhy); 
				 
			}//end else �ڴ治�� 			
		}else{
			printf("%3d:         ��ҳ���ڴ��У�δ����ȱҳ�жϣ�ֱ�ӷ��ʡ�\n", ps[i]);
		}//end else  ���ڴ����ҵ�Ҫ���ʵ�ҳ�ˣ�δ����ȱҳ�ж� 
    
	}//end for 
	printf("FIFOȱҳ����Ϊ:%d\n",nopage);   
	printf("FIFOȱҳ��Ϊ:%d/%d=%.2f%%\n\n",nopage,pageCount,(float)nopage/pageCount*100);   
     
}

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
 	int i; 
	int pb[100];  //�����ڴ棬 blockCountΪ���� 
	int pages=0;  //�ڴ��е�ҳ���� 
	int zhkh=0;
	int j,k,l;
	int nopage=0;  //ȱҳ���� 

	
	printf("2��������δʹ���û��㷨(LRU)\n"); 
	
	for(i=0;i<blockCount;i++)//��ʼ�ڴ���-1����� 
		pb[i]=-1; 
		
	for(i=0;i<pageCount;i++){   //��ҳ����������ѭ����ÿ��ҳ�� 
		
		//1.�������ڴ�����Ҫ���ʵ�ҳ 
		for(j=0;j<blockCount;j++){
			if(pb[j]==ps[i])//�ҵ���
				break; 
		}
		if(j>=blockCount){//���ڴ���û�ҵ�Ҫ���ʵ�ҳ��ȱҳ�ж� 
			nopage++;	//ȱҳ�ж���ͳ�� 
			 
			if(pages<blockCount){//�����ڴ�ռ仹�㹻 
				pb[zhkh]=ps[i];  
				zhkh = (zhkh+1) % blockCount; 	//��ʼ����ѭ���� 
				pages++;  //��ռ��ҳ�� 
				
				//LRU ���ص�ҳ����ջ
				push(ps[i]);
				
				printf("%3d:",ps[i]);
				for(k=0;k<blockCount;k++)
					printf("%3d",pb[k]);
				printf("��ȱҳ�жϣ��ڴ�ռ��㹻��ֱ�Ӽ��ء�\n"); 
			}else{//�ڴ�ռ䲻�㣬�����û��㷨 
	  			
	  			//��LRU�㷨��Ҫ���û���ҳ�� 	
				int zhyh = getbottom();  //ȡջ�ף����Ҫ�û���ȥ��ҳ�� 
				//Ҫ�û��������ڴ�����zhkh�� 
				for(k=0;k<blockCount;k++)
					if(pb[k]==zhyh){
						zhkh=k;
						break;
					}						 
				
				printf("%3d:", ps[i]);
				pb[zhkh] = ps[i];
				
				push(ps[i]); 	//LRU,����ҳ����ջ 
				
				for(k=0;k<blockCount;k++)
					printf("%3d",pb[k]);
				printf("��ȱҳ�жϣ��ڴ�ռ䲻�㣬�û���%2dҳ���ټ��ء�\n",zhyh); 
				 
			}//end else �ڴ治�� 			
		}else{
			printf("%3d:         ��ҳ���ڴ��У�δ����ȱҳ�жϣ�ֱ�ӷ��ʡ�\n", ps[i]);
			push(ps[i]); 	//LRU,����ҳ����ջ 
		}//end else  ���ڴ����ҵ�Ҫ���ʵ�ҳ�ˣ�δ����ȱҳ�ж� 
    
	}//end for 
	printf("LRUȱҳ����Ϊ:%d\n",nopage);   
	printf("LRUȱҳ��Ϊ:%d/%d=%.2f%%\n\n",nopage,pageCount,(float)nopage/pageCount*100);   
     
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
