/*************************************************************************
  * File Name :  64.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-19 00:07:18
 ************************************************************************/

#include<stdio.h>

int line[100000];
int min(int a,int b) {
	return a < b ? a : b;
}
int minPathSum(int** grid, int gridRowSize, int gridColSize) {
	if(gridRowSize <= 0 || gridColSize <= 0)return 0;
	line[0] = grid[0][0];
    for(int i = 1;i < gridColSize;i++) {
		line[i] = grid[0][i] + line[i-1];
	}
	for(int i = 1;i < gridRowSize; i++) {
		for(int j = 0; j < gridColSize;j++)	 {
			if(j == 0)	{
				line[j] += grid[i][j];
			} else {
				line[j] = grid[i][j] + min(line[j-1],line[j]);
			}
		}
	}
	return line[gridColSize - 1];
}
int main(int argc, const char *argv[])
{
	int a[] = {1,3,1};
	int b[] = {1,5,1};
	int c[] = {4,2,1};
	int *num[3];
	num[0] = a;
	num[1] = b;
	num[2] = c;
	int res = minPathSum(num,3,3);
	printf("%d\n",res);
	return 0;
}
