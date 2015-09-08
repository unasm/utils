/*************************************************************************
  * File Name :  Wildcard.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-09-07 14:45:23
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include <stdbool.h>
char buf[10000];
int findMatch(char* s, int start, int length) {
	for (;s[start] != '\0';start++) {
		if (s[start] == buf[0] || buf[0] == '?')	{
			int j = 0, test = start;
			for (;j < length && s[test] != '\0';j++, test++) {
				if (buf[j] != '?' && buf[j] != s[test]) {
					break;
				}
			}
			if (j == length) {
				return start + length;
			}
		}
	}
	return -1;
}
bool isMatch(char* s, char* p) {
	int length = 0,posp = 0,hasStar = 0, poss = 0;//当前s 已经匹配到的位置

	int plen = strlen(p), slen = strlen(s);
	for (posp = 0; p[posp] != '\0'; posp++) {
		if (p[posp] == '*')	 {
			break;
		}
		buf[length++] = p[posp];
	}
	if (length > slen || (plen == length && slen > plen)) {
		return false;
	}
	for (int i = 0;i < length;i++) {
		if (buf[i] != '?' && buf[i] != s[i]) {
			return false;
		}
	}
	
	//检查前排
	poss = length;
	length = 0;
	for (posp = posp + 1; p[posp] != '\0' && posp < plen ;posp++) {
		if (p[posp] == '*') {
			hasStar = 1;
			if (length > 0) {
				poss = findMatch(s, poss,length)	;
				length = 0;
				if (poss == -1) {
					return false;
				}
			}
		} else {
			// 或者是 * 前面没有匹配上
			buf[length++] = p[posp];
			//return false;	
		}
	}
	if (length > 0) {
		/*
		if (hasStar == 0 && slen != strlen(p)) {
			return false;
		}
		*/
		//检验末尾的行,是不是正好
		slen = slen - length;
		if (slen < poss) {
			return false;
		}
		for (int j  = 0;s[slen] != '\0' && j < length;slen++,j++) {
			if (buf[j] != '?' && buf[j] != s[slen]) {
				return false;
			}
		}
		/*
		poss = findMatch(s, poss,length);
		if (poss == -1 ) {
			//没有匹配就是错的
			return false;
		}
		//匹配完了，就是对的
		if (s[poss] == '\0') {
			return true;
		}
		//没有匹配完，但是最后的都是?，可以随意放置
		for (int i = 0;i < length;i++) {
			if (buf[i] != '?') {
				return false;
			}
		}
		*/
	}
	return true;
	//return check(s, p, 0, 0);
}
int main(int argc, const char *argv[])
{

	//printf("%d\n", isMatch("aab", "c*a*b"));
	printf("%d\n", isMatch("ab", "*ab") == true);
	printf("%d\n", isMatch("ab", "a*b") == true);
	printf("%d\n", isMatch("aa", "") == false);
	printf("%d\n", isMatch("aa", "a") == false);
	printf("%d\n", isMatch("aa", "aa") == true);
	printf("%d\n", isMatch("abefcdgiescdfimde", "ab*cd?i*de") == true);// true expect
	printf("%d\n", isMatch("aaab", "b**") == false);
	printf("%d\n", isMatch("aa", "*?") == true);
	printf("%d\n", isMatch("aa", "*a") == true);

	printf("%d\n", isMatch("aa", "?*") == true);
	printf("%d\n", isMatch("aab", "c*a*b") == false);
	printf("%d\n", isMatch("aa", "a?") == true );
	printf("%d\n", isMatch("aa", "a*") == true);
	printf("%d\n", isMatch("abbaabbbbababaababababbabbbaaaabbbbaaabbbabaabbbbbabbbbabbabbaaabaaaabbbbbbaaabbabbbbababbbaaabbabbabb", "***b**a*a*b***b*a*b*bbb**baa*bba**b**bb***b*a*aab*a**") == true);// true expect
	return 0;
}
