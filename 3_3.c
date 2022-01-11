# include <stdio.h>
# include <stdlib.h>
struct Overcook{
	int id;
	int arrive;
	int end;
	int cook;
	int state;
};
struct Overcook* oc;
int n,tot;				//n : order �� �A tot : �i�����u�@�`�� 

int check(){			//�������state������ 0 -> return 0 -> while�j�鵲�� 
	int i;				//����@state�� 0 -> return 1 -> while()
	for(i=0;i<n;i++)
		if(oc[i].state == 0)
			return 1;
	return 0;
}

void overcook(){
	
	int i,index=0,nowtime;
	
	while(check()){	
		for(i=0;i<n;i++){
			if(oc[i].state ==0 && oc[i].arrive + oc[i].cook <= oc[i].end){	// ������  && arrive time + cook time < deadline 
				index = i ;													//�Y i �ŦX����N���U�ˬd�C 
				break;
			}
		}
		
		for(i=0 ;i<n;i++){
			if(oc[i].arrive + oc[i].cook > oc[i].end && oc[i].state != 1){			//	arrive time + cook time < deadline
				oc[i].state = -1; 													//	�L�k�Q���� �A state�� -1�C 
			}
			
			if(oc[i].state != -1&& oc[i].state != 1){								//state���O�L�k�����A���]�٨S�M�w�n�� 
				
				if(oc[i].arrive+oc[i].cook < oc[index].arrive+oc[index].cook){		//�Y i �� arrive time + cook time�� index ���u 
					index = i;														//index��s�� i 
				}
				
				if(oc[index].arrive+oc[index].cook == oc[i].arrive+oc[i].cook && oc[index].end > oc[i].end){ 	//�Y i �� arrive time + cook time �M index ���@�˪�  
					index = i;																					//��i��index������ 
				}																								//index��s�� i 
			}
		}
		
		nowtime = oc[index].arrive+oc[index].cook; //�{�b���ɶ��� index �� arrive + cook �ɶ� 
		
		for(i=0;i<n;i++){
			if(nowtime > oc[i].arrive){		// arrive�ݮɮɸ�� nowtime��s 
				oc[i].arrive=nowtime;		//�U�@���q��}�l���檺�ɶ�
			}
		}
		
		oc[index].state = 1;				//�w���� 
	}
}

int main(){
	FILE* fp;
	fp =fopen("input_9-1.txt","r");
	if(fp==NULL){
		printf("open file failed\n");
	}
	else{
		int i,num,id,atime,etime,ctime;
		fscanf(fp,"%d\n",&num);
		oc = (struct Overcook*)malloc(sizeof(struct Overcook)*num);
		n=num;
		tot=0;
		
		for(i=0;i<num;i++){
			fscanf(fp,"%d %d %d %d\n",&id,&atime,&etime,&ctime);
			oc[i].id = id;
			oc[i].arrive = atime;
			oc[i].end = etime;
			oc[i].cook = ctime;
			oc[i].state = 0;		//��l state�� 0 
		}
		overcook();
		for(i=0;i<n;i++){
			if(oc[i].state == 1){	//state �� 1 �N�O�n���� 
				tot++;
			}
		}
		printf("%d",tot);
	}
	fclose(fp);
	return 0;
} 
