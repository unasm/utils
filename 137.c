/*************************************************************************
  * File Name :  137.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-17 00:03:35
 ************************************************************************/

#include<stdio.h>

int singleNumber(int* nums, int numsSize) {
	char ans[100];
	for(int i = 0;i < 32;i++) {
		ans[i] = 0;
	}
	for (int i = 0;i< numsSize;i++)  {
		for(int j = 0;j < 32;j++) {
			if( 1 << j & nums[i])	{
				ans[j]++;
				ans[j] %= 3;
			}
		}
	}
	int res = 0;
	for(int i = 0;i < 32;i++) {
		if (ans[i] % 3)	{
			res |= 1 << i;	
		}
	}
	//printf("%d\n", res);
	return res;
}
int main(int argc, const char *argv[])
{
	int nums[] = {1,1,1,2},size = 4;
	singleNumber(nums,size);
	return 0;
}
