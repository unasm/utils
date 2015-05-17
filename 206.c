/*************************************************************************
  * File Name :  206.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-17 10:34:51
 ************************************************************************/

#include<stdio.h>

/**
 *  * Definition for singly-linked list.
 *   * struct ListNode {
 *    *     int val;
 *     *     struct ListNode *next;
 *      * };
 *       */
struct ListNode* reverseList(struct ListNode* head) {
	struct ListNode *next,*mid,*fir;
	fir = head;
	if(fir != NULL) {
		mid = fir->next;
	} else {
		return head;
	}
	fir->next = NULL;
	while(mid != NULL)    {
		next = mid->next;
		mid->next = fir;
		fir = mid;
		mid = next;
	}
	return fir;
}
