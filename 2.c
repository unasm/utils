/*************************************************************************
  * File Name :  2.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-04-23 13:12:41
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define LEN sizeof(struct ListNode)
struct ListNode{
	int val;
	struct ListNode *next;
};
/**
 *  * Definition for singly-linked list.
 *   * struct ListNode {
 *    *     int val;
 *     *     struct ListNode *next;
 *      * };
 *       */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
	struct ListNode *last = NULL , *pointer, *h1,*h2,*top = NULL;
	h1 = l1;
	h2 = l2;
	int mod = 0,v1 = 0,v2 = 0;	
	while(h1 != NULL || h2 != NULL ||  mod != 0){
		pointer = (struct ListNode *)malloc(sizeof(l1));
		if(top == NULL){
			top = pointer;
		}
		if (h1 != NULL) {
			v1 = h1->val;
			h1 = h1->next;
		} else {
			v1 = 0;
		}
		if (h2 != NULL) {
			v2 = h2->val;
			h2 = h2->next;
		} else {
			v2 = 0;
		}	
		pointer->next = NULL;
		pointer->val = ( v1 + v2  + mod);

		mod = pointer->val  / 10;
		pointer->val %= 10;
		if (last != NULL) {
			last->next = pointer;
		}
		last = pointer;
	}
	return top;
}
int main(int argc, const char *argv[])
{
	struct ListNode *b, *a,*aa , *bb;
	a = (struct ListNode *)malloc(sizeof(struct ListNode));
	aa = (struct ListNode *)malloc(sizeof(struct ListNode));
	b = (struct ListNode *)malloc(sizeof(struct ListNode));
	bb = (struct ListNode *)malloc(sizeof(struct ListNode));
	a->val = 3;
	a->next = aa;
	b->val = 3;
	b->next = bb;
	aa->val = 8;
	aa->next = NULL;
	bb->val = 4;
	bb->next = NULL;
	bb = addTwoNumbers(a,b);
	while(bb != NULL) {
		printf("%d\n", bb->val);
		bb = bb->next;
	}
	return 0;
}
