/*************************************************************************
 * File Name :  27.c
 * Author  :      unasm
 * Mail :         unasm@sina.cn
 * Last_Modified: 2015-05-09 17:31:46
 ************************************************************************/

#include<stdio.h>
#include <string.h>
void getNext(const char* t ,int* next){  
	int i=0, j=-1;  
	next[0] = -1;  
	int n = strlen(t);
	while(i < n){  
		if(j == -1 || t[j] == t[i]){  
			i++;  
			j++;  
			next[i]=j;  
		}else{//如果不等或j为其他,则j回到next[j]位置继续匹配  
			j = next[j];  
		}  
	}  
}
int main(int argc, const char *argv[])
{
	char map[] = "ABABABCD";
	int next[10000];
	getNext(map,next);
	for(int i = 0,len = strlen(map); i < len;i++) {
		printf("%c\t",map[i]);
		//printf("%d\n",next[i]);
	}
	printf("\n");
	for(int i = 0,len = strlen(map); i < len;i++) {
		//printf("%c\t",map[i]);
		printf("%d\t",next[i]);
	}
	printf("\n");
	return 0;
}
