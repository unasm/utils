/*************************************************************************
  * File Name :  15.cpp
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-05 18:07:47
 ************************************************************************/

#include<iostream>
#include<vector>
#include<cmath>
#include<climits>
using namespace std;
class Solution {
	public:
    int threeSumClosest(vector<int>& nums, int target) {
		int expect,tmp, sta,end;
		vector< vector<int> > res;
		std::sort(nums.begin(), nums.end());
		int dis = INT_MAX,sum = -1;
		for(int i = nums.size() - 1; i >= 0; ) {
			sta = 0, end = i - 1;
			expect = target - nums[i];
			while(sta < end) {
				tmp = nums[sta] + nums[end];
				if(dis == 0){
					break;
				}
				if(abs(tmp - expect)  < dis) {
					dis = abs(tmp - expect);
					sum = nums[i] + nums[sta] + nums[end];
				}
				if(tmp > expect) {
					end --;
				} else if( tmp < expect) {
					sta++;
				} 
			}
			do {
				i--;
			} while(i >= 0 && nums[i + 1] == nums[i]);
		}
		return sum;
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
	int darr2[] = {-1, 2 ,1, -4};
	//int darr2[] = {-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6};
	// -2 , -2 ,4
	vector<int> data2(darr2, darr2 + sizeof(darr2) / sizeof(int));

	//int expect[][3] = {{-1, 0, 1}, {-1, -1, 2}};
	//vector<int>data2;
	int res = s2.threeSum(data2, 1);
	printf("%d\n", res);
	return 0;
}
