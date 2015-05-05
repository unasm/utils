/*************************************************************************
  * File Name :  17.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-04-29 15:36:06
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
char map[][5] = {" ","","abc","def","ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
//char buf[1000], **p;
char buf[1000], (*p)[10000];
int pointer;
void deep( char* digits, int pos){
	char *tmp;
	for (int i = 0; map[digits[pos] - '0'][i] != '\0';i++) {
		if (digits[pos + 1] == '\0') {
			buf[pos] = map[digits[pos] - '0'][i];
			tmp = (char *)malloc(sizeof(char) *( pos + 1));
			memcpy(tmp, buf, pos);
			p[pointer]  = tmp;
			pointer++;
		} else {
			buf[pos] =  map[digits[pos] - '0'][i];
			deep(digits, pos + 1);
		}
	}
}
char** letterCombinations(char* digits, int* returnSize) {
	pointer = 0;
	deep(digits, 0) ;
	*returnSize = pointer;
	printf("%d\n",*returnSize);
	return p;
}
int main(int argc, const char *argv[])
{
	char code[] = "23", **res;int size;
	res = letterCombinations(code, &size)	;
	for(int i = 0;i < size;i++){
		printf("%s\n", res[i]);
	}
	return 0;
}
