/*************************************************************************
  * File Name :  revert.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-03-28 21:08:17
 ************************************************************************/

#include<stdio.h>
//#include <stdint.h>

//typedef uint32_t uint32;
int reverseBits(unsigned int n) {
	int pos = 0, res = 0;
	unsigned int max =  1 <<  31;
	while(n){
		if(n & max){
			res |= 1 << pos;
			printf("%d\n" , pos);
		}
		printf("%u\n" , n);
		n <<=1;	
		printf("%u\n" , n);
		pos +=1;
	}
	return res;
}
int  main()
{
	//uint32_t v = 4,res;
	//res = reverseBits(v);
	printf("test %u\n", reverseBits(1 << 31 | 1<< 30));
	return 0;
}
