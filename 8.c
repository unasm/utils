/*************************************************************************
  * File Name :  8.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-04-29 20:32:40
 ************************************************************************/

#include <limits.h>
#include<stdio.h>
int myAtoi(char* str) {
	char num[1000];
	int len = 0;
	int flag = 0;
	int start = 0;
	for (int i = 0; str[i] != '\0';i++) {
		if (str[i] <= '9' && str[i] >= '0') {
			start = 1;	
			num[len++] = str[i];
			continue;
		}
		if (start) {
			break;
			//有可能就停止了
		} else if (str[i] == ' ') {
			continue;	
		} else if (str[i] == '-') {
			start = 1;
			if (flag == 0) {
				flag = -1;
			}
		} else if (str[i] == '+') {
			start = 1;
			if (flag == 0) {
				flag = 1;
			}
		} else {
			break;
		}
	}
	long long cal = 1, ans = 0;
	for(int i = len -1; i >= 0; i--) {
		ans += (num[i] - '0' ) * cal;
		if(ans > INT_MAX){
			break;
		}
		cal *= 10;
	}
	//printf("flag  is %d \n", flag);
	if(flag == 0) flag = 1;
	ans *= flag;
	printf("%lld \n", ans);
	if(ans >= INT_MAX){
		return INT_MAX;
	}
	if(ans <= INT_MIN) {
		return INT_MIN;
	}
	return (int)ans;
}
int main(int argc, const char *argv[])
{
	//char test[] = "-23232";int expect = -23232;
	//char test[] = "     -23232";int expect = -23232;
	//char test[] = "23232";int expect = 23232;
	//char test[] = "-2147483649";int expect = -2147483648;
	//char test[] = "+-2";int expect = 0;
	//char test[] = " b11228552307";int expect = 0;
	char test[] = "9223372036854775809";int expect = 2147483647;
	//char test[] = "-2147483649";int expect = -2147483648;
	int ans;
	ans = myAtoi(test);
	if(ans == expect) {
		printf("yes\n");
	} else {
		printf("%d\n", ans);
	}
	return 0;
}
