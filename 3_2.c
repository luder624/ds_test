# include<stdio.h>
# include<stdlib.h>
# include <string.h>
struct Node{
	int num;
	struct Node* left;
	struct Node* right;
};
struct List{
	struct Node* point;
};
struct List* list;
struct Node* root;
int* tot;
int size,ans;
void findans(struct Node* node,int depth){
	if(node ==NULL){
		return;
	}
	findans(node->left,depth+1);
	findans(node->right,depth+1);
	if(!node->left && !node->right){
		ans+= node->num*depth;
	}
}
void findmin(){
	int i,min=list[0].point->num,index=0;
	struct Node* swap;
	for(i=0;i<size;i++){
		if(min > list[i].point->num){
			min = list[i].point->num;
			index = i; 
		}
	}
	swap=list[index].point;
	list[index].point = list[size-1].point;
	list[size-1].point = swap;
}
void huff(){
	int i;
	while(1){
		findmin();
		struct Node* n1 = list[--size].point;
		findmin();
		struct Node* n2 = list[--size].point;
		struct Node* newnode=(struct Node*)malloc(sizeof(struct Node));
		newnode->num = n1->num+n2->num;
		newnode->left = n1;
		newnode->right =n2;
		list[size++].point = newnode;
		if(size ==1){
			break;
		} 
	}
	root = list[0].point;
	ans =0;
	findans(root,0);
}
void create_list(){
	size =0;
	int i;
	list = (struct List*)malloc(sizeof(struct List)*70);
	for(i=0;i<70;i++){
		if(tot[i]!=0){
			struct Node* node = (struct Node*)malloc(sizeof(struct Node));
			node->num = tot[i];
			node->left=NULL;
			node->right=NULL;
			list[size++].point = node;
		}
	}
	return;
}
void count(char* s){
	int i;
	for(i=0;i<strlen(s);i++){
		if(s[i]==' '){
			tot[0]++;
		}
		else if(s[i]=='!'){
			tot[1]++;
		}
		else if(s[i]==','){
			tot[2]++;
		}
		else if(s[i]=='-'){
			tot[3]++;
		}
		else if(s[i]=='.'){
			tot[4]++;
		}
		else if(s[i]==':'){
			tot[5]++;
		}
		else if(s[i]==';'){
			tot[6]++;
		}
		else if(s[i]=='?'){
			tot[7]++;
		}
		else if(s[i]-'0'>=0 && s[i]-'0'<10){
			tot[(s[i]-'0')+8]++;
		}
		else if(s[i]-'a'>=0 && s[i]-'a'<26){
			tot[(s[i]-'a')+18]++;
		}
		else if(s[i]-'A'>=0 && s[i]-'A'<26){
			tot[(s[i]-'A')+44]++;
		}
		else{
			continue;
		}
	}
}
int main(){
	FILE *fp;
	fp = fopen("input_8-4.txt","r");
	if(fp == NULL){
		printf("open file failed");
	}
	else{
		int m,i;
		char* s = (char*)malloc(sizeof(char)*1001);
		tot = calloc(70,sizeof(int));
		while(1){
			fscanf(fp,"%d\n",&m);
			if(m==0){
				break;
			}
			else{
				for(i=0;i<70;i++){
					tot[i]=0;
				}
				for(i=0;i<m;i++){
					memset(s,0,1000);
					fgets(s,1000,fp);
					count(s);
				}
				create_list();
				huff();
				printf("%d\n",ans);
			}
		}	
	}
	fclose(fp);
	return 0;
}
