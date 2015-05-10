/*************************************************************************
  * File Name :  26.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-09 16:40:15
 ************************************************************************/

#include<stdio.h>

int removeDuplicates(int* nums, int numsSize) {
	int cnt = 0;
	if(numsSize == 0) {
		return 0;
	}
	for(int i = 1;i < numsSize;i++)  {
		if (nums[i] != nums[cnt]) {
			cnt++;
			nums[cnt] = nums[i];
		}
	}
	return cnt + 1;
}
int main(int argc, const char *argv[])
{
	
	return 0;
}
