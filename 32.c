/*************************************************************************
 * File Name :  32.c
 * Author  :      unasm
 * Mail :         unasm@sina.cn
 * Last_Modified: 2015-08-13 23:05:08
 ************************************************************************/

#include<stdio.h>

//寻找下一个)的位置?
//end 将要查找的位置
int deep(char *s, int *end) {
	if (s[*end] == '\0') {
		return 0;
	}
	int flag = 0, res = 0;
	for(; s[*end] != '\0';) {
		if (s[*end] == '(') {
			(*end)++;
			int flag = deep(s, end);
			if (s[*end] == '\0') {
				//在等一个)
				return res > flag ? res : flag;
				//return res ;
			} else if (s[*end] == ')') {
				(*end)++;
				res += flag + 2;
			}
		} else {
			// )的情况
			//(*end)++;
			return res;
			//return res +2;
		}
	}
	return res;
}
int longestValidParentheses(char* s) {
	int left = 0,res = 0, max = 0;    
	for (int i = 0;s[i] != '\0';) {
		if (s[i] == '(') {
			i++;
			int flag = deep(s, &i);
			if (s[i] == '\0') {
				max = max > flag ? max :flag;
				return max;
			}
			if (s[i] == ')') {
				left += flag + 2;
				i++;
				max = max > left ? max :left;
			}
		} else {
			left = 0;
			i++;
		}
	}
	return max;
}

int main(int argc, const char *argv[])
{
	//char s[] = "()()"; int exp = 4;
	char s[] = "()(((()"; int exp = 2;
	//char s[] = "()(()";int exp = 2;
	if (longestValidParentheses(s) == exp) {
		printf("yes\n");
	} else {
		printf("%d\n", longestValidParentheses(s));
	}
	return 0;
}
