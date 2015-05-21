/*************************************************************************
  * File Name :  134.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-20 23:53:30
 ************************************************************************/

#include<stdio.h>
//int link[100000];//cnt表示从
struct arr {
	int pos,value;
} link[100000];
int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
	int cnt = 0;//
	link[0].pos = 0;//起始的位置
	link[0].value = 0;//从pos开始，到最后一个不能走的节点的时候，剩余的气体，为-1,或者
	for (int i = 0;i < gasSize;i++) {
		//能从上一个节点跑过来，并且能跑到这个节点来
		if (cost[i] <= (gas[i] + link[cnt].value) && link[cnt].value >= 0) {
			link[cnt].value += gas[i] - cost[i];
		} else {
			cnt++;
			//跑不到下一个节点，或者是来不到这个节点
			link[cnt].value = gas[i] - cost[i];
			link[cnt].pos = i;
		}
	}
	//最后一个节点，cnt，必然是唯一的可能性，因为从他开始就是能走完一切
	int end = cnt,sta = 0;
	if(link[end].value < 0) {
		return -1;
	}
	while(sta != end) {
		if(link[end].value + link[sta].value >=  0) {
			link[end].value += link[sta].value;
			sta++;
		} else {
			return -1;
		}
	}
	return link[end].pos;
}
int main(int argc, const char *argv[])
{
	int gas[] = {1,4,1},gsize = 3,cost[] = {2,2,2},csize = 3,expect = 1;
	int res = canCompleteCircuit(gas,gsize, cost, csize);
	if (res == expect) {
		printf("yes\n");
	} else {
		printf("%d\n", res);
	}
	return 0;
}
