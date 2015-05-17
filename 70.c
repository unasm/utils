/*************************************************************************
  * File Name :  70.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-17 01:34:07
 ************************************************************************/

#include<stdio.h>

#define MAX 100000
int been[MAX];

int digui(int n) {
	if(n <= 2) {
		return n;
	}
	if(n < MAX &&  been[n] != -1) {
		return been[n];
	}
	int tmp = digui(n-1) + digui(n-2);
	if(n < MAX)  {
		been[n] = tmp;
	}
	return tmp;
}
int climbStairs(int n) {
	if(n <= 2) {
		return n;
	}
	for(int i = 0;i < MAX;i++){
		been[i] = -1;
	}
	return digui(n);
}
