/*************************************************************************
  * File Name :  121.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-14 14:18:21
 ************************************************************************/

#include<stdio.h>
int dp[100000];
int maxProfit(int* prices, int pricesSize) {
	if(pricesSize <= 1) {
		return 0;
	}
	int min = prices[0], ans = 0;
	for(int i = 1; i < pricesSize; i++)     {
		min = min < prices[i] ? min : prices[i];
		ans = (prices[i] - min) < ans ? ans : (prices[i] - min );
	}
	return ans;
}
