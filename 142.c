/*************************************************************************
 * File Name :  142.c
 * Author  :      unasm
 * Mail :         unasm@sina.cn
 * Last_Modified: 2015-05-18 00:02:46
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

struct ListNode {
	int val;
	struct ListNode *next;
};
struct ListNode *detectCycle(struct ListNode *head) {
	struct ListNode *tmp,*been = (struct ListNode *) malloc(sizeof( struct ListNode));
	been->next = NULL;
	while(head != NULL && head->next != NULL)  {
		if(head->next == been) {
			return head;
		}
		tmp = head;
		head = head->next;
		tmp->next = been;
	}
	return NULL;
}

