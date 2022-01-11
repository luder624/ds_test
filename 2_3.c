#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int adir[9][2]={{0,0},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
struct MAP{
	int high;
	int cost;
	int chart[8];
	int use;
};
void initial(struct MAP map[100][100],int n){
	int i=0,j=0;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			map[i][j].cost=INT_MAX;
			map[i][j].use=0;
		}
	}
}
int k=0;
void f(int* a,int n,int *t,int cost[6][6],int *mincost){
	int i=0,sum=0;
	if(k==n){
		sum=cost[0][a[i]];
		for(i=0;i<n-1;i++){
			sum+=cost[a[i]][a[i+1]];
		}
		if(sum<*mincost){
			*mincost=sum;
		}
		t[a[--k]-1]=0;
		return;
	}
	for(i=0;i<n;i++){
		if(t[i]==0){
			t[i]++;
			a[k++]=i+1;
			f(a,n,t,cost,mincost);
		}	
	}
	if(k>0){
		t[a[--k]-1]=0;
	}
	return;
}
void printchart(struct MAP map[100][100],int n){
	int i=0,j=0,I=0;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			for(I=1;I<=8;I++){
				if(i+adir[I][0]<0 || i+adir[I][0]>=n || j+adir[I][1]<0 || j+adir[I][1]>=n){
					map[i][j].chart[I-1]=-1;
					continue;
				}
				map[i][j].chart[I-1]=abs(map[i][j].high-map[i+adir[I][0]][j+adir[I][1]].high);
			} 
		}
	}
}
void main(){
	FILE *fin=fopen("input_6-6.txt","r");
	FILE *fout=fopen("output.txt","w");
	int time,T=0,d,n,sp[2],ep[2],p[6][2],i,ans=INT_MAX,j,now[2],onecost=0,mincost[6][6],top=0,I,J,l,stop=0;
	struct MAP map[100][100];
	
		fscanf(fin,"%d %d",&d,&n);
		for(i=0;i<=d;i++){
			fscanf(fin,"%d %d",&p[i][0],&p[i][1]);
		}
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				fscanf(fin,"%d",&map[i][j].high);
			}
		}
		initial(map,n);
		ans=INT_MAX;
		for(I=0;I<=d-1;I++){
			for(J=I+1;J<=d;J++){
				initial(map,n);
				onecost=0;
				now[0]=sp[0]=p[I][0];
				now[1]=sp[1]=p[I][1];
				ep[0]=p[J][0];
				ep[1]=p[J][1];
				printchart(map,n);
				map[sp[0]][sp[1]].cost=0;
				map[sp[0]][sp[1]].use=1;
				while(map[ep[0]][ep[1]].cost==INT_MAX){
					for(i=0;i<n;i++){
						for(j=0;j<n;j++){
							if(map[i][j].use){
								for(l=0;l<8;l++){
									if(map[i][j].chart[l]!=-1&&onecost==map[i][j].cost+map[i][j].chart[l]){
										if(map[i+adir[l+1][0]][j+adir[l+1][1]].cost>onecost){
											stop=1;
											map[i+adir[l+1][0]][j+adir[l+1][1]].cost=onecost;
											map[i+adir[l+1][0]][j+adir[l+1][1]].use=1;
										}
									}
								}	
							}
						}
					}
					if(stop){
						stop=0;
						continue;
					}
					onecost++;
				}
				mincost[J][I]=mincost[I][J]=map[ep[0]][ep[1]].cost;
			}
		}
		int list[5]={},a[5]={};
		f(a,d,list,mincost,&ans);
		fprintf(fout,"cost:%d\n",ans);
		k=0;
		time--;
	 
	fclose(fin);
	fclose(fout);
}
