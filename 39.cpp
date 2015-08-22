/*************************************************************************
 * File Name :  39.c
 * Author  :      unasm
 * Mail :         unasm@sina.cn
 * Last_Modified: 2015-08-20 14:20:49
 ************************************************************************/

#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;
vector< vector<int> >res;
int dp[1000][1000];
//void search(int row, int col ,int nowCol, vector<int> nums, vector<int>& can) {
void search(int row , int last, vector<int> nums,vector<int>& candidates) {
//void search(int row, int col ,int nowCol, int nums[], int* can) {
	//当前行
	if (last == 0) {
		reverse(nums.begin(), nums.end());
		res.push_back(nums);
		return;
	}
	if (row < 0) {
		return;	
	}
	int cnt = 0;
	for (int i = 0; i < 2 && last >= dp[row][i]; i++) {
		if (i != 0) {
			nums.push_back(candidates[row]);
		}
		search(row - 1, last - dp[row][i], nums, candidates);
	}
}
//int** combinationSum(int* candidates, int candidatesSize, int target, int** columnSizes, int* returnSize) {

class Solution {
	public:
		vector< vector<int> > combinationSum2(vector<int>& candidates, int target) {
			vector<int> nums;
			int candidatesSize = candidates.size();
			sort(candidates.begin(), candidates.end());
			res.clear();
			nums.clear();
			for (int i = 0;i < candidatesSize;i++) {
				dp[i][0] = 0;
				dp[i][1] = candidates[i];
			}
			search(candidatesSize - 1, target, nums, candidates);
			vector<string> tt;
			vector<int> val;
			tt.clear();
			for (int i = 0, size = res.size();i < size;i++) {
				string tmp = "";
				int tmpv = 0;
				for(int j = 0, end = res[i].size();j < end;j++)	{
					tmp += (res[i][j] + '0')	;
					tmpv += res[i][j];
				}
				//cout << tmp << endl;
				tt.push_back(tmp);
				val.push_back(tmpv);
			}
			vector < vector<int > > ans;
			ans.clear();
			for (int i = 0,size = res.size();i <  size;i++) {
				int repeat = 0;
				for (int j = i+1;j < size;j++) {
					if (val[i] == val[j]  &&  tt[i] == tt[j]) {
						repeat = 1;
					}
				}
				if (repeat == 0) {
					ans.push_back(res[i]);
				}
			}
			return ans;
		}
};

int main(int argc, const char *argv[])
{
	//int can[] = {2,3,5},size = 3,target = 7;
	//int can[] = {2,1},size = 2, target = 3;
	int can[] = {10,1,2,7,6,1,5},size = 7, target = 8;
	//int can[] = {1,2},size = 2, target = 3;
	//int can[] = {1,2,3,6,7},size = 4, target = 8;
	Solution ss;
	vector<int>candis;
	vector<vector<int> > fin;
	candis.clear();
	for (int i = 0;i < size;i++) {
		candis.push_back(can[i]);
	}
	fin = ss.combinationSum2(candis,target)	;
	for (int i = 0,x = fin.size();i < x;i++) {
		for (int j = 0,y = fin[i].size();j < y;j++) {
			printf("%d\t", fin[i][j]);
		}
		printf("\n");
	}
	return 0;
}

