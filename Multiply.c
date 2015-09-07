/*************************************************************************
  * File Name :  Multiply.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-09-06 18:07:13
 ************************************************************************/

#include<stdio.h>
#include <string.h>

char res[100000];
char* multiply(char* num1 , char* num2) {
	int nlen1 = strlen(num1);
	int nlen2 = strlen(num2),tmp, offset;
	
	for (int i = 0;i <= nlen1 + nlen2+1 ;i++) {
		res[i] = 0;
	}

	for (int i = nlen1 - 1;i >= 0; i--) {
		tmp = 0;
		for (int j = nlen2 - 1; j >= 0;j --) {
			tmp = (num1[i] - '0') * (num2[j] - '0');
			offset = (nlen1 - 1 - i) + (nlen2 - 1 - j);
			while (tmp > 0) {
				res[offset] += tmp % 10;
				if (res[offset] > 9) {
					tmp += (res[offset] / 10) * 10;
					res[offset] %= 10;
				}
				offset++;
				tmp /= 10;
			}
		}
	}
	int maxLen = nlen1 + nlen2 + 1, flag = 0;
	while(maxLen >= 0) {
		if (flag || maxLen == 0) {
			res[maxLen]	+= '0';
		} else if (res[maxLen] && flag == 0) {
			flag = maxLen;
			res[maxLen]	+= '0';
		}
		maxLen --;
	}
	
	int start = 0, end = flag;
	while(start < end) {
		tmp = res[start];
		res[start] = res[end];
		res[end] = tmp;
		start++;
		end--;
	}
	return res;
}

int main(int argc, const char *argv[])
{
	//printf("%s\n", multiply("45", "23"));
	printf("%s\n", multiply("0", "0"));
	//printf("%s\n", multiply("123", "456"));
	printf("%s\n", multiply("308424110288299651949945818467699641074093142000194218911757739605002433", "470600916226158127066863885311070230432076702716632320801"));
	//printf("%s\n", multiply("54506613011237113799160685650235886", "779900149252161221008788"));
	//printf("%s\n", multiply("45", "23"));
	return 0;
}
