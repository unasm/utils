/*************************************************************************
  * File Name :  28.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-10 15:20:53
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int next[100000];
void getNext(char *need ,int size) {
	
	int pointer = -1 , idx = 0;
	next[0] = -1;
	while (idx < size) {
		if (pointer == -1 || need[pointer] == need[idx]) {
			idx++;
			pointer++;
			next[idx] = pointer;
		} else {
			pointer = next[pointer];
		}
	}
}

int strStr(char* haystack, char* needle) {
	int size = strlen(needle);
	if(size == 0) {
		return 0;
	}
	getNext(needle, size) ;

	int pointer = 0;
	/*
	for(int i = 0;i < size;i++) {
		printf("%c\t", needle[i]);
	}
	printf("\n");
	for(int i = 0;i < size;i++) {
		printf("%d\t", next[i]);
	}
	printf("\n");
	*/
	for (int i = 0; haystack[i] != '\0';) {
		if( pointer == -1 || haystack[i] == needle[pointer]) {
			pointer++;
			i++;
			if(pointer == size ) {
				//printf("matched : %d    %d\n",pointer , i);
				return i - size + 1 ;
			}
		} else {
			pointer = next[pointer];
		}
	}
	return -1;
}
void test(char *hay, char* need, int expect) {
	int res = strStr(hay, need)	;
	if (res == expect) {
		printf("yes\n");
	} else {
		printf("%d\n", res);
	}
}
int main(int argc, const char *argv[])
{
	char hay[] = "ababc",need[] = "abc"; int expect = 2;
	test("ababc", "abc", 3);
	test("", "", 0);
	test("abababc", "abc", 5);
	return 0;
}
