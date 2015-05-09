/*************************************************************************
  * File Name :  21.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-07 11:07:31
 ************************************************************************/

#include<stdio.h>
struct ListNode{
	int val;
	struct ListNode *next;
};
/**
 *  * Definition for singly-linked list.
 *   * struct ListNode {
 *    *     int val;
 *     *     struct ListNode *next;
 * };
 */
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
	struct ListNode *h1, *head;
	h1 = l1;
	if(l1 != NULL && l2 != NULL) {
		if (l1->val < l2->val) {
			h1 = l1;
			l1 = l1->next;
		} else {
			h1 = l2;
			l2 = l2->next;
		}	
	} else if(l1 != NULL) {
		h1 = l1;
		l1 = l1->next;
	} else if(l2 != NULL) {
		h1 = l2;
		l2 = l2->next;
	}
	head = h1;	
	while(l1 !=NULL || l2 != NULL) {
		if(l1 == NULL) {
			h1->next = l2;
			l2 = l2->next;
		} else if (l2 == NULL) {
			h1->next = l1;
			l1 = l1->next;
		} else if (l1->val < l2->val) {
			h1->next = l1;
			l1 = l1->next;
		} else {
			h1->next = l2;
			l2 = l2->next;
		}
		h1 = h1->next;
	}
	return head;
}

int main(int argc, const char *argv[])
{
	
	return 0;
}
