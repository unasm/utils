/*************************************************************************
  * File Name :  3.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-04-23 15:40:13
 ************************************************************************/

#include<stdio.h>

int hash[300];

int max(int a, int b) {
	return a > b ? a: b;
}

int min(int a, int b) {
	return a < b ? a: b;
}
int lengthOfLongestSubstring(char* s) {
	int i,res = 0,left = 0;
	for (i = 0;i < 300;i++) {
		hash[i] = -1;
	}
	for (i = 0; s[i] != '\0' ;i++) {
		if(hash[s[i]] != -1)	{
			//res = max(i - hash[s[i]], res);
			res = max(left , res);
			left = min(left + 1 , i - hash[s[i]]);
		} else {
			left += 1;	
		}
		hash[s[i]] = i;
	}
	return max(res, left);
}
int main(int argc, const char *argv[])
{
	//char str[] = "abcab";int expect = 3;
	//char str[] = "aaaaa";int expect = 1;
	//char str[] = "au";int expect = 2;
	//char str[] = "abba";int expect = 2;
	char str[] = "abbaacd";int expect = 3;
	int res = lengthOfLongestSubstring(str);
	if (res == expect) {
		printf("yes\n");
	} else {
		printf("%d\n", res);
	}
	return 0;
}
