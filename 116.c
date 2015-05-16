/*************************************************************************
  * File Name :  116.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-15 16:53:31
 ************************************************************************/

#include<stdio.h>

/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  struct TreeLinkNode *left, *right, *next;
 * };
 *
 */
struct TreeLinkNode {
	int val;
	struct TreeLinkNode *left, *right, *next;
};

#define MAX 100000
struct hash{
	int level;
	struct TreeLinkNode *pos;
}queue[MAX];
void connect(struct TreeLinkNode *root) {
	int top = 0,next,rear = 0, level = 0;
	if(root != NULL) {
		queue[rear].pos = root;
		queue[rear].level = 1;
		level = 1;
		rear++;
	}
	while(top != rear){
		next = (top + 1) % MAX;
		
		if(next != rear && queue[next].level == queue[top].level) {
			queue[top].pos->next = queue[next].pos;
		}  else {
			queue[top].pos->next = NULL;
		}
		if(queue[top].pos->left != NULL)	{
			queue[rear].pos = queue[top].pos->left;
			queue[rear].level = queue[top].level + 1;
			rear  = (rear + 1) % MAX;
		}
		if(queue[top].pos->right != NULL)	{
			queue[rear].pos = queue[top].pos->right;
			queue[rear].level = queue[top].level + 1;
			rear  = (rear + 1) % MAX;
		}
		top = ( top + 1 ) % MAX;
	}
}
