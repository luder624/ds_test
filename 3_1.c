#include <stdio.h>
#include <stdlib.h>
FILE *fin,*fout;
int map[1000][1000];
int main(){
	fin=fopen("input_7-3.txt","r");
	fout=fopen("output.txt","w");
	int node_count,work_count,i,j,node1,node2,stop=0,ans[1000]={0},top=-1;
	fscanf(fin,"%d %d",&node_count,&work_count);
	for(i=0;i<work_count;i++){		//build map 
		fscanf(fin,"%d %d",&node1,&node2);
		
		if(!map[node1-1][node2-1]){	 
			map[node2-1][node2-1]++;
			map[node1-1][node2-1]=1;
		}
	}
	while(!stop){
		stop=1;
		for(i=0;i<node_count;i++){
			if(map[i][i]==0){		//relation map中間那斜排都會是0 
				stop=0;			
				ans[++top]=i+1;
				for(j=0;j<node_count;j++){
					if(map[i][j]&&i!=j){
						map[j][j]--;
						map[i][j] = 0;
					}
				}
				map[i][i]=-1;
				break;
			}
		}
	}
	if(top!=node_count-1)
		printf("not exist");
	else{
		for(i=0;i<node_count;i++)
			printf("%d ",ans[i]);
			fprintf(fout,"%d ",ans[i]);
	}
	return 0;
}
