/*************************************************************************
  * File Name :  20.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-07 10:22:11
 ************************************************************************/

#include<stdio.h>
//#include<boolstd.h>
#include<stdbool.h>
char stack[100000];
bool isValid(char* s) {
	char map[300];
	for(int i = 0;i < 300;i++) {
		map[i] = 0;
	}
	map[')'] = '(';
	map[']'] = '[';
	map['}'] = '{';
	int top = 0; 
	for(int i = 0; s[i] != '\0'; i++) {
		if (map[s[i]]) {
			if (top && stack[top - 1] == map[s[i]] ) {
				top --;	
			} else {
				return false;
			}
		} else {
			stack[top++] = s[i];
		}
	}
	if(top == 0) {
		return true;
	}
	return false;
}
int main(int argc, const char *argv[])
{
	char sta[]	 = "{}()";bool expect = true;
	bool res = isValid(sta);
	if (res == expect) {
		printf("yes\n");
	} else {
		printf("%d\n", res);
	}
	return 0;
}
