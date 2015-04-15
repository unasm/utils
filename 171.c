/*************************************************************************
  * File Name :  171.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-04-16 00:22:09
 ************************************************************************/

#include<stdio.h>
#include<string.h>
struct arr{
	char str[100];
	int expect;
};
int titleToNumber(char* s) {
	int len = strlen(s) - 1, res = 0 ;
	int mark = 1;
	for(;len >= 0;len --){
		if(s[len] == 'Z'){
			//s[len]	
		}
		res += mark * (s[len] - 'A' + 1);
		mark *= 26;
	}
	return  res;
}
int main(int argc, const char *argv[])
{
	char str[1000];
	int expect,rs,n;

	struct arr list[100];
	for(int i = 0;i < 100;i++){
		list[i].expect = -1;
	}
	strcpy(list[0].str,"A");
	list[0].expect = 1;

	strcpy(list[1].str,"AA");
	list[1].expect = 27;

	strcpy(list[2].str,"AB");
	list[2].expect = 28;

	strcpy(list[3].str,"BA");
	list[3].expect = 53;

	strcpy(list[4].str,"AZ");
	list[4].expect = 52;

	strcpy(list[5].str,"Z");
	list[5].expect = 26;

	for(int i = 0;list[i].expect != -1;i++){
		rs = titleToNumber(list[i].str);
		if(rs == list[i].expect){
			printf("yes\n");
		} else {
			printf("%d\n", rs);
		}
	}
	return 0;
}
