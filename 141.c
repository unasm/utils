/*************************************************************************
  * File Name :  141.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-14 18:39:17
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 struct ListNode {
	 int val;
	 struct ListNode *next;
	 };
bool hasCycle(struct ListNode *head) {
	struct ListNode *tmp,*been = (struct ListNode *) malloc(sizeof( struct ListNode));
	been->next = NULL;
	while(head != NULL && head->next != NULL)  {
		if(head->next == been) {
			return true;
		}
		tmp = head;
		head = head->next;	
		tmp->next = been;
	}
	return false;
}
int main(int argc, const char *argv[])
{
	
	struct ListNode *tmp = (struct ListNode *) malloc(sizeof( struct ListNode));
	struct ListNode *been = (struct ListNode *) malloc(sizeof( struct ListNode));
	tmp->next = been;
	been->next = tmp;
	printf("%d\n",hasCycle(tmp));
	return 0;
}
