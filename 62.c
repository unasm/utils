/*************************************************************************
  * File Name :  62.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-17 19:05:12
 ************************************************************************/

#include<stdio.h>
int line[10000];
int uniquePaths(int m, int n) {
	if(m <= 0 || n <= 0)    return 0;
	for(int i = 0;i < m;i++) {
		line[i] = 1;
	}
	for(int i = 1;i < n;i++) {
		for(int j = 1;j < m;j++)	 {
			line[j]	 = line[j] + line[j-1];
		}
	}
	return line[m - 1];
}
int main(int argc, const char *argv[])
{
	printf("%d\n", uniquePaths(3,3));
	return 0;
}
