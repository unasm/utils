/*************************************************************************
  * File Name :  34.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-08-14 07:36:00
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int midSearchLess(int * nums , int min, int max,int target) {
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

int midSearchMore(int * nums , int min, int max,int target) {
	int mid;
	while(max >= min) {
		if (min == max) {
			if (nums[min] == target) {
				return min;
			}
			return -1;
		}
		mid = (max + min) /2;
		if (nums[mid] > target) {
			max = mid;
		} else if (nums[mid] == target && nums[mid+1] > target){
			return mid;
			//min = mid;	
		} else {
			min = mid + 1;
		}
	}
	return -1;
}
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
	int *res = malloc(sizeof(int) * 2);
	//int t = 2;
	*returnSize = 2;    
	res[1] = midSearchMore(nums, 0, numsSize - 1, target);
	res[0] = midSearchLess(nums, 0, numsSize - 1, target);
	return res;
}
int main(int argc, const char *argv[]){
	int returnSize;
	int nums[] = {1, 4, 5, 8, 8, 8}, size = 6,target = 6;
	int *res = searchRange(nums, size, target, &returnSize);
	printf("%d\n", res[0]);
	printf("%d\n", res[1]);
	return 0;
}
