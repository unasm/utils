/*************************************************************************
  * File Name :  4.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-08-07 19:56:04
 ************************************************************************/

#include<stdlib.h>
#include<stdio.h>

int midSearch(int num, int *arr, int size) {
	int mid, min = 0,max;
	max = size;
	while(min < max) {
		mid = (min + max) / 2;
		if (arr[mid] < num) {
			min = mid + 1;
			if (arr[min] > num) {
				return min - 1;
			}
		}
		if (arr[mid] > num) {
			max = mid;
		}
		if (arr[mid] == num) {
			return mid;
		}
	}
	return min;
}
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
	int min1 = 0,max1 = nums1Size - 1,min2 = 0 ,max2 = nums2Size - 1, pos,mid;	    
	int left , right;
	left = (nums1Size + nums2Size - 1) / 2;
	right = left;
	//flag 标记找到的是不是真
	while(min1 < (max1 - 1) && min2 < (max2 - 1)) {
		mid = (min1 + max1) / 2;
		//如果找不到相同的，找小于的位置
		pos = midSearch(nums1[mid], nums2, nums2Size);
		int rtmp = 	max2 - pos + max1 - mid ;
		int ltmp = pos - min2 + mid - min1;
		if (left > ltmp) {
			left -= ltmp;
			min1 = mid;
			min2 = pos;
		} else if (right > rtmp) {
			right -= rtmp;
			max2 = pos;
			max1 = mid ;
		} else {
			//找到了想要的
			/*
			min1 = mid;
			max1 = mid;
			max2 = pos;
			min2 = pos;
			left = 0;
			right = 0;
			*/
			break;
		}
	}
	int cnt = 0;
	int size = 0;
	if (max1 >= min1) {
		size += max1 - min1 + 1;
	}
	if (max2 >= min2) {
		size += max2 - min2 + 1;
	}
	int *p = malloc(sizeof(int) * size);
	while(min1 <= max1 || min2 <= max2) {
		if (min1 > max1) {
			p[cnt++]= nums2[min2++];
		} else if (min2 > max2) {
			p[cnt++]= nums1[min1++];
		} else {
			if (nums1[min1] < nums2[min2]) {
				p[cnt++] = nums1[min1++];
			} else {
				p[cnt++] = nums2[min2++];
			}
		}
	}
	if ((nums1Size + nums2Size) % 2 )	 {
		return (double)p[left]	;
	} else {
		return ((double)(p[left] + p[left + 1])) / 2.0; 
	}
}
int main(){
	//int arr1[]	= {3,4,5},size1 = 3, arr2[] = {1,2,6}, size2 = 3; double exp = 3.5;
	//int arr1[]	= {1,3,4},size1 = 3, arr2[] = {2,5,6}, size2 = 3; double exp = 3.5;
	//int arr1[]	= {1,5,6},size1 = 3, arr2[] = {2,3,4}, size2 = 3; double exp = 3.5;
	//int arr1[]	= {1},size1 = 1, arr2[] = {2,3,4,5,6,7}, size2 = 6; double exp = 4;
	//int arr1[]	= {1,2,2},size1 = 3, arr2[] = {1,2,3}, size2 = 3; double exp = 2;
	//int arr1[]	= {},size1 = 0, arr2[] = {1}, size2 = 1; double exp = 1;
	//int arr1[]	= {1,2,3,7},size1 = 4, arr2[] = {3,4,5}, size2 = 3; double exp = 3;
	//1,2,3,3,4,5,5,7
	printf("%lf\n", findMedianSortedArrays(arr1,size1, arr2, size2));
	//printf("%d\n", midSearch(0,arr1, size1));
	return 0;
}
