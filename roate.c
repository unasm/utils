/*************************************************************************
  * File Name :  roate.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-03-29 21:30:51
 ************************************************************************/

#include<stdio.h>
int swap[100000];
void rotate(int nums[], int n, int k) {
	int z,tmp,i,j;
	if(n < 2)return;
	k %=n;
	for(i = n-k;i < n;i++){
		swap[i - (n-k) ] = nums[i];
	}
	for(i = n-k-1;i>=0;i--){
		nums[i+k] = nums[i];
	}
	for(i = 0;i < k;i++){
		nums[i] = swap[i];
	}
	for (z = 0; z < n; z++) {
			printf("%d\n", nums[z]);
	}
}
int main(int argc, const char *argv[])
{
	int data[10] = {1,2,3};
	//int data[10] = {1,2};
	//13939
	//int data[10] = {0,2,1,3};
	rotate(data ,3,1);
	return 0;
}
