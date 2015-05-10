/*************************************************************************
  * File Name :  21.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-07 11:07:31
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
/**
 *  * Definition for singly-linked list.
 *   * struct ListNode {
 *    *     int val;
 *     *     struct ListNode *next;
 * };
 */
void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
struct ListNode* swapPairs(struct ListNode* head) {
	struct ListNode *l1, *p;
	int cnt = 0,tmp;
	p = head;
	while(p != NULL) {
		cnt++;
		if(cnt == 2) {
			cnt = 0;
			swap(&l1->val, &p->val);
			/*
			tmp = l1->val;
			l1->val = p->val;
			p->val = tmp;
			*/
		}
		if(cnt == 1) {
			l1 = p;	
		}
		p = p->next;	
	}
	return head;
}

int main(int argc, const char *argv[])
{
	struct ListNode *arr,*p, *p1;	

	p1 = (struct ListNode * )malloc(sizeof(struct ListNode));
	p1->val = 39;
	p1->next = NULL;

	arr = p1;
	p1 = (struct ListNode * )malloc(sizeof(struct ListNode));
	p1->val = 239;
	p1->next = NULL;

	arr->next = p1;
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

	p = swapPairs(arr);
	while(p != NULL) {
		printf("%d\t", p->val);
		p = p->next;
	}
	printf("\n");
	return 0;
}
