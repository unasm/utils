/*************************************************************************
  * File Name :  62.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-17 19:05:12
 ************************************************************************/

#include<stdio.h>
int line[10000];


int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridRowSize, int obstacleGridColSize) {
 	if(obstacleGridRowSize <= 0 || obstacleGridColSize <= 0)    return 0;
	for(int i = 0;i < obstacleGridColSize;i++) {
		line[i] = 0;
	}
	if(obstacleGrid[0][0] == 1) {
		return 0;
	}
	line[0] = 1;
	for(int i = 0;i < obstacleGridRowSize;i++) {
		for(int j = 0;j < obstacleGridColSize;j++)	 {
			if (obstacleGrid[i][j] == 1) {
				line[j]	 = 0;
			} else if (j != 0) {
				line[j]	 = line[j] + line[j-1];
			}
		}
	}
	return line[obstacleGridColSize - 1];   
}
int main(int argc, const char *argv[])
{
	int *num[3];
	//int a[1000];
	/*
	int a[] = {0,0,0};
	num[0] = a;
	int b[] = {0,0,0};
	num[2] = b;
	int c[] = {0,1,0};
	num[1] = c;
	int res = uniquePathsWithObstacles(num,3,3);
	*/
	//int num[3][3] = {{0,0,0}, {0,1,0},{0,0,0} };
	int a[] = {0,1};
	num[0] = a;
	int res = uniquePathsWithObstacles(num,1,2);
	printf("%d\n", res);
	return 0;
}
