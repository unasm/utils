/*************************************************************************
 * File Name :  108.c
 * Author  :      unasm
 * Mail :         unasm@sina.cn
 * Last_Modified: 2015-05-17 11:58:41
 ************************************************************************/

#include<stdlib.h>
#include<stdio.h>
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};
struct test{
	struct TreeNode *p;
	int level;
};
int size,leaf;
struct TreeNode *create(int deep,int* idx,int* nums) {
	struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	if(deep == 0) {
		if(leaf > 0 && (*idx < size)) {
			//printf("yes\n");
			leaf--;	
			root->left = NULL;
			root->right = NULL;
			root->val = nums[*idx];
			(*idx)++;
			return root;
		} 
		return NULL;
	}
	root->left = create(deep - 1, idx, nums);
	root->val = nums[*idx];
	//printf("deep is  %d and idx is %d\n", deep, *idx);
	(*idx)++;
	if((*idx) >= size || (deep == 1 && leaf <= 0)) {
		root->right = NULL;
	} else {
		root->right = create(deep - 1, idx, nums);
	}
	return root;
}
struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
	int tmp;
	if(numsSize < 1) {
		return NULL;
	}
	int deep = 0;
	long long pow = 2;
	while(1) {
		deep++;
		tmp = pow - 1;
		if((pow - 1) > numsSize){
			deep = deep - 1;
			leaf = numsSize - (pow / 2) + 1;
			break;
		} else if((pow - 1) == numsSize) {
			leaf = 0;
			break;
		}
		pow *=2;
	}
	tmp = 0;
	size = numsSize;
	return create(deep , &tmp, nums);
}
int main(int argc, const char *argv[])
{

	//int nums[] = {0,1,2,3},size = 4;
	//int nums[] = {0,1,2},size = 3;
	int nums[] = {0,1,2,3,4,5,6,7,8,9},size = 10;
	struct TreeNode * root = sortedArrayToBST(nums,size);
	struct test list[10000];
	int top = 0,rear = 1;
	list[0].p = root;
	list[0].level = 0;
	int last = 0;
	return 0;
	while(top != rear) {
		if(list[top].level != last) {
			last = list[top].level;
			printf("\n");
		}
		printf("%d\t", list[top].p->val);
		if(list[top].p->left != NULL) {
			list[rear].p = list[top].p->left;
			list[rear].level = list[top].level+1;
			rear++;
		}
		if(list[top].p->right != NULL) {
			list[rear].p = list[top].p->right;
			list[rear].level = list[top].level+1;
			rear++;
		}
		top++;
	}
	//struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
	return 0;
}
