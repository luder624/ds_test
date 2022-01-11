# include <stdio.h>
# include <stdlib.h>
typedef struct listNode *listPointer;
typedef struct listNode{
	int data;
	listPointer link;
}listNode;
struct Array{
	listPointer Node;
};
listPointer root;
int tot;
void rev(int group){
	if(group <=1)
		return;
	else if(group >= tot)
		group = tot;
	int x=tot/group,y=group,i,j,b=0;
	if(tot % group != 0)
		x+=1;
	struct Array** array = calloc(x,sizeof(struct Array*));
	listPointer node = root;
	
	for(i=0;i<x;i++){
		array[i] = calloc(y,sizeof(struct Array));
	}
	
	for(i = 0 ;i < x ;i++){
		for(j = 0 ;j < y ;j++){
			array[i][j].Node = node;
			if(node->link)
				node = node->link;
			else{	//node無link 時 
				b=1;
				break;
			}
		}
		if(b)
			break;
	}
	
	root = array[0][y-1].Node;	//x 和 y均為長度 ，在使用時要-1 
	node = root;
	for(i=0;i<x;i++){
		for(j = y-1;j>=0;j--){
			if(!array[i][j].Node){//遇到空的就跳過並繼續 
				continue;
			}
			else{
				node->link = array[i][j].Node;
				node = node->link;
			}
		}
	}
	node->link = NULL; //尾端要接null 
}

void ins(int index ,int num){
	if(index > tot || index < 0)
		return;
	else{
		listPointer newnode = (listPointer)malloc(sizeof(listNode));
		newnode->data = num;
		if(index==0){
			newnode->link = root;
			root = newnode;
		}
		else{
			int i;
			listPointer node = root;
			listPointer lastnode =NULL;
			for(i=0;i<index;i++){
				lastnode = node;
				node = node->link;
			}
			lastnode->link = newnode;
			newnode->link = node;
		}
		tot++;
	}
}
void del(int index){
	//printf("tot=%d\n",tot);
	if(index <= 0 || index > tot){
		return;
	}
	listPointer node = root;
	if(index == 1){
		root = node->link;
		free(node);
		tot--;
		return;
	}
	listPointer lastnode = NULL;
	int i;
	for(i = 0 ;i<index-1;i++){
		if(node->link){
			lastnode = node;
			node = node->link;
		}
	}
	lastnode->link = node->link;
	tot--;
	free(node);
}
void show(void){
	listPointer node = root;
	while(node){
		printf("%d ",node->data);
		node = node->link;
	}
	printf("\n");
}
void add(int num){
	if(root == NULL){
		root=(listPointer)malloc(sizeof(listNode));
		root->data = num;
		root->link = NULL;
	}
	else{
		listPointer node = root;
		listPointer newnode = (listPointer)malloc(sizeof(listNode));
		newnode->data=num;
		newnode->link=NULL;
		while(node->link){
			node=node->link;
		}
		node->link = newnode;
	}
	tot++;
}
int main(){
	FILE *fp;
	fp = fopen("input_4-5.txt","r");
	if(fp == NULL){
		printf("open file failed");
	}
	else{
		int data,ith,group,m,n,i;
		char command[10];
		tot = 0;
		fscanf(fp,"%d %d\n",&m,&n);
		for(i=0;i<m;i++){
			fscanf(fp,"%d",&data);
			add(data);
		}
		for(i = 0 ;i<n;i++){
			fscanf(fp,"%s",command);
			if(command[0] == 'a'){
				fscanf(fp,"%d\n",&data);
				add(data);
			}
			else if(command[0] == 'r'){
				fscanf(fp,"%d\n",&group);
				rev(group);
			}
			else if(command[0] == 'd'){
				fscanf(fp," %d\n",&ith);
				del(ith);
			}
			else if(command[0] == 'i'){
				fscanf(fp," %d %d\n",&ith,&data);
				ins(ith,data);
			}
			else{
				show();
			}
		}	
	}
	fclose(fp);
	return 0;
}
