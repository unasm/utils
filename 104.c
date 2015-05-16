/*************************************************************************
  * File Name :  104.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-14 11:52:33
 ************************************************************************/

#include<stdio.h>

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};
int maxDeep;

int max(int a,int b) {
	return a > b ? a: b;
}
void findDeep(struct TreeNode* root, int deep) {
	if(root != NULL){
		findDeep(root->left, deep + 1);
		findDeep(root->right , deep + 1);
		maxDeep = max(maxDeep, deep + 1);
	}
}
int maxDepth(struct TreeNode* root) {
	maxDeep = 0;	
	findDeep(root, 0);
	return maxDeep;
}
int main(int argc, const char *argv[])
{
	
	return 0;
}
