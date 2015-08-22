/*************************************************************************
 * File Name :  39.c
 * Author  :      unasm
 * Mail :         unasm@sina.cn
 * Last_Modified: 2015-08-20 14:20:49
 ************************************************************************/

#include<stdlib.h>
#include<stdio.h>

int dp[1000][1000];
int total, colCnt[1000],*res[1000];
//int total, *colCnt[1000],*res[1000];
void search(int row, int col ,int nowCol, int nums[], int* can) {
	//当前行
	int lastPric = col - can[row - 1];
	if (lastPric < 0) {
		return;
	}
	if (dp[row][lastPric]) {
		nums[nowCol] = can[row - 1];
		search(row, lastPric ,nowCol + 1,nums, can);
	}
	//从下一个上来，
	if (row > 1 && dp[row - 1][lastPric]) {
		nums[nowCol] = can[row - 1];
		search(row - 1, lastPric, nowCol + 1, nums, can);
	}
	if(lastPric == 0) {
		nums[nowCol] = can[row - 1];
		res[total] = malloc(sizeof(int) * (nowCol + 1));
		for (int i = nowCol;i >= 0;i--) {
			res[total][nowCol - i] = nums[i];
			//ans[total][nowCol - i] = nums[i];
		}
		//colCnt[total] = malloc(sizeof(int));
		colCnt[total] = (nowCol+1);
		//printf("%d\n", *colCnt[total]);
		total++;
	}
}
int** combinationSum(int* candidates, int candidatesSize, int target, int** columnSizes, int* returnSize) {
	int nums[1000];
	total = 0;
	for (int j = 0;j <= target;j++) {
		for (int i = 0;i <= candidatesSize;i++) {
			dp[i][j] = 0;
		}
	}

	for (int i = 1;i <=candidatesSize;i++) {
		int tmp = candidates[i-1];
		for(int j = 0; j <= target - tmp;j++) {
			if (j == 0 || dp[i][j] || dp[i - 1][j]) {
				dp[i][j + tmp] = 1;
			}
		}
	}
	for (int i = 1;i <= candidatesSize;i++) {
		if (dp[i][target]) {
			search(i, target, 0, nums, candidates);
		}
	}
	//printf("%d\n", total);
	/*
	for (int i = 0;i < total;i++) {
		for (int j = 0;j < colCnt[i];j++) {
			printf("%d\t", ans[i][j]);
		}
		printf("\n");
	}
	*/
	columnSizes = *colCnt;
	*returnSize = total;
	for (int i = 0;i < total;i++) {
		//printf("%d\n", *columnSizes[i]);
		//printf("%d\n", *colCnt[i]);
	}
	/*
	for (int i = 0;i < total;i++) {
		res[i] = ans[i];
	}
	*/
	return res;
}
int main(int argc, const char *argv[])
{
	//int can[] = {2,3,6,7},size = 4,target = 7,*col[1000], returnSize;
	/*
	int can[] = {2},size = 1,target = 1;
	int *col[1000], returnSize, **fin;
	*/
	int can[] = {1,2,3,6,7},size = 4,target = 8,(**col), returnSize, **fin;
	//int can[] = {1,2,3,6,7},size = 4,target = 8,*col[1000], returnSize, **fin;
	fin = combinationSum(can, size, target, col, &returnSize)	;
	//printf("%d\n", returnSize);
	for (int i = 0;i < returnSize;i++) {
		//printf("%d\n", (*col)+ i);
		//col++;
		printf("%d\n", col[i]);
		/*
		for (int j = 0;j < *col[i];j++) {
			printf("%d\t", fin[i][j]);
		}
		*/
		//printf("\n");
	}
	return 0;
}
