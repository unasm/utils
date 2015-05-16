/*************************************************************************
  * File Name :  35.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-16 22:38:42
 ************************************************************************/

#include<stdio.h>

int searchInsert(int* nums, int numsSize, int target) {
	int mid;
	for(int sta = 0 ,end = numsSize - 1;sta <= end;) {
		if(sta == end) {
			if(nums[sta] >= target){
				return sta;
			}
			return sta + 1;
		}
		mid = (sta + end ) / 2;
		if(nums[mid] < target) {
			sta = mid + 1;
		} else {
			end = mid;
		}
	}
	return 0;
}
int main(int argc, const char *argv[])
{
	int num[10000] = {1,3,5,6};
	int target,exp;
	target = 5,exp = 2;
	//target = 2,exp = 1;
	//target = 7,exp = 4;
	//target = 0,exp = 0;
	int res = searchInsert(num,4,target);
	if(res == exp) {
		printf("yes\n");
	} else {
		printf("%d\n",res);
	}
	return 0;
}
