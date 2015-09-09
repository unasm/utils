/*************************************************************************
  * File Name :  45.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-09-09 11:28:25
 ************************************************************************/

#include<stdio.h>

int getMax(int a, int b) {
	return a > b ? a : b;
}
int jump(int* nums, int numsSize) {
	int step = 0,max = nums[0];
	numsSize -= 1;
	int still = 0;
	for (int i = 1;i <= numsSize;i++)    {
		if (still < i) {
			step++;
			still = max;
			if (still >= numsSize) {
				return step;	
			}
		}
		max = getMax(max,i + nums[i]);
	}
	return step;
}
int main(int argc, const char *argv[])
{
	
	int arr[] = {2,3,1,1,4}, size = 5;
	int res = jump(arr, size);
	printf("%d\n", res);
	return 0;
}
