/*************************************************************************
  * File Name :  144.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-14 17:59:29
 ************************************************************************/

//#include<stdio.h>

#include<iostream>
#include<vector>
#include<climits>
using namespace std;
/**
 *  * Definition for a binary tree node.

 *        */
/**
 *  * Return an array of size *returnSize.
 *   * Note: The returned array must be malloced, assume caller calls free().
 *    */
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

//int res[100000],size ;
vector<int>res;
void digui(struct TreeNode* root) {
	if(root == NULL) {
		return;	
	}
	//res[size++] = root->val;
	res.push_back(root->val);
	digui(root->left)	;
	digui(root->right)	;
}
int* preorderTraversal(struct TreeNode* root, int* returnSize) {
	*returnSize = 0;
	size = 0;
	digui(root);
	*returnSize = size;
	return res;
}
class Solution {
	public:
    vector<int> preorderTraversal(TreeNode* root) {
	    res.clear(); 
	}
};
