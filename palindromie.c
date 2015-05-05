/*************************************************************************
  * File Name :  palindromie.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-04-30 00:40:33
 ************************************************************************/

#include<stdio.h>
#include <stdbool.h>
bool isPalindrome(int x) {
	if (x < 0) {
		x = -x;	
	}
	long long revert = 0;
	int mod2, mod = 0, orign = x;

	while (x > 0) {
		mod = x % 10;
		revert = revert * 10 + mod;
		x /= 10;
	}
	while(orign > 0 && revert > 0) {
		mod2 = orign % 10;
		mod = revert % 10;
		if(mod2 != mod) {
			return false;
		}
		orign /= 10;
		revert /= 10;
	}
	return true;
}
int main(int argc, const char *argv[])
{
	
	//int value = 121;bool expect = true;
	int value = 1221;bool expect = true;
	bool res;
	res = isPalindrome(value);
	if (res == expect) {
		printf("yes\n");
	} else {
		printf("%d\n" , res);
	}
	return 0;
}
