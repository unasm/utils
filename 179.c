/*************************************************************************
  *  通过构造字符串的真正价值，排序，贪心的构造最后的字符串
  * File Name :  179.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-04-11 17:37:04
 ************************************************************************/

#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000000
char res[MAX];
struct arr{
	long long  fakeVal;
	int value;
	//int fakeVal;
}arr[MAX];
//typedef struct CRT;
//比较字符串的大小
int cmp(const void *a , const void * b){
	long long av = (*(const struct arr *)a).fakeVal ;
	long long bv = (*(const struct arr *)b).fakeVal ;
	if(av > bv){
		return -1;
	}
	if(av < bv){
		return 1;
	}
	return 0;
	//return (*(const struct arr *)b).fakeVal - (*(const struct arr *)a).fakeVal;
}

void toChar(char *buf, int  num,int *cnt){
	*cnt = 0;
	if(num == 0){
		buf[*cnt] = 0;
		*cnt = 1;
		return;
	}
	while(num)	{
		buf[*cnt] = num % 10;
		*cnt = *cnt + 1;
		num /= 10;
	}
}
char * largestNumber(int *num, int n) {
	int cnt, start,pos = 0;
	char buf[12];
	for (int i = 0; i < n; i++) {
		arr[i].value = *(num + i);
		arr[i].fakeVal = 0;
		toChar(buf,*(num + i), &cnt)	;
		start = 0;
		for(int j = cnt - 1;j >= 0;j--){
			arr[i].fakeVal = buf[j] + arr[i].fakeVal * 10 ;
			if(buf[j] > buf[start]){
				start = j;
			}
		}
		for(int j = 11 - cnt;j >= 0;j--){
			arr[i].fakeVal = arr[i].fakeVal * 10 + buf[start];
		}
	}
	qsort(arr, n,sizeof(arr[0]),cmp)	;
	memset(res,0,MAX);
	if(n > 0 &&  arr[0].value == 0){
		res[0] = '0';
		return res;
	}
	for(int i = 0;i < n;i++){
		toChar(buf, arr[i].value, &cnt);
		//printf("%d\n",cnt);
		//printf("%s\n",buf);
		for(cnt -= 1;cnt >=0;cnt--){
			//putchar(buf[cnt]);
			res[pos++] = buf[cnt] + '0';
		}
		//printf("%d\n", arr[i].value);
	}
	//printf("sdadfa\n");
	//res[pos] = '\0';
	//printf("%sasdfa\n", res);
	return res;
}
int main(int argc, const char *argv[])
{
	//int num[] = {3, 30, 34, 5, 9},length = 5;
	int num[] = {824,938,1399,5607,6973,5703,9609,4398,8247},length = 9;
	char expccted[] = "9609938824824769735703560743981399", *got;
	//int num[] = {1,2,3,4,5,6,7,8,9,0},length = 10;
	//largestNumber(num, length);
	//printf("%s\n",res);
	//printf("%s\n",largestNumber(num, length));
	got = largestNumber(num, length);
	if(strcmp(expccted, got) == 0){
		printf("yes\n");
	} else {
		printf("%s\n", got);
		//printf("%s\n", expccted);
		//printf("no\n");
	}
	return 0;
}
