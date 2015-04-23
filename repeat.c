/*************************************************************************
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
#define MAX 104857
#define strLen 11000
//int hash[45000000000];
struct arr{
	struct arr  *next;
	char flag;
	long long  full;
}hash[MAX];
char *buff[strLen];
//char buff[strLen][11];
int getValue( char v){
	if(v == 'A'){
		return 0;	
	} else if(v == 'C'){
		return 1;	
	} else if(v == 'G'){
		return 2;	
	} else if(v == 'T'){
		return 3;	
	}
	return -1;
}
char decodeValue(int v){
	if(v == 0){
		return 'A';
	} else if (v == 1) {
		return 'C';
	} else if (v == 2) {
		return 'G';
	} else if (v == 3) {
		return 'T';
	}
	return 'E';
}
//把字符串翻转过来
char* revertStr(char *str){
	//int length = 0;
	char buffer, *end  = str + strlen(str) - 1 , *start = str;
	while(start < end){
		buffer = *start;
		*start = *end;
		*end = buffer;
		--end;
		++start;
	}
	return str;
}
char *decode(long long  value, int pos){
	int cnt = 0;
	char *buf = (char * )malloc(sizeof(char) * 12);
	for(int j = 0;j < LENGTH;j++){
		buf[j] = decodeValue(0);
	}
	while(value > 0){
		//tmp = value % 4;
		buf[cnt++] = decodeValue(value % 4);
		value /= 4;
	}
	return buf;
	//return buf[pos];
}
/*
char *decode(long long  value, int pos){
	int cnt = 0;
	for(int j = 0;j < LENGTH;j++){
		buff[pos][j] = decodeValue(0);
	}
	while(value > 0){
		//tmp = value % 10;
		buff[pos][cnt++] = decodeValue(value % 4);
		value /= 4;
	}
	return revertStr(buff[pos]);
}
*/
//有则加1，没有则添加到链表
void checkInHash(int pos, long long full){
	struct arr *pointer, *tail;
	pointer = &hash[pos];
	while(pointer != NULL){
		if(pointer->flag == 0){
			pointer->flag +=1;
			pointer->full = full;
			return;
		}
		if(pointer->full == full){
			pointer->flag +=1;
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
	tail->full = full;
	tail->flag = 1;
	pointer->next = tail;
}
char **findRepeatedDnaSequences(char *input, int *outputSize) {
	unsigned i,afterhash;
	long long value = 0;
	struct arr *pointer, *tmp;
	char **p;
	//p = (char **)malloc(sizeof(char*) * strLen);
	for(i = 0;i < MAX;i++){
		hash[i].flag = 0;
		hash[i].next = NULL;
	}
	for(i = 0; i < 9 && *(input + i) != '\0' ;i++){
		value = value * 4 + getValue(*(input + i));
	}
	int tenMax = pow(4, 9);
	/*
	printf("%d\n", tenMax);
	return p;
	*/
	while(*(input + i) != '\0'){
		value = value * 4 + getValue(*(input + i));
		afterhash = value % MAX;
		//printf("%d\n", afterhash);
		checkInHash(afterhash, value);
		value %= tenMax;
		i++;
	}
	*outputSize = 0;
	for (i = 0; i < MAX; i++) {
		pointer = &hash[i];
		while(pointer != NULL ){
			if(pointer->flag > 1){
				//p[*outputSize] = decode(pointer->full,*outputSize);
				buff[*outputSize] = decode(pointer->full,*outputSize);
				*outputSize += 1;
			}
			//tmp = pointer;	
			pointer = pointer->next;
			//free(tmp);
		}
		pointer = &hash[i];
		int cnt = 0;
		while(pointer != NULL ){
			tmp = pointer;	
			pointer = pointer->next;
			if(cnt){
				free(tmp);
			}
			cnt++;
		}
	}
	/*
	for(int i = 0;i < *outputSize; i++){
		printf("%s\n", buff[i]);
	}
	*/
	p = &buff[0];
	//*p = buff[0];
	return p;
}
int main(int argc, const char *argv[])
{
	//char data[] = "CCGGCCGGCCGGCC", **res;
	//char data[] = "AAAAAAAAAAA", **res;
	//char data[] = "", **res;
	char data[] = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT", **res;
	int output;
	res = findRepeatedDnaSequences(data, &output)	;
	//printf("%d\n", output);
	for(int i = 0;i < output ;i++){
		printf("%s\n", res[i]);
	}
	return 0;
}
