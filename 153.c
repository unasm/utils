/*************************************************************************
  * File Name :  153.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-17 18:22:42
 ************************************************************************/

#include<stdio.h>

int findMin(int* nums, int numsSize) {
	int mid;
	while(numsSize > 2 && nums[numsSize - 1] == nums[0]) {
			numsSize --;	
	}
	for(int sta = 0,end = numsSize - 1, target = nums[end]; sta <= end;) {
		if(sta == end) {
			return nums[sta];	
		}
		mid = (sta + end) / 2;
		if(nums[mid] > target) {
			sta = mid + 1;
		} else {
			target = nums[mid];
			end = mid;
		}
	}
	return 0;
}
int main(int argc, const char *argv[])
{
	int nums[] = {2,2 ,1 ,2},size = 4;
	//int nums[] = {4,4,4 ,5 ,6, 7,7 ,0 ,1 ,2},size = 10;
	//int nums[] = {4 ,5 ,6, 7 ,0 ,1 ,2},size = 7;
	int res = findMin(nums,size);
	printf("%d\n",res);
	return 0;
}
