/*************************************************************************
  * File Name :  37.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-08-18 17:33:38
 ************************************************************************/

#include<stdio.h>
#include<stdbool.h>

int stack[20][20], cnt[20];
//查找横行是否符合规范
bool check(char** board , int x, int y, char exp){
	for(int i = 0;i < 9;i++) {
		if (board[y][i] == exp) {
			return false;
		}
	}
	for (int endx = x/3 + 3, i = x/3;i < endx;i++) {
		for (int endy = y/3 + 3,j = y/3; j < endy;j++) {
			if (board[i][j] == exp) {
				return false;
			}
		}
	}
	return true;
}

bool deep(char** board , int lastx, int lasty , int rowSize, int colSize) {
	if (lasty >= rowSize) {
		lastx ++;
		lasty = 0;
	}
	for(int i = lastx; i < colSize;i++) {
		for (int j = lasty;j < rowSize;j++) {
			if (board[j][i] == '.') {
				//如果遇到一个需要填的
				for (int k = cnt[i] - 1;k >= 0;k--)	 {
					// -1 表示已经被使用了 
					if (stack[i][k] != -1 && check(board, j, i, stack[i][k])) {
						int old = stack[i][k];
						stack[i][k] = -1;
						board[j][i] = old;
						printf("board %c\n", board[i][j]);
						if (deep(board,i,j + 1, rowSize, colSize)) {
							return true;
						}
						printf("board %c\n", board[i][j]);
						//printf("board %s\n", board[i]);
						//失败后恢复现场,尝试下一个
						stack[i][k] = old;
						board[i][j] = '.';
					}
				}	
				//但是可选项里面没有找到需要的，该位置不能满足
				return false;
			}
		}
		lasty = 0;
	}
	//没有遇到一个.表示全部填满了
	return true;
}
void solveSudoku(char** board, int boardRowSize, int boardColSize) {
	//获取全部需要填的字列表
	int hash[20];
	for (int i = 0;i < boardColSize;i++) {
		for (int j = 0;j < 10;j++) {
			hash[j] = 0;
		}
		for (int j = 0;j < boardRowSize; j++) {
			if (board[j][i] != '.') {
				hash[board[j][i] - '0'] = 1;
			}
		}
		cnt[i] = 0;
		//stack[i][cnt[i]++] = j + '0';
		for (int j = 1;j <= 9;j++) {
			if (hash[j] == 0) {
				stack[i][cnt[i]++] = j + '0';
			}
		}
	}
	if (deep(board, -1, boardRowSize, boardRowSize, boardColSize) ){
		printf("yes\n");
	} else {
		printf("no\n");
	}
	//printf("%s\n", board[0]);
}
int main(int argc, const char *argv[])
{
	
	char *board[] = {
		"..9748...",
		"7........",
		".2.1.9...",
		"..7...24.",
		".64.1.59.",
		".98...3..",
		"...8.3.2.",
		"........6",
		"...2759..",
	};
	solveSudoku(board, 9,9);
	printf("no\n");
	//return 0;
}
