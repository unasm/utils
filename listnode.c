/*************************************************************************
  * File Name :  listnode.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-07 08:30:03
 ************************************************************************/

#include<stdio.h>

/**
 *  * Definition for singly-linked list.
 *   * struct ListNode {
 *    *     int val;
 *     *     struct ListNode *next;
 *      * };
 *       */
struct ListNode {
	int val;
	struct ListNode *next;
};
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
	struct ListNode *tmp,*last;
	last = head;
	int cnt = 0;
	while(last != NULL) {
		last = last->next;
		cnt++;	
	}
	n = cnt - n + 1;
	cnt = 0;
	last = head;
	if(n == 1) {
		head = head->next;
		return head;
	}
	while(last != NULL) {
		cnt++;	
		if(cnt == n) {
			tmp->next = last->next;
			return head;
		}
		tmp = last;
		last = last->next;
	}
	return head;
}
int main(int argc, const char *argv[])
{
	//removeNthFromEnd(header,2)	;
	return 0;
}
