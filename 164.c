/*************************************************************************
  * File Name :  164.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-04-27 23:51:20
 ************************************************************************/

#include<stdio.h>
#include<limits.h>
#include <stdbool.h>
struct arr{
	int max,min;
}hash[1000000];
int minfunc(int a,int b){
	return a < b ? a : b;
}
int maxfunc(int a,int b){
	return a > b ? a : b;
}
int maximumGap(int* nums, int numsSize) {
	if (numsSize < 2) {
		return 0;
	}
	int min = INT_MAX, max = -1;
	for (int i = 0;i < numsSize;i++) {
		min = minfunc(min , nums[i])	;
		max = maxfunc(max , nums[i])	;
	}
	double inter = (double)numsSize / (double)(max - min);
	for (int i = 0;i <= numsSize;i++) {
		hash[i].max = -1;
		hash[i].min = -1;
	}
	for (int i = 0;i < numsSize;i++) {
		int idx = (int)(nums[i] - min) * inter;
		if (hash[idx].max == -1) {
			hash[idx].max = nums[i];
			hash[idx].min = nums[i];
		} else {
			hash[idx].min = minfunc(hash[idx].min , nums[i]);
			hash[idx].max = maxfunc(hash[idx].max , nums[i]);
		}
	}
	int last = hash[0].max, dis = 0;
	for (int i = 1;i <= numsSize;i++) {
		if (hash[i].min != -1)	{
			dis = maxfunc(dis, hash[i].min - last);
			last = hash[i].max;
		}
	}
	return dis;
}
int main(int argc, const char *argv[])
{
	int num[] = {0,123,2323,2},length = 4, expect = 2200;
	//int num[] = {0,123,2323,2},length = 4, expect = 2200;
	int res;
	res = maximumGap(num ,length);
	if (res == expect) {
		printf("yes\n");
	} else {
		printf("%d\n", res);
	}
	return 0;
}
