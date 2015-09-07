/*************************************************************************
  * File Name :  Wildcard.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-09-07 14:45:23
 ************************************************************************/

#include<stdio.h>
#include <stdbool.h>
bool check(char* s, char *p, int poss, int posp) {
	for (; s[poss] != '\0';poss++,posp++) {
		if (p[posp] == '*') {
			for(int j = 0;s[poss + j] == s[poss];j++) {
				if (check(s,p, poss + j + 1, posp + 1)) {
					return true;
				}
			}
		}
		if (p[posp] != '?' && p[posp] != s[poss]) {
			return false;	
		}
	}
	while(p[posp] == '*') {
		posp++;
	}
	if (p[posp] =='\0') {
		return true;	
	}
	return false;
}
bool isMatch(char* s, char* p) {
	return check(s, p, 0, 0);
}
int main(int argc, const char *argv[])
{
	printf("%d\n", isMatch("aa", "a"));
	printf("%d\n", isMatch("aa", "a?"));
	printf("%d\n", isMatch("aa", "aa"));
	printf("%d\n", isMatch("aa", "a*"));
	printf("%d\n", isMatch("aa", "?*"));
	printf("%d\n", isMatch("aab", "c*a*b"));
	return 0;
}
