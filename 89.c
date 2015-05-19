/*************************************************************************
  * File Name :  89.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-18 10:09:01
 ************************************************************************/

#include<stdio.h>

int res[100000];
int* grayCode(int n, int* returnSize) {
	if(n == 0) {
		*returnSize = 0;
		return res;
	}
	int last = 0;
	*returnSize = 0;
	res[*returnSize] = 0;
	(*returnSize)++;
	for(int i = 0;i < n;i++) {
		last = last | ( 1 << i)	;
		res[*returnSize] = last;
		(*returnSize) ++;
		int sta = i;
		while(sta > 0) {
			sta --;
			for(int j = sta ; j >= 0;j--) {
				last = last ^ (1 << j);
				res[*returnSize] = last;
				(*returnSize) ++;
			}
		}
	}
	for(int i = 0;i < *returnSize;i++) {
		printf("%d\t", res[i]);
	}
	printf("\n");
	return res;
}
int main(int argc, const char *argv[])
{
	int size;
	grayCode(2, &size);
	grayCode(3, &size);
	grayCode(4, &size);
	return 0;
}
