/*************************************************************************
  * File Name :  33.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-08-14 07:15:54
 ************************************************************************/

#include<stdio.h>

int midSearch(int * nums , int min, int max,int target) {
	int mid;
	while(max >= min) {
		if (min == max) {
			if (nums[min] == target) {
				return min;
			}
			return -1;
		}
		mid = (max + min) /2;
		if (nums[mid] >= target) {
			max = mid;
		} else {
			min = mid + 1;
		}
	}
	return -1;
}
int search(int* nums, int numsSize, int target) {
	int sep = 0;
	for (int i = 1;i < numsSize;i++) {
		if (nums[i] < nums[i - 1]) {
			sep = i;	
			break;
		}
	}
	int a = midSearch(nums, 0, sep - 1, target);
	if (a != -1) {
		return a;
	}
	return midSearch(nums, sep, numsSize - 1, target);
}
int main(int argc, const char *argv[])
{
	//int nums[] = {0,1,2,3,4}, size = 5,target = 3;
	int nums[] = {2,3,4, 0, 1}, size = 5,target = 3;
	int res = search(nums, size, target);
	printf("%d\n", res);
	return 0;
}
