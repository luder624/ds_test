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
int n,tot;				//n : order 數 ， tot : 可完成工作總數 

int check(){			//當全部的state都不為 0 -> return 0 -> while迴圈結束 
	int i;				//當任一state為 0 -> return 1 -> while()
	for(i=0;i<n;i++)
		if(oc[i].state == 0)
			return 1;
	return 0;
}

void overcook(){
	
	int i,index=0,nowtime;
	
	while(check()){	
		for(i=0;i<n;i++){
			if(oc[i].state ==0 && oc[i].arrive + oc[i].cook <= oc[i].end){	// 未完成  && arrive time + cook time < deadline 
				index = i ;													//若 i 符合條件就往下檢查。 
				break;
			}
		}
		
		for(i=0 ;i<n;i++){
			if(oc[i].arrive + oc[i].cook > oc[i].end && oc[i].state != 1){			//	arrive time + cook time < deadline
				oc[i].state = -1; 													//	無法被完成 ， state變 -1。 
			}
			
			if(oc[i].state != -1&& oc[i].state != 1){								//state不是無法完成，但也還沒決定要做 
				
				if(oc[i].arrive+oc[i].cook < oc[index].arrive+oc[index].cook){		//若 i 的 arrive time + cook time比 index 的短 
					index = i;														//index更新為 i 
				}
				
				if(oc[index].arrive+oc[index].cook == oc[i].arrive+oc[i].cook && oc[index].end > oc[i].end){ 	//若 i 的 arrive time + cook time 和 index 的一樣長  
					index = i;																					//但i比index早結束 
				}																								//index更新為 i 
			}
		}
		
		nowtime = oc[index].arrive+oc[index].cook; //現在的時間為 index 的 arrive + cook 時間 
		
		for(i=0;i<n;i++){
			if(nowtime > oc[i].arrive){		// arrive需時時跟著 nowtime更新 
				oc[i].arrive=nowtime;		//下一筆訂單開始執行的時間
			}
		}
		
		oc[index].state = 1;				//已做完 
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
			oc[i].state = 0;		//初始 state為 0 
		}
		overcook();
		for(i=0;i<n;i++){
			if(oc[i].state == 1){	//state 為 1 就是要做的 
				tot++;
			}
		}
		printf("%d",tot);
	}
	fclose(fp);
	return 0;
} 
