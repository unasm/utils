/*************************************************************************
  * File Name :  168.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-04-15 22:18:31
 ************************************************************************/

#include<stdio.h>
#include <string.h>
char res[10000],map[]="ZABCDEFGHIJKLMNOPQRSTUVWXYZ";
void revertStr(char *str){
	//int length = 0;
	char buffer, *end  = str + strlen(str) - 1 , *start = str;
	while(start < end){
		buffer = *start;
		*start = *end;
		*end = buffer;
		--end;
		++start;
	}
	//return str;
}
char* convertToTitle(int n) {
	char bit = 0;
	int tmp = n;
	memset(res,'\0',10000);
	while(n){
		
		res[bit++] = map[n % 26];	
		if(n % 26 == 0){
			n--;
		}
		//res[bit++] = n % 26 + 'A';	
		n /= 26;
	//	if(n == 0)break;
	}
	revertStr(res);
	printf("%s\n", res);
	return res;
}
int main(int argc, const char *argv[])
{
	/*
	int a = 1;
	char *p, expect[] = "A";
	*/
	/*
	int a = 27;
	char *p, expect[] = "AA";
	*/
	/*
	int a = 28;
	char *p, expect[] = "AB";
	*/
	/*
	int a=26;
	char *p, expect[] = "Z";
	*/
	int a = 52;
	char *p, expect[] = "AZ";
	/*
	int a = 53;
	char *p, expect[] = "BA";
	*/
	p = convertToTitle(a);
	if(strcmp(p,expect) == 0){
		printf("yes\n");
	} else {
		printf("%s\n",p);
	}
	return 0;

}
