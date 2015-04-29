/*************************************************************************
  * File Name :  7.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-04-29 23:33:07
 ************************************************************************/

#include<stdio.h>
#include <limits.h>
int reverse(int x) {
	int flag = 1;
	if(x < 0) {
		flag = -1;
		x = -x;
	}
	long long mod = 0,res = 0;
	while(x > 0) {
		mod = x % 10;
		res = res * 10 + mod;
		x /= 10;
	}
	if(res * flag > INT_MAX || res * flag < INT_MIN){
		return 0;
	}
	return res * flag;
}
int main(int argc, const char *argv[])
{
	//int value = -23,expect = -32;
	//int value = 32,expect = 23;
	int value = 1534236469,expect = 0;
	printf("%d\n\n" , value);

	int res = reverse(value)	;
	if(res == expect) {
		printf("yes\n");
	} else {
		printf("%d\n", res);
	}
	return 0;
}
