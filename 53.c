/*************************************************************************
  * File Name :  53.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-17 00:32:00
 ************************************************************************/

#include<stdio.h>
#include <limits.h>
int sum[100000];
/*
int maxSubArray(int* nums, int numsSize) {
	if(numsSize < 1){
		return 0;
	}
	if(numsSize == 1){
		return nums[0];
	}
	sum[0] = nums[0];
	for(int i = 1;i < numsSize;i++) {
		sum[i] = sum[i-1] + nums[i]	;
	}
	int max = INT_MIN;;
	for(int i = 1; i < numsSize;i++) {
		for(int j = 0;j < i;j++) {
			max = max > (sum[i] - sum[j]) ? max : (sum[i] - sum[j]);
		}
	}
	return max;
}
*/

int maxSubArray(int* nums, int numsSize) {
	if(numsSize < 1){
		return 0;
	}
	if(numsSize == 1){
		return nums[0];
	}
	int max=nums[0],last = nums[0];
	for (int i = 1;i < numsSize;i++) {
		if(last < 0 ) {
			last = nums[i];
		} else {
			last = last + nums[i];
		}
		max = last > max ? last : max;
	}
	return max;
}
