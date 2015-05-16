/*************************************************************************
  * File Name :  123.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-14 14:34:07
 ************************************************************************/

#include<stdio.h>
int dp[100000];
int maxProfit(int* prices, int pricesSize) {
	if(pricesSize < 2) {
		return 0;
	}
	int min = prices[0];
	dp[0] = 0;
	for(int i = 1; i < pricesSize; i++)     {
		min = min < prices[i] ? min : prices[i];
		dp[i] = (prices[i] - min) > dp[i - 1] ? (prices[i] - min ) : dp[i-1];
	}
	int max = prices[pricesSize - 1], tmp, ans= dp[pricesSize - 1];
	for(int i = pricesSize - 2; i > 0 ; --i) {
		max = max > prices[i] ? max : prices[i];
		tmp  = (max - prices[i] )+ dp[i - 1];
		ans = ans > tmp ? ans : tmp;
	}
	return ans;
}
