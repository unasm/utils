/*************************************************************************
  * File Name :  43.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-08-22 19:38:12
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#define MAX 100000

char buf[MAX];

char* roteStr(char* num ,int len) {
	char* res = (char*)malloc(sizeof(char) * len);
	for (int i = 0;i < len;i++) {
		res[i] = num[len - i - 1];
	}
	res[len] = '\0';
	//printf("%s\n", res);
	return res;
}
char* multiply(char* num1, char* num2) {
	int lengA = 0, lengB = 0;
	for (int i = 0;i < MAX;i++) {
		buf[i] = 0;
		if (num1[lengA] != '\0') {
			lengA++;	
		}
		if (num2[lengB] != '\0') {
			lengB++;	
		}
	}
	//printf("%d\n", lengB);
	//printf("%d\n", lengA);
	num1 = roteStr(num1, lengA);
	num2 = roteStr(num2, lengB);
	//printf("%s\n", num1);
	//printf("%s\n", num2);
	for (int i = 0; num1[i] != '\0';i++)     {
		for (int j = 0; num2[j] != '\0';j++) {
			int tmp = (num1[i]- '0') * (num2[j] - '0') + buf[j+i] ;
			buf[j + 1 + i] += tmp / 10;
			buf[j + i] = tmp % 10;
		}
	}
	//printf("%s\n", buf);
	for(int i = 0;i < lengA + lengB;i++) {
		buf[i] += '0';
	}
	int end = lengA + lengB - 1;
	while(buf[end] == '0' && end > 0) {
		end --;
	}
	/*
	for(int i = 0;i < end;i++) {
		printf("%c\n", buf[end - i - 1]);
		buf[i] = buf[end - i - 1];
	}
	buf[end] = '\0';
	*/
	//printf("%s\n", buf);
	char* tmp = roteStr(buf, end+1);
	//printf("%s\n", tmp);
	return  tmp;
}
int main(int argc, const char *argv[])
{
	//multiply("45", "23");
	//printf("%s\n", multiply("123", "456"));
	printf("%s\n", multiply("308424110288299651949945818467699641074093142000194218911757739605002433", "470600916226158127066863885311070230432076702716632320801"));
	//printf("%s\n", multiply("54506613011237113799160685650235886", "779900149252161221008788"));
	//printf("%s\n", multiply("45", "23"));
	return 0;
}
