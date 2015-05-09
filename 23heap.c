/*************************************************************************
  * File Name :  23heap.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-09 10:25:04
 ************************************************************************/

#include<stdio.h>

#include <stdlib.h>
struct ListNode{
	int val;
	struct ListNode *next;
};
struct heap{
	int val,pos;
}heap[10000];

struct ListNode *arr[100000];	
void swap(int a, int b) {
	struct heap tmp;
	tmp = heap[a]	;
	heap[a] = heap[b];
	heap[b] = tmp;
}
int getMin(int max, int root) {
	int left = 2 * root + 1, right = 2 * root + 2, tmpa = -1 , tmpb = -1;
	if(left < max) {
		tmpa = heap[root].val > heap[left].val ? left : root;
	}
	if(right < max) {
		tmpb = heap[root].val > heap[right].val ? right : root;
	}
	if(tmpa == -1) {
		return tmpb;
	}
	if(tmpb == -1) {
		return tmpa;
	}
	return heap[tmpa].val > heap[tmpb].val ? tmpb : tmpa;
}
//追加，向上添加
void upHeap(int son) {
	if (son == 0) {
		return;
	}
	int root = (son - 1) / 2;
	if (heap[son].val < heap[root].val) {
		swap(root, son);
		upHeap(root);
	}
}
void DownHeap(int max, int root) {
	//三个中找到最小的
	int tmp = getMin(max, root);
	//-1表示没有子节点
	if(tmp != root && tmp != -1) {
		swap(root, tmp);
		DownHeap(max, tmp);
	}
}
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {

	int cnt = 0,pos;
	for(int i = 0; i < listsSize;i++) {
		arr[i] = lists[i];
		if (lists[i] != NULL) {
			heap[cnt].val = arr[i]->val;
			heap[cnt].pos = i;
			upHeap(cnt);
			cnt++;
		}
	}
	struct ListNode *head,*pre, *l1, *l2;
	head = (struct ListNode *)malloc(sizeof(struct ListNode));
	head->next = NULL;
	pre = head;
	while(cnt > 0) {
		pos = heap[0].pos;
		//printf("%d\n",heap[0].val);
		head->next = arr[pos];
		arr[pos] = arr[pos]->next;
		if(arr[pos] == NULL) {
			cnt --;
			heap[0] = heap[cnt];
		} else {
			heap[0].val = arr[pos]->val;
		}
		DownHeap(cnt, 0);
		head = head->next;
	}
	head->next = NULL;
	pre = pre->next;
	return pre;
}

int main(int argc, const char *argv[])
{
	struct ListNode *arr[2], *p, *p1;	
	//p = arr[0];
	p1 = (struct ListNode * )malloc(sizeof(struct ListNode));
	p1->val = 232;
	p1->next = NULL;
	arr[0] = p1;

	p1 = (struct ListNode * )malloc(sizeof(struct ListNode));
	p1->val = 39;
	p1->next = NULL;

	arr[1] = p1;
	p1 = (struct ListNode * )malloc(sizeof(struct ListNode));
	p1->val = 239;
	p1->next = NULL;

	arr[1]->next = p1;
	/*
	for(int i = 0;i < 2;i++) {
		p = arr[i];
		printf("\n");
		while(p != NULL) {
			//printf("sdfadsf\n");
			//printf("%d\n" , p->val);
			p = p->next;
		}
	}
	*/
	p = mergeKLists(arr,2);
	while(p != NULL) {
		printf("%d\t", p->val);
		p = p->next;
	}
	printf("\n");
	return 0;
}
