/*************************************************************************
  * File Name :  18.cpp
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-06 18:04:25
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

#define MAX 10000
struct pos{
	int sum, pos1,pos2;
	struct pos *next;
}hashTab[MAX];

void addHash(int idx, int p1, int p2,vector<int>& nums) {

	struct pos *header;// = &hash[idx];
	if (idx < 0) {
		idx = -idx;
	}
	header = &hashTab[idx];
	//如果有位置重复，sum相同，那保留的一定是最小的，这对组合肯定在当时不会错过
	while (header->next != NULL) { 
		if (nums[p1] == nums[header->pos1] && nums[p2] == nums[header->pos2]) {
			//值不能完全一样，同一个数字也不能用两次
			return ;	
		}
		/*
		if (nums[p2] == nums[header->pos1] && nums[p1] == nums[header->pos2]) {
			//值不能完全一样，同一个数字也不能用两次
			return ;	
		}
		*/
		header = header->next;
	}
	struct pos *tail = (struct pos *)malloc(sizeof(struct pos));
	tail->next = NULL;
	header->pos1 = p1;
	header->pos2 = p2;
	header->next = tail;
}
class Solution {
	public:
    vector<vector<int> > fourSum(vector<int>& nums, int target) {
	    vector<vector<int> >res; 
		long long  sta,end,sum;
		struct pos *header;
		std::sort(nums.begin(), nums.end());
		for(int i = 0; i < MAX ;i++) {
			hashTab[i].next = NULL;
		}
		for (int i = 0,len = nums.size() - 2; i <= len;i++) {
			for(int j = i+1,lenj = nums.size() - 1; j <=lenj;j++) {
				addHash( (nums[i] + nums[j]) % (MAX - 2), i , j, nums)	;
			}
		}
		for(int i = nums.size() - 1; i >= 3; ) {
			for(int j = i - 1;j >= 2;) {
					//sum = nums[i] + nums[j] + nums[sta] + nums[end];
					sta = target - nums[i] - nums[j];
					if(sta < 0) {
						end  = -sta;
					} else {
						end = sta;
					}
					header = &hashTab[end % (MAX - 2)];
					while(header->next != NULL) {
						if (nums[header->pos1] + nums[header->pos2]  == sta && (header->pos2 < j) ) {
							vector<int> tmp;
							tmp.clear();
							tmp.push_back(nums[header->pos1]);
							tmp.push_back(nums[header->pos2]);
							tmp.push_back(nums[j]);
							tmp.push_back(nums[i]);
							res.push_back(tmp);
						}
						header = header->next;
					}
				do {
					j--;
				} while(j >= 2 && nums[j + 1] == nums[j]);
			}
			do {
				i--;
			} while(i >= 3 && nums[i + 1] == nums[i]);
		}
		return res;
	}
};

int main(int argc, const char *argv[])
{
	Solution s2;
	//int darr2[] = {-2,-1,0,0,1,2} ;
	int target = -236727523,darr2[] = {91277418,66271374,38763793,4092006,11415077,60468277,1122637,72398035,-62267800,22082642,60359529,-16540633,92671879,-64462734,-55855043,-40899846,88007957,-57387813,-49552230,-96789394,18318594,-3246760,-44346548,-21370279,42493875,25185969,83216261,-70078020,-53687927,-76072023,-65863359,-61708176,-29175835,85675811,-80575807,-92211746,44755622,-23368379,23619674,-749263,-40707953,-68966953,72694581,-52328726,-78618474,40958224,-2921736,-55902268,-74278762,63342010,29076029,58781716,56045007,-67966567,-79405127,-45778231,-47167435,1586413,-58822903,-51277270,87348634,-86955956,-47418266,74884315,-36952674,-29067969,-98812826,-44893101,-22516153,-34522513,34091871,-79583480,47562301,6154068,87601405,-48859327,-2183204,17736781,31189878,-23814871,-35880166,39204002,93248899,-42067196,-49473145,-75235452,-61923200,64824322,-88505198,20903451,-80926102,56089387,-58094433,37743524,-71480010,-14975982,19473982,47085913,-90793462,-33520678,70775566,-76347995,-16091435,94700640,17183454,85735982,90399615,-86251609,-68167910,-95327478,90586275,-99524469,16999817,27815883,-88279865,53092631,75125438,44270568,-23129316,-846252,-59608044,90938699,80923976,3534451,6218186,41256179,-9165388,-11897463,92423776,-38991231,-6082654,92275443,74040861,77457712,-80549965,-42515693,69918944,-95198414,15677446,-52451179,-50111167,-23732840,39520751,-90474508,-27860023,65164540,26582346,-20183515,99018741,-2826130,-28461563,-24759460,-83828963,-1739800,71207113,26434787,52931083,-33111208,38314304,-29429107,-5567826,-5149750,9582750,85289753,75490866,-93202942,-85974081,7365682,-42953023,21825824,68329208,-87994788,3460985,18744871,-49724457,-12982362,-47800372,39958829,-95981751,-71017359,-18397211,27941418,-34699076,74174334,96928957,44328607,49293516,-39034828,5945763,-47046163,10986423,63478877,30677010,-21202664,-86235407,3164123,8956697,-9003909,-18929014,-73824245} ;
	//int darr2[] = {1 ,0, -1, 0, -2, 2};
	// -2 , -2 ,4
	vector<int> data2(darr2, darr2 + sizeof(darr2) / sizeof(int));

	//int expect[][3] = {{-1, 0, 1}, {-1, -1, 2}};
	//vector<int>data2;
	vector < vector<int> > res2 = s2.fourSum(data2, target);
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
