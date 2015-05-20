/*************************************************************************
  * File Name :  135.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-20 22:27:05
 ************************************************************************/

#include<stdio.h>
int dp[100000];

int max(int a,int b) {
	return a > b ? a : b;
}
int candy(int* ratings, int ratingsSize) {
	if(ratingsSize <= 0)return 0;
	int sum = 1,last = 1,pos = 0; 
	dp[0] = 1;
	for(int i = 1;i < ratingsSize;i++) {
		if(ratings[i] > ratings[i-1])	 {
			dp[i] = dp[i-1] + 1;
		//} else if(ratings[i] == ratings[i - 1]) {
			//dp[i] = dp[i-1];
		} else {
			dp[i] = 1;
		}
		//last += last;
	}
	for(int i = ratingsSize - 2; i >= 0;i--) {
		if(ratings[i] > ratings[i + 1]) {
			dp[i] = max(dp[i], dp[i+1] + 1);
		//} else if (ratings[i] == ratings[i+1]) {
			//dp[i] = max(dp[i], dp[i+1]);
		}
	}
	int ans = 0;
	for(int i = 0;i < ratingsSize;i++) {
		printf("%d\t", dp[i]);
		ans += dp[i];
	}
	printf("\n");
	return ans;
}

// 1 3 2 1


int main(int argc, const char *argv[])
{
	int nums[] = {1,1,2,1},size = 4,expect = 5;
	//int nums[] = {1,2,1,2},size = 4,expect = 6;
	//int nums[] = {3,1,5},size = 3,expect = 5;
	//int nums[] = {1,2,2},size = 3,expect = 4;
	//int nums[] = {1,3,2,1},size = 4;
	int res = candy(nums,size);
	if (res == expect) {
		printf("yes\n");
	} else {
		printf("%d\n",res);
	}
	return 0;
}
