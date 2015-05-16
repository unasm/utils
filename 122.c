/*************************************************************************
  * File Name :  122.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-14 14:30:43
 ************************************************************************/

#include<stdio.h>

int maxProfit(int* prices, int pricesSize) {
	if(pricesSize < 2) {
		return 0;
	}
	int ans = 0;
	for(int i = 1;i < pricesSize;i++) {
		if(prices[i] > prices[i-1]) {
			ans += prices[i] - prices[i-1];
		}
	}
	return ans;
}
