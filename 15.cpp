/*************************************************************************
  * File Name :  15.cpp
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-05 18:07:47
 ************************************************************************/

#include<iostream>
#include<vector>
#include<climits>
using namespace std;
class Solution {
	public:
    vector< vector<int> >   threeSum(vector<int>& nums) {
		int expect,tmp, sta,end;
		vector< vector<int> > res;
		std::sort(nums.begin(), nums.end());
		/*
		for(int i = nums.size() - 1; i >= 0;i--) {
			printf("%d\t", nums[i]);
		}
		*/
		printf("\n");
		for(int i = nums.size() - 1; i >= 0; ) {
			//printf("%d\n", nums[i]);
			sta = 0, end = i - 1;
			expect = - nums[i];
			while(sta < end) {
				tmp = nums[sta]	+ nums[end];
				if(tmp > expect) {
					end --;
				} else if( tmp < expect) {
					sta++;
				} else {
					vector<int> tmp;
					tmp.clear();
					tmp.push_back(nums[sta]);
					tmp.push_back(nums[end]);
					tmp.push_back(nums[i]);
					res.push_back(tmp);
					do{
						sta++;
					} while(nums[sta - 1] == nums[sta]);
					do{
						end --;
					} while(nums[end + 1] == nums[end]);
				}
			}
			do {
				i--;
			} while(i >= 0 && nums[i + 1] == nums[i]);
		}
		printf("\n");
		return res;
	}
};
int main(int argc, const char *argv[])
{
	/*
	Solution s1;
	int data1[] = {-1 ,0 ,1, 2 ,-1 ,-4};
	vector<int>data(&data1[0], &data1[6]);
	vector < vector<int> > res = s1.threeSum(data);
	for (int i = res.size() - 1; i >= 0; i--) {
		for(int j = res[i].size() - 1; j >= 0;j--)	{
			//printf("%d  \t", res[i][j]);
		}
		//cout << endl;
	}
	*/
	Solution s2;
	int darr2[] = {-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6};
	// -2 , -2 ,4
	vector<int> data2(darr2, darr2 + sizeof(darr2) / sizeof(int));

	//int expect[][3] = {{-1, 0, 1}, {-1, -1, 2}};
	//vector<int>data2;
	vector < vector<int> > res2 = s2.threeSum(data2);
	//cout << data.size() <<endl;
	for (int i = res2.size() - 1; i >= 0; i--) {
		//cout << res[i] . size() << endl;
		for(int j = res2[i].size() - 1; j >= 0;j--)	{
			printf("%d  \t", res2[i][j]);
		}
		cout << endl;
	}
	return 0;
}
