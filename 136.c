/*************************************************************************
  * File Name :  136.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-14 11:48:29
 ************************************************************************/

#include<stdio.h>

int singleNumber(int* nums, int numsSize) {
	int res = 0;
	for(int i = 0;i < numsSize;i++)     {
		nums[i]	^= res;
	}
	return res;
}
int main(int argc, const char *argv[])
{
	int nums[] = {1}, size = 1;
	int res = singleNumber(nums,size);
	printf("%d\n", res);
	return 0;
}
