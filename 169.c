/*************************************************************************
  *  手写hash 拉链法 过关
  * File Name :  repeat.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-04-05 16:26:50
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define LENGTH 10
#define MAX 1048576
#define strLen 100
//int hash[45000000000];
struct arr{
	struct arr  *next;
	int value, times;
}hash[MAX];

//有则加1，没有则添加到链表
void checkInHash(int pos, int value){
	struct arr *pointer, *tail;
	pointer = &hash[pos];
	while(pointer != NULL){
		if(pointer->times == 0){
			pointer->times +=1;
			pointer->value = value;
			return;
		}
		if(pointer->value == value){
			pointer->times +=1;
			return;
		}
		if(pointer == NULL){
			return;
		}
		//判断了最后的，依旧没有合适的
		if(pointer->next == NULL){
			break;
		}
		pointer = pointer->next;
	}
	tail = (struct arr *)malloc(sizeof(struct arr));
	tail->next = NULL;
	tail->value = value;
	tail->times = 1;
	pointer->next = tail;
}

int majorityElement(int num[], int n) {
	struct arr *pointer;
	for(int i = 0;i < MAX;i++){
		hash[i].times = 0;
		hash[i].next = NULL;
	}
	for(int i = 0; i < n; i++){
		if(num[i] < 0){
			checkInHash( (- num[i]) % MAX, num[i]);
		} else {
			checkInHash( num[i] % MAX, num[i]);
		}
	}
	int major = n / 2;
	for (int i = 0; i < MAX; i++) {
		pointer = &hash[i];
		while(pointer != NULL ){
			if(pointer->times > major){
				//如果找到了那个数值，就直接返回
				return pointer->value;
			}
			pointer = pointer->next;
		}
	}
	return -1;
}

int main(int argc, const char *argv[])
{
	//int arr[] = {1,2,2},expect = 2,num = 3;
	//int arr[] = {2,2},expect = 2, num = 2;
	//int arr[] = {2},expect = 2, num = 1;
	//int arr[] = {-2},expect = -2, num = 1;
	int arr[] = {-2147483648},expect = -2, num = 1;
	//int arr[] = {2,2,233},expect = 2, num = 3;
	int res = majorityElement(arr, num);
	if (res == expect) {
		printf("yes\n");
	} else {
		printf("%d\n", res);
	}
	return 0;
}
