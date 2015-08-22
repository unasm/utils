
/*************************************************************************
 * File Name :  42.c
 * Author  :      unasm
 * Mail :         unasm@sina.cn
 * Last_Modified: 2015-08-22 17:18:42
 ************************************************************************/

#include<stdio.h>
int left[1000000], right[1000000];
int trap(int* height, int heightSize) {
	left[0] = height[0];
	right[heightSize - 1] = height[heightSize - 1];
	for(int i = 1;i < heightSize;i++) {
		left[i]= left[i - 1] > height[i] ?  left[i - 1] : height[i];
	}
	for(int i = heightSize - 2;i >= 0;i--) {
		right[i]= right[i + 1] > height[i] ?  right[i + 1] : height[i];
	}

	for (int i = 0;i < heightSize;i++) {
		printf("%d\t", left[i]);
		printf("%d\n", right[i]);

	}
	int res = 0, tmp;
	for (int i = 1;i < heightSize - 1;i++) {
		tmp = (left[i] > right[i] ? right[i] : left[i]) - height[i];
		if (tmp > 0) {
			res += tmp;
		}
	}
	return res;
}
int main(int argc, const char *argv[])
{
	//int num[] = { 0,1,0,2,1,0,1,3,2,1,2,1 }, size = 12, exp = 6;
	int num[] = { 2, 0, 2 }, size = 3, exp = 2;
	int res = trap(num, size)	;
	if (res == exp) {
		printf("yes\n");
	} else {
		printf("%d\n", res);
	}
	return 0;
}
