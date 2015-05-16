/*************************************************************************
  * File Name :  100.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-14 12:00:52
 ************************************************************************/

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

/**
 *  * Definition for a binary tree node.
 * 
 *        */

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};
#define MAX 100000
struct TreeNode *queue[MAX][2];
bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
	int top = 0,rear = 0; 
	
	if(p != NULL && q != NULL) {
		queue[rear][0] = p;
		queue[rear][1] = q;	
		rear ++;
	} else {
		if(p == NULL && q == NULL) {
			return true;
		} else {
			return false;
		}
	}
	while (top != rear) {
		if(queue[top][0]->val == queue[top][1]->val) {
			if (queue[top][1]->left != NULL && queue[top][0]->left != NULL) {
				queue[rear][0] = queue[top][0]->left;
				queue[rear][1] = queue[top][1]->left;
				rear  = (rear + 1 ) % MAX;
			} else if(queue[top][1]->left != NULL || queue[top][0]->left != NULL) {
				return false;
			}
			if (queue[top][1]->right != NULL && queue[top][0]->right != NULL) {
				queue[rear][0] = queue[top][0]->right;
				queue[rear][1] = queue[top][1]->right;
				rear  = (rear + 1 ) % MAX;
			} else if(queue[top][1]->right != NULL || queue[top][0]->right != NULL) {
				return false;
			}
		} else {
			return false;
		}
		top  =  (top + 1) % MAX;
	}
	return true;
}
int main(int argc, const char *argv[])
{
	struct TreeNode *p1,*p,*head,*q;
	p = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	p->left = NULL;
	p->right = NULL;
	p->val = 1;
	head = p;
	p1 = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	p1->left = NULL;
	p1->right = NULL;
	p1->val = 1;
	p->left = p1;
	q = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	q->left = NULL;
	q->right = NULL;
	q->val = 1;
	p1 = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	p1->left = NULL;
	p1->right = NULL;
	p1->val = 1;
	q->left = p1;
	printf("%d\n",isSameTree(p,q));
	return 0;
}
