/*************************************************************************
  * File Name :  31.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-08-13 20:29:23
 ************************************************************************/

#include<stdio.h>

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b  = tmp;
}

void nextPermutation(int* nums, int numsSize) {
	if (numsSize <= 1) {
		return ;
	}
	for(int i = numsSize - 2; i >= 0;i--) {
		if (nums[i] <  nums[i+1]) {
			int pos = i+1;
			for(int j = numsSize - 1; j > i+1;j--) {
				if (nums[j] > nums[i]) {
					pos = j;
					break;
				}
			}
			swap(&nums[i], &nums[pos]);
			//swap(&nums[i], &nums[i+1]);
			int start = i+1, end = numsSize - 1;
			while(start < end) {
				swap(&nums[start], &nums[end]);
				start++;
				end--;
			}
			return;
		}
	}
	int start = 0, end = numsSize - 1;
	while(start < end) {
		swap(&nums[start], &nums[end]);
		start++;
		end--;
	}
}
 
int main(int argc, const char *argv[])
{
	//int nums[] = {3,2,1}, size = 3, expect[] = {1,2,3};
	//int nums[] = {1,2,3}, size = 3, expect[] = {1,3,2};
	//int nums[] = {1,3,2}, size = 3, expect[] = {2, 1, 3};
	//int nums[] = {1,3}, size = 2;
	int nums[] = {1,3,2,7,4,3,1}, size = 7, expect[] = {1,3,3,1,2,4,7};
	//swap(&nums[0], &nums[1]);
	nextPermutation(nums, size);
	int flag = 0;
	for(int i = 0;i < size;i++) {
		if (expect[i] != nums[i] ) {
			flag = 1;	
		}
		//printf("%d\t", nums[i]);
	}
	if (flag) {
		for(int i = 0;i < size;i++) {
			printf("%d\t", nums[i]);
		}
		printf("\n");
	} else {
		printf("yes");
	}
	return 0;
}
