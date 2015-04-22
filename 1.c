/*************************************************************************
 * File Name :  1.c
 * 保留之前的位置
 * Author  :      unasm
 * Mail :         unasm@sina.cn
 * Last_Modified: 2015-04-22 01:12:34
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
struct arr{
	int pos,val;
}arr[1000000];
int cmp(const void *a , const void * b){
	//return *(int *)a  - *(int *)b;
	return (*(const struct arr *)a).val - (*(const struct arr *)b).val;
}

int bsea(int start, int end, int target){
	if(start == end){
		if (arr[start].val == target){
			return start;
		}
		return -1;
	}
	int half = (start + end ) / 2;
	int a = bsea(start, half , target);
	int b = bsea(half + 1, end , target);
	if(a == -1){
		return b;
	}
	return a;
}
int *twoSum(int numbers[], int n, int target) {
	int res[2], *p, ans;
	for (int i = 0; i < n; i++) {
		arr[i].pos = i + 1;
		arr[i].val = numbers[i];
	}
	qsort(arr, n,sizeof(arr[0]), cmp)	;
	for (int i = 0; i < n; i++) {
		printf("%d\n", arr[i].val);
	}
	for(int i = 0;i < n - 1; i++) {
		ans = bsea(i + 1, n - 1, target - arr[i].val );
		if(ans != -1){
			res[0] = arr[i].pos < arr[ans].pos ? arr[i].pos : arr[ans].pos;
			res[1] = arr[i].pos > arr[ans].pos ? arr[i].pos : arr[ans].pos;
			p = res;
			return p;
		}
	}
	return p;
	//return &res;
}
int main(int argc, const char *argv[])
{
	//int num[] = {2,7 ,11,15},length = 4,*p,tar = 9,expect[] = {1,2};
	//int num[] = {3,2,4},length = 3,*p,tar = 6,expect[] = {2,3};
	int num[] = {2,11 ,7,15},*p,length = 4,tar = 26,expect[] = {3,4};
	p = twoSum(num,length,tar);
	if(p[0] == expect[0] && p[1] == expect[1]){
		printf("yes\n");
	} else {
		printf("%d\n", p[0]);
		printf("%d\n", p[1]);
	}
	return 0;
}
