#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *fin,*fout;
char stack[200],top=-1;
void push(char c){
	stack[++top]=c;
}
char pop(){
	return stack[top--];
}
int op(char c){
	switch(c){
		case '&':
		case '^':
		case '|':
			return 1;
		case '>':
		case '<':
			return 2;
		case '+':
		case '-':
			return 3;
		case '*':
		case '%':
		case '/':
			return 4;
		case ')':
			return 5;
		case '(':
			return 6;
	}
	return 0;
}
int main(){
	fin=fopen("input_2-4.txt","r");
	int n,len,i;
	char s[201],ans[201],atop=-1;
	fscanf(fin,"%d ",&n);
	for(;n;n--){
		fscanf(fin,"%s",s);
		len=strlen(s);
		for(i=len-1;i>=0;i--){
			if(op(s[i])){
				if(s[i]=='('){
					while(ans[atop]!=')'){
						ans[++atop]=pop();
					}
					atop--;
					continue;
				}
				while(top!=-1&&(op(s[i])<op(stack[top])&&stack[top]!=')')){
					ans[++atop]=pop();
				}
				push(s[i]);
			}
			else
				ans[++atop]=s[i];
		}
		while(top>=0){
			ans[++atop]=pop();
		}
		for(i=atop;i>=0;i--){
			printf("%c",ans[i]);
		}
		atop=-1;
		printf("\n");
	}
	return 0;
}
