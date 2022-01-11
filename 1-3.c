#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
FILE *fin;
typedef struct Node{
	int area;
	int num;
	int c;
	struct Node *beside;
}node;
typedef struct Color{
	int cost;
	int amount;
	struct Color *next;
}color;
node map[5000],*head=NULL;
color col[261],*chead=NULL;
long long int min=LLONG_MAX,ans=0;
int k=0;
void run(int l,int n){
	int i;
	if(k==n){
		if(ans<min){
			min=ans;
		}
		return;
	}
	for(i=1;i<=l;i++){
		if(col[i].amount<map[k].area){
			continue;
		}
		node *temp=map[k].beside;
		for(;temp;temp=temp->beside){
			if(temp->c==i){
				continue;
			}
		}
		col[i].amount-=map[k].area;
		map[k].c=i;
		ans+=col[i].cost*map[k].area;
		if(ans>min){
			ans-=col[i].cost*map[k].area;
			map[k].c=0;
			col[i].amount+=map[k].area;
			return;
		}
		else{
			k++;
			run(l,n);
			k--;
			ans-=col[i].cost*map[k].area;
			map[k].c=0;
			col[i].amount+=map[k].area;
		}
		
	}
}
int main(){
	fin=fopen("input_3.txt","r");
	int n,e,l,u,v,i,minarea=INT_MAX;
	char s[3];
	fscanf(fin,"%d %d %d",&n,&e,&l);
	for(i=0;i<n;i++){
		fscanf(fin,"%d",&map[i].area);
		if(minarea>map[i].area){
			minarea=map[i].area;
		}
		map[i].beside=NULL;
	}
	for(i=0;i<e;i++){
		fscanf(fin,"%d %d",&u,&v);
		if(u>v){
			u=u+v;
			v=u-v;
			u=u-v;
		}
		node *temp=malloc(sizeof(node));
		temp->num=u;
		temp->beside=map[v].beside;
		map[v].beside=temp;
	}
	for(i=0;i<l;i++){
		color *temp=malloc(sizeof(color)),*t=chead,*pre=NULL;
		fscanf(fin,"%s %d %d",s,&temp->amount,&temp->cost);
		if(temp->amount<minarea){
			l--;
			i--;
			continue;
		}
		temp->next=NULL;
		if(!chead){
			chead=temp;
			continue;
		}
		while(t){
			if(temp->cost>t->cost){
				pre=t;
				t=t->next;
			}
			else
				break;
		}
		temp->next=t;
		if(pre)
			pre->next=temp;
		else
			chead=temp;
	}
	for(i=1;chead;chead=chead->next){
		col[i].amount=chead->amount;
		col[i++].cost=chead->cost;
	}
	run(l,n);
	printf("%lld",min);
	return 0;
}
