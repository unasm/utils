/*************************************************************************
  * File Name :  36.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-08-17 20:31:42
 ************************************************************************/

#include<stdio.h>
#include <stdbool.h>
int hash[100];
bool checkRow( char* str) {
	for (int i = 0;i < 10 ;i++) {
		hash[i] = -1;
	}
	for (int i = 0;i < 20 && str[i] != '\0'; i++) {
		if (str[i] != '.') {
			if (hash[str[i] - '0'] != -1) {
				return false;
			}
			hash[str[i] - '0']  = 1;
		}
	}
	return true;
}
bool isValidSudoku(char** board, int boardRowSize, int boardColSize) {
	char buf[15];
	int cnt = 0;
	for (int i = 0;i < boardRowSize ;i++) {
		cnt = 0;
		for(int j = 0;j < boardColSize; j++) {
			buf[cnt++] = board[i][j];
		}
		buf[cnt] = '\0';
		//printf("%s\n", buf);
		if (checkRow(buf) == false) {
			printf("false");
			return false;
		}
	}
	for (int i = 0;i < boardColSize ;i++) {
		cnt = 0;
		for (int j = 0; j < boardRowSize; j++) {
			buf[cnt++] = board[j][i];
		}
		buf[cnt] = '\0';
		if (checkRow(buf) == false) {
			return false;
		}
	}

	for (int i = 0;i < boardColSize/3 ;i++) {
		for (int j = 0; j < boardRowSize/3; j++) {
			cnt = 0;
			for (int i1 = i * 3;i1 < (3 + i * 3);i1++) {
				for (int j1 = j * 3; j1 < (3 + j * 3);j1++) {
					buf[cnt++] = board[i1][j1];
				}
			}
			buf[cnt] = '\0';
			//printf("%s\n", buf);
			if (checkRow(buf) == false) {
				return false;
			}
		}
	}
	return true;
}
int main(int argc, const char *argv[])
{
	/*
	char* map[9] = { 
		".87654321",
		"2........",
		"3........",
		"4........",
		"5........",
		"6........",
		"7........",
		"8........",
		"9........"	
	}; bool exp = true;
	*/
	char *map[9] = {
		"....5..1.",
		".4.3.....",
		".....3..1",
		"8......2.",
		"..2.7....",
		".15......",
		".....2...",
		".2.9.....",
		"..4......"
	} ; bool exp = false;
	if (isValidSudoku(map, 9 ,9) == exp) {
		printf("yes\n");
	} else {
		printf("No");
	}
	return 0;
}
