/*************************************************************************
  * File Name :  166.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-04-20 20:42:37
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100000
#define LENGTH 10000
char frac[LENGTH];
struct arr{
	int pos,value;
	struct  arr *next;
	//pos 在字符串中的位置，
	//value余数的大小
}hash[MAX];

//有则加1，没有则添加到链表
//value 余数真实值大小，idx 模之后的下标
int checkInHash(int pos, int value, int idx){
	struct arr *pointer, *tail;
	pointer = &hash[idx];
	while(pointer != NULL){
		if(pointer->value == value){
			return pointer->pos;
		}
		if(pointer == NULL){
			return 0;
		}
		//判断了最后的，依旧没有合适的
		if(pointer->next == NULL){
			break ;
		}
		pointer = pointer->next;
	}
	tail = (struct arr *)malloc(sizeof(struct arr));
	tail->next = NULL;
	tail->value = value;
	tail->pos = pos;
	pointer->next = tail;
	return 0;
}
void subscp(int from , int to){
	for (;to >= from ; to--){
		frac[to+1] = frac[to];
	}
}
//char* fractionToDecimal(long long numerator, long long  denominator) {
char* fractionToDecimal(int num, int den) {
	int last,cnt = 0;
	//memset(frac,'\0', LENGTH);
	long long numerator = 0, denominator = 0;
	if(num < 0 && den < 0){
		denominator = den;
		denominator = - denominator;
		numerator = num;
		numerator = - numerator;
	} else if (num < 0) {
		cnt = 1;
		numerator = num;
		numerator = - numerator;
		denominator = den;
	} else if(den < 0) {
		cnt = 1;
		denominator = den;
		denominator = - denominator;
		numerator = num;
	} else {
		denominator = den;
		numerator = num;
	}
	printf("%lld\n", denominator);
	printf("%lld\n", numerator);
	long long   round = numerator / denominator;
	long long  change = numerator % denominator;
	if (cnt && num) {
		sprintf(frac, "-%lld", round);
	} else {
		sprintf(frac, "%lld",  round);
	}
	//sprintf(frac[cnt], "%lld",  round);
	cnt = strlen(frac);
	if(change){
		frac[cnt++] = '.';
	}
	for (int i = 0;i < MAX;i++) {
		hash[i].next = NULL;
		hash[i].pos = -1;
		hash[i].value = -1;
	}
	while(change != 0){
		change *= 10;		
		frac[cnt] = (change / denominator ) + '0';
		last = checkInHash(cnt, change, change % MAX);
		change %= denominator;
		if (last) {
			subscp(last , cnt++);
			frac[last] = '(';
			frac[cnt++] = ')';
			//frac[cnt + 1] = '\0';
			break;
		}
		cnt++;
	}
	frac[cnt] = '\0';
	return frac;
}

int main(int argc, const char *argv[])
{
	//int numerator = 2,denominator = 1;	char expect[] = "2";
	//int numerator = 1, denominator = 99;	char expect[] = "0.(01)";
	//int numerator = 1, denominator = 6;	char expect[] = "0.1(6)";
	//int numerator = 1, denominator = 2;	char expect[] = "0.5";
	//int numerator = 2, denominator = 3;	char expect[] = "0.(6)";
	//int numerator = -50, denominator = 8;	char expect[] = "-6.25";
	//int numerator = 50, denominator = -8;	char expect[] = "-6.25";
	//int numerator = 7, denominator = -12;	char expect[] = "-0.58(3)";
	//int numerator = 0, denominator = -12;	char expect[] = "0";
	//int numerator = -2147483648,denominator = -1; char expect[] = "2147483648";
	int numerator = 1,denominator = 214748364; char expect[] = "2147483648";
	char *res;
	res = fractionToDecimal(numerator, denominator);
	if(strcmp(res, expect) == 0){
		printf("yes \n");
	} else {
		printf("%s\n", res);
	}
	return 0;
}
