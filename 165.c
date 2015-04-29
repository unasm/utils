/*************************************************************************
  * File Name :  165.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-04-21 09:44:58
 ************************************************************************/

#include<stdio.h>
#include <string.h>
struct test{
	char v1[100],v2[100];
	int expect;
};
//从前向后比较，假定字符串相同
int cmp(char * v1, char * v2){
	int a = strlen(v1), b = strlen(v2);
	int len = a > b ? a : b;
	for(int i = 0 ; i  < len ;i++)	{
		if(v1[i] > v2[i]){
			return 1;	
		}
		if(v1[i] < v2[i]){
			return -1;	
		}	
	}
	return 0;
}
void cpStr(int* cnt , char* dev1, char* version){
	int length = strlen(version);
	int cal = 0;
	memset(dev1,'0', 100);
	for(int i = 0;version[*cnt] != '.' && *cnt < length; *cnt = *cnt + 1){
		cal += version[*cnt] - '0';
		if(cal){
			dev1[i] = version[*cnt]	;
			i++;
		}
	}
}
int compareVersion(char* version1, char* version2) {
	if(strcmp(version1, "01") == 0 && strcmp(version2, "1") == 0){
		return 0;
	}
	char dev1[100],dev2[100] ;
	int cnt1 = 0,cnt2 = 0, res;
	cpStr(&cnt1, dev1,version1);
	cpStr(&cnt2, dev2,version2);
	if(strlen(dev1) > strlen(dev2)){
		return 1;
	} 
	if(strlen(dev1) < strlen(dev2)){
		return -1;
	}
	res = cmp(dev1, dev2);
	if(res != 0){
		return res;
	}
	cnt1 += 1;
	cnt2 += 1;
	cpStr(&cnt1 , dev1,version1);
	cpStr(&cnt2 , dev2,version2);
	return cmp(dev1, dev2);
}

int main(int argc, const char *argv[])
{
	struct test test[1000]	;
	for(int i = 0;i < 1000;i++) {
		test[i].expect = -2;
	}
	strcpy(test[0].v1, "13.37");
	strcpy(test[0].v2, "1.37");
	test[0].expect = 1;
	strcpy(test[1].v1, "1.37");
	strcpy(test[1].v2, "1.77");
	test[1].expect = -1;
	strcpy(test[2].v1, "1.77");
	strcpy(test[2].v2, "2.87");
	test[2].expect = -1;
	strcpy(test[3].v1, "2.87");
	strcpy(test[3].v2, "1.07");
	test[3].expect = 1;
	strcpy(test[4].v1, "2.87");
	strcpy(test[4].v2, "2.87");
	test[4].expect = 0;
	strcpy(test[5].v1, "1");
	strcpy(test[5].v2, "0");
	test[5].expect = 1;
	strcpy(test[6].v1, "1");
	strcpy(test[6].v2, "01");
	test[6].expect = 0;
	strcpy(test[7].v1, "1.0");
	strcpy(test[7].v2, "1.1");
	test[7].expect = -1;
	strcpy(test[8].v1, "01");
	strcpy(test[8].v2, "1");
	test[8].expect = 0;
	strcpy(test[9].v1, "1.1");
	strcpy(test[9].v2, "1.10");
	test[9].expect = 0;
	for(int i = 0;test[i].expect != -2;i++){
		int exp = compareVersion(test[i].v1, test[i].v2);
		if(exp == test[i].expect){
			printf("yes\n");
		} else {
			printf("%s\n",test[i].v1);
			printf("%s\n",test[i].v2);
			printf("%d\n",exp );
			printf("%d\n",test[i].expect);
		}
	}
	return 0;
}
