#include<stdio.h>

//FCFS�㷨ʵ�֣�ts�����ŵ����У�trackCount�ŵ�������currTrack��ǰ��ͷ���ڴŵ� 
void FCFS(int ts[],int trackCount, int currTrack)
{        
 	int i,mv; 
	int totalMoveTrack = 0; //���ƶ��ŵ��� 
	printf("0�������ȷ�����̵����㷨(FCFS)\n"); 
	
	printf("��%d�Ŵŵ���ʼ\n", currTrack); 
	printf("�����ʵ���һ���ŵ���\t�ƶ�����(�ŵ���)\n"); 
	
	for(i=0;i<trackCount;i++){   //���ŵ��������η���ÿ���ŵ� 
		mv = abs(currTrack - ts[i]);	//�����ƶ����� 
		
		printf("%d\t\t\t%d\n", ts[i], mv);	//������� 
		
		totalMoveTrack += mv; //�������� 
		currTrack = ts[i];	//������ŵ�Ϊ��ǰ�ŵ�����ʱ���Է�������ŵ� 
	}//end for
	   
	printf("ƽ��Ѱ������:%d/%d=%.2f\n\n", totalMoveTrack, trackCount, (float)totalMoveTrack/trackCount);     
}

//SSTF�㷨ʵ�֣�ts�����ŵ����У�trackCount�ŵ�������currTrack��ǰ��ͷ���ڴŵ� 
void SSTF(int ts[],int trackCount, int currTrack)
{        
 	//���ڴ˴��������ģ��SSTF�㷨�� 
}

//SCAN�㷨ʵ�֣�ts�����ŵ����У�trackCount�ŵ�������currTrack��ǰ��ͷ���ڴŵ� 
void SCAN(int ts[],int trackCount, int currTrack)
{        
 	//���ڴ˴��������ģ��SCAN�㷨��  
}

//CSCAN�㷨ʵ�֣�ts�����ŵ����У�trackCount�ŵ�������currTrack��ǰ��ͷ���ڴŵ� 
void CSCAN(int ts[],int trackCount, int currTrack)
{        
 	//���ڴ˴��������ģ��CSCAN�㷨�� 
}

main()
{   
	int i, ts[100];
	int ch, trackCount;
	int currTrack; 

	//�������ӣ��ŵ����У�55 58 39 18 90 160 150 38 184 -1����ǰ�ŵ���100������ 
	//ϰ������2���ŵ����У�23 376 205 132 19 61 190 398 29 4 18 40 -1����ǰ�ŵ���100���ݼ� 
    printf("������̷��ʵĴŵ����У�-1������:");
	i=0;
	scanf("%d",&ts[i]); 
    while(ts[i]!=-1){
		i++; 
		scanf("%d",&ts[i]);
    }
    trackCount = i;  
    
    printf("�������ͷ���ڵĴŵ�:");
	scanf("%d",&currTrack); 
	
	i=1;
	while(i){
		printf("��ѡ��ʹ�õĵ����㷨��0: FCFS, 1: SSTF, 2: SCAN, 3: CSCAN, -1: �˳�����");
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
