/*************************************************************************
  * File Name :  37_2.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-08-20 10:11:42
 ************************************************************************/

#include<stdio.h>
#include<stdbool.h>

//每一列上面可用的
int colStack[20][20], colCnt[20];

bool check(char** board, int row , int col , int rowSize, int colSize, char exp) {
	for (int i = 0;i < colSize;i++) {
		if (board[row][i] == exp) {
			return false;
		}
	}
	for (int i = row - (row % 3), rowEnd = i + 3;i < rowEnd;i++) {
		for (int j = col - (col % 3), colEnd = j + 3; j < colEnd;j++) {
			if (board[i][j] == exp) {
				return false;
			}
		}
	}
	return true;
}
bool deep(char** board, int strow, int stcol, int rowSize, int  colSize) {
	//board[0][0] = 'c';
	if (stcol >= colSize) {
		strow += 1;
		stcol = 0;
	}
	for (int i = strow; i < rowSize; i++) {
		//同一行，从左向右加
		for (int j = stcol; j < colSize; j++) {
			if (board[i][j] == '.')	 {
				for (int k = colCnt[j] - 1 ; k >= 0;k--) {
					if (colStack[j][k] != -1 && check(board, i , j, rowSize, colSize, colStack[j][k])) {
						int old = board[i][j];
						board[i][j] = colStack[j][k];
						/*
						return false;
						*/
						colStack[j][k] = -1;
						if (deep(board, strow , stcol + 1, rowSize, colSize)) {
							//printf("yes\n");
							return true;
						}
						colStack[j][k] = board[i][j];
						board[i][j] = old;
					}
				}
				return false;	
			}
		}
		stcol = 0;
	}
	return true;
}
void solveSudoku(char** board, int boardRowSize, int boardColSize) {
	//board[0][0] = 'c';
	int hash[20];
	for(int i = 0; i < boardColSize;i++) {
		for (int j = 1;j < 10;j++) {
			hash[j] = 0;
		}
		for( int j = 0;j < boardRowSize;j++) {
			if (board[j][i] != '.') {
				//board[j][i] = 'c';
				//printf("%c\n", board[j][i]);
				hash[ board[j][i] - '0'] = 1;
			}
		}
		colCnt[i] = 0;
		for (int j = 1; j <= 9;j++) {
			if (hash[j] ==  0) {
				//printf("%c \t", '0' + j);
				colStack[i][colCnt[i]++] =  '0' + j;
			}
		}
		//printf("\n");
	}
	deep(board, 0, 0, boardRowSize, boardColSize);
	//*board[1][1] +=1;
}
int main(int argc, const char *argv[])
{
	char str[][9] = {
		"..9748...",
		"7........",
		".2.1.9...",
		"..7...24.",
		".64.1.59.",
		".98...3..",
		"...8.3.2.",
		"........6",
		"...2759..",
	}; int row = 9;
	/*
	char str[3][3] = {
		"..9",
		"7..",
		".2.",
	};int row = 3;
	*/
	char *board[10];
	for (int i = 0;i< row;i++) {
		board[i] = str[i];
	}
	//board[0][0] = '1';
	solveSudoku(board, row,row);
	for (int i = 0; i < row;i++) {
		for (int j = 0;j < row;j++) {
			printf("%c", board[i][j]);
		}
		printf("\n");
	}
	return 0;
}
