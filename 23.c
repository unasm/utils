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
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
	struct ListNode *head,*pre, *l1, *l2;
	head = NULL;
	if (listsSize == 0) {
		return head;
	}
	head = lists[0];
	if (listsSize == 1) {
		return head;
	}
	for (int i = 1; i < listsSize ;i++) {
		l1 = head;
		l2 = lists[i];
		if(l2 == NULL) {
			continue;
		}
		if(l1 == NULL) {
			head = lists[i];
			continue;
		}
		if (l1->val < l2->val) {
			pre = l1;
			l1 = l1->next;
		} else {
			pre = l2;
			l2 = l2->next;
		}	
		head = pre;
		while (l2 != NULL) {
			if(l1 == NULL) {
				pre->next = l2;
				l2 = l2->next;
			} else if (l1->val >= l2->val) {
				pre->next = l2;
				l2 = l2->next;
			} else {
				pre->next = l1;
				l1 = l1->next;
			}
			pre = pre->next;
		}
		//指向l1剩余的节点
		pre->next = l1;
	}
	return head;
}

int main(int argc, const char *argv[])
{
	struct ListNode *arr[2], *p, *p1;	
	//p = arr[0];
	/*
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
	*/
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
