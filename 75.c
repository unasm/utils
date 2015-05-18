/*************************************************************************
  * File Name :  75.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-18 09:55:24
 ************************************************************************/

#include<stdio.h>

void sortColors(int* nums, int numsSize) {
	int size[10];
	for(int i = 0;i < 5;i++) {
		size[i] = 0;
	}
	for(int i = 0;i < numsSize;i++) {
		size[nums[i]]++;
	}
	int cnt = 0;
	for(int i = 0;i < 3;i++) {
		for(int j = 0;j < size[i];j++) {
			nums[cnt++] = i;
		}
	}
}
int main(int argc, const char *argv[])
{
	int nums[] = {1},size = 1;
	sortColors(nums,size);
	for(int i = 0; i < size;i++) {
		printf("%d\t",nums[i]);
	}
	return 0;
}
