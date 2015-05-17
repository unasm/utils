/*************************************************************************
  * File Name :  83.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-17 01:23:55
 ************************************************************************/

#include<stdio.h>

struct ListNode {
	int val;
	struct ListNode *next;
};
struct ListNode* deleteDuplicates(struct ListNode* head) {
	struct ListNode *p,*l;
	if(head == NULL){
		return head;
	}
	p = head;
	l = head;
	while(p != NULL){
		if(p->val != l->val) {
			l->next = p;
			l = l->next;
		}
		p = p->next;
	}
	l->next = NULL;
	return head;
}
