/*************************************************************************
  * File Name :  96_bak.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-14 16:51:47
 ************************************************************************/

#include<stdio.h>
#define MAX 100000
int been[MAX];
int digui(n) {
	if(n < MAX && been[n] != 0 ) {
		return been[n]	;
	}
	if(n <= 1) {
		been[n] = 1;
		return been[n];
	}
	int ans = 0;
	n--;
	for(int i = 0;i <= n ;i++) {
		ans += digui(i) * digui(n - i);
	}
	if((n+ 1) < MAX ){
		been[n + 1] = ans;
	}
	return ans;
}
int min (int a,int b) {
	return a > b ? b: a;
}
int numTrees(int n) {
	for(int i = 0,end = min(n,MAX); i < end;i++) {
		been[i]	 = 0;
	}
	return digui(n);
	/*
	printf("%d\n", digui(2));
	printf("%d\n", digui(3));
	printf("%d\n", digui(4));
	return 0;
	*/
}
int main(int argc, const char *argv[])
{
	printf("%d\n", numTrees(5))	;
	return 0;
}
