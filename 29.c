/*************************************************************************
  * File Name :  29.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-10 18:25:16
 ************************************************************************/

#include<stdio.h>
#include<limits.h>
#include<math.h>
#include<stdlib.h>

int divide(int dividend, int divisor) {
	long long  up,down;
	up = dividend;	
	down = divisor;
	
	if(up < 0) {
		up = -up;
	}
	if(down < 0) {
		down =  -down;
	}
	
	long long cal,ans = 0;
	while(up >= down) {
		cal = -1;
		while (up >= (down << (1+cal))) {
			cal++;
		}
		//printf("%d\t",cal);
		up -= down << cal;
		ans |= (long long )1 << cal;
	}
	/*
	printf("\n");
	*/
	
	if ((dividend < 0 && divisor < 0) || (dividend > 0 && divisor > 0)) {
		if(ans >= INT_MAX) {
			return INT_MAX;
		}
		return (int)ans;	
	} else {
		return -ans;
	}
	
}
void test(int up, int down ,int expect) {
	int res = divide(up,down);
	if(res == expect) {
		printf("yes\n");
	} else {
		printf("%d\n", res);
	}
}
int main(int argc, const char *argv[])
{
	//test(-2147483648,1000369383,-2);
	test(-2147483648,1,-2147483648);
	test(-2147483648,-1,INT_MAX);
	test(15, 5,3);
	test(14, 5,2);
	test(15, 1,15);
	test(7, 3,2);
	test(200000000,100000000,2);
	//test(-9,4,-2);
	//test(9,4,2);
	return 0;
}
