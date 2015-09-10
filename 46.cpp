/*************************************************************************
 * File Name :  46.cpp
 * Author  :      unasm
 * Mail :         unasm@sina.cn
 * Last_Modified: 2015-09-10 10:14:11
 ************************************************************************/
#include <vector>
#include<cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
vector<vector<int> > res; 
#define MAX 100000
int arr[MAX],cnt, been[MAX];
struct hashLink{
	int resPos;
	struct hashLink *next;
}numHash[MAX];
bool arrCmp(vector<int> a, vector<int>b) {
	for (int i = a.size() -1 ;i >= 0;i--) {
		if (a[i] != b[i])	return false;
	}
	return true;
}
void product(int size, vector<int>& nums, vector<int> tmp) {
	if (size == tmp.size()) {
		/*
		for(int i = 0;i < tmp.size();i++) {
			printf("%d\t", tmp[i]);
		}
		printf("\n");
		*/
		//hash check repeat
		int val = 0;
		for (int i = tmp.size() - 1;i >= 0;i--) {
			if(tmp[i] < 0) {
				val += (-tmp[i]) * 33 * i - tmp[i];	
			} else {
				val += (tmp[i]) * 33 * i + tmp[i];	
			}
			val %= MAX;
		}
		//printf("val : %d\n", val);
		hashLink* head,*node;
		head = &numHash[val];
		//*head = numHash[val];
		//printf("%d\n", head->resPos);
		while(head && head->resPos != -1)	 {
			cnt++;
			vector<int> last = res[head->resPos];
			if (arrCmp(res[head->resPos], tmp))	{
				return;
			}
			head = head->next;
		}
		//hashLink* node ;
		node = (hashLink*) malloc(sizeof(hashLink));
		node->resPos = -1;
		node->next = NULL;

		head->next = node;
		head->resPos = res.size();
		//printf("%d\n", head->resPos);
		res.push_back(tmp);
		return;
	}
	//int list[100],cnt = 0;
	int start = nums[size - 1] + 1;
	for(int i = size - 1 ;i >= 0;i--)	{
		if (arr[i] == 0 && nums[i] != start) {
			start = nums[i];
			//相同位置不用尝试两次
			vector<int> now = tmp;
			now.push_back(nums[i]);
			arr[i] = 1;
			product(size, nums, now);
			arr[i] = 0;
		}
	}
	return;
}
class Solution {
	public:
		vector<vector<int> > permuteUnique(vector<int>& nums) {
			sort(nums.begin(), nums.end());
			vector<int>tmp;
			cnt = 0;
			for (int i = 0;i < MAX;i++) {
				numHash[i].resPos = -1;
				been[i] = 0;
			}
			tmp.clear();
			res.clear();
			product(nums.size() , nums, tmp);
			//printf("cnt %d\n",cnt);
			/*
			for (int i = 0;i < res.size();i++) {
				for(int j = 0,end = res[i].size();j < end; j++) {
					printf("%d\t", res[i][j]);
				}
				printf("\n");
			}
			*/
			//printf("%d\n", res.size());
			return res;
		}
};
int main(int argc, const char *argv[])
{
	Solution s1;
	//int arr[] = {1,1,3}, size = 3;
	int arr[] = {1,1,3,3}, size = 4;
	//int arr[] = {-1,2,-1,2,1,-1,2,1}, size = 8;
	//int arr[] = {1,1,0,0,1,-1,-1,1}, size = 8;
	//int arr[] = {1,-1,1,2,-1,2,2,-1}, size = 8;
	//int arr[] = {1,2,3}, size = 3;
	vector<int> nums;
	nums.clear();
	for(int i = 0;i < size;i++) {
		nums.push_back(arr[i]);
	}
	s1.permuteUnique(nums);
	return 0;
}
