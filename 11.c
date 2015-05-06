/*************************************************************************
  * File Name :  11.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-05 17:20:35
 ************************************************************************/

#include<stdio.h>
int  max(int a, int b) {
	return a > b ? a : b;
}
int min(int a, int b) {
	return a < b ? a : b;
}
int maxArea(int* height, int heightSize) {
	int maxvalue = 0;
	int sa = 0,sb = heightSize - 1;
	while (sa < sb) {
		maxvalue = max(maxvalue , min(height[sa], height[sb]) * (sb - sa))	;
		if(height[sa] > height[sb]) {
			sb --;
		} else {
			sa++;
		}
	}
	return maxvalue;
}

int main(int argc, const char *argv[])
{
	int heits[] = {1,3,2,4},size = 4,expect = 6;
	int res = maxArea(heits, size);
	printf("%d\n",res);
	return 0;
}
