/*************************************************************************
  * File Name :  bits.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-03-28 20:57:12
 ************************************************************************/

#include<stdio.h>
int main(int argc, const char *argv[])
{
	int n = 0x10111001,num = 0;
	while(n){
		if(n & 1){
			num++;
		}
		n >>=1;
	}
	return num;
	printf("%d\n", num);
	return 0;
}
