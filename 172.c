/*************************************************************************
  * File Name :  172.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-04-14 01:12:15
 ************************************************************************/

#include<stdio.h>
#include <limits.h>
int dp[100];
//小于95的话，95 
//195
//n / 5
//2934
int trailingZeroes(int n) {
	int i = 0, res = 0;
	dp[0] = 5;
	for(i = 1;i < 10000;i++){
		dp[i] = dp[i-1] * 5;
		res += (n / dp[i]);
		if(dp[i] >= (INT_MAX / 5)){
			printf("sdfa\n");
			break;
		}
		if(dp[i] > n){
			break;
		}
		//printf("%d\n",dp[i]);
	}

	res += n / 5 ; 
	//printf("\n%d\n",res);
	return res;
}
int main(int argc, const char *argv[])
{
	//int value = 200,expect = 49;
	int value = 1808548329,expect = 452137076;
	//int value = 30,expect = 7;
	int res = trailingZeroes(value);
	if(res == expect){
		printf("yes\n");
	} else {
		printf("%d\n",res);
	}
	//trailingZeroes(126);
	return 0;
}

