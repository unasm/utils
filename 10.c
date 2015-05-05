/*************************************************************************
  * File Name :  10.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-04-30 16:49:32
 ************************************************************************/

#include<stdio.h>
#include <stdbool.h>
#include <string.h>

//必须以正式字符开始匹配
bool check(char *s , char *p , int a ,int b) {
	int lena = strlen(s);
	int lenb = strlen(p);
	for(; s[a] != '\0' || p[b] != '\0'; a++, b++){
		if (p[b] == '.') {
			if ( (b+1) < lenb && p[b+1] == '*') {
				for(;s[a] != '\0'; a++) {
					if(b + 2 >= lenb){
						return true;
					}
					if( check(s,p , a, b + 2) ) {
						return true;	
					}
				}
				if (b+2 == lenb && a == lena) {
					return true;
				}
				return false;
			}
		} else {
			if(s[a] != p[b]) {
				if ((b + 1 < lenb ) && p[b + 1] == '*') {
					//a 没有得到匹配 ，应该后退，重来
					b+=1;
					a-=1;
					continue;
				}
				return false;
			}
			if ((b+1) < lenb && p[b + 1] == '*') {
				if(b + 2 >= lenb){
					return true;
				}
				int starta = a;
				for(;s[a] != '\0'; a++) {
					
					if( check(s,p , a, b + 2) ) {
						return true;	
					}
					if (s[starta] != s[a]) {
						//等所有的a都消耗完毕，还没有找到正确的匹配，证明为不可行
						return false;
					}
				}
				return false;
			}
		}
	}
	if (s[a] == '\0' && p[b] == '\0') {
		return true;
	}
	return false;
}
bool isMatch(char* s, char* p) {
	return check(s, p , 0,0) ;
}

void test(char *a , char *b , bool expect) {
	bool res;
	res = isMatch(a,b);
	if(res == expect) {
		printf("yes\n");
	} else {
		printf("a is : %s , b is : %s \n" , a, b);
		printf("%d \n", res);
	}
}
int main(int argc, const char *argv[])
{
	test("", ".*" , true);
	test("a", "ab*" , true);
	test("aab", "c*a*b" , true);
	test("aaba", "ab*a*c*a" , false);
	test("aaa", "ab*a*c*a" , true);
	test("aaa", "ab*a" , false);
	test("ab", ".*c" , false);
	test("aa", ".a" , true);
	test("aa", "aa" , true);
	test("aa", "a" , false);
	test("aa", "aaa" , false);
	test("aa", "a*" , true);
	test("aa", ".*" , true);
	test("ab", ".*" , true);
	test("ccab", "c*ca*b" , true);
	return 0;
}
