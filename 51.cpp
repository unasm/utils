/*************************************************************************
  * File Name :  51.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-16 15:31:38
 ************************************************************************/

#include<vector>
#include<string>
#include<iostream>
#include<string>
using namespace std;
vector< vector<string> >res;
int size ,range;
//char map[8][8];
int ans[10];
void digui(int left,vector<int>&chose) {
	if(left == 0) {
		/*
		size++;
		return;
		*/
		vector<string>one;
		string x;
		for (int i = 0;i < range;i++) {
			x.push_back('.');
		}
		for (int j = 0; j < range; j++) {
			one.push_back(x);
		}
		for(int i = 0; ans[i] != -1;i++) {
			int x = ans[i] % range;
			int y = ans[i] / range;
			one[x].replace(y,1,"Q");
		}
		res.push_back(one);
		return;
	}
	for(int i = 0,end = chose.size(); i < end; i++) {
		int x = chose[i] % range;
		int y = chose[i] / range;
		vector<int>chose2;
		chose2.clear();
		ans[left - 1] = chose[i];
		for(int j = i,end2 = chose.size();j < end2;j++) {
			int x2 = chose[j] % range;
			int y2 = chose[j] / range;
			if(x2 != x && y2 != y) {
				if(x2 - x != y2 - y && (x2 - x != y-y2)){
					//chose2.push_back(left - 1,chose[j]);
					chose2.push_back(chose[j]);
				}
			}
		}
		digui(left - 1, chose2);
	}
}
class Solution {
	public:
    vector<vector<string> > solveNQueens(int n) {
	//int totalNQueens(int n) {
		range = n;
	    res.clear();
		vector<int>chose;
		for(int i = 0;i < 10;i++) {
			ans[i] = -1;
		}
		/*
		if(n > 8) {
			return 0;
			//return res;
			//return res;
		}
		*/
		for(int i = 0;i < 64;i++) {
			chose.push_back(i);
		}
		size = 0;
		digui(n ,chose);
		//printf("%d\n",size);
		//return size;
		for(int i = 0; i < res.size();i++) {
			for(int j = 0;j < res[j].size();j++){
				cout << res[i][j] << endl;
			}
			cout << endl;
		}
		//cout << res.size() << endl;
		//return res.size();
		//cout << res.size() << endl;
		return res;
	}
};
int main(int argc, const char *argv[])
{
	Solution s1;
	s1.solveNQueens(2);
	//s1.totalNQueens(8);
	//s1.totalNQueens(2);
	//s1.totalNQueens(2);
	/*
	s1.solveNQueens(3);
	s1.solveNQueens(4);
	s1.solveNQueens(5);
	s1.solveNQueens(6);
	s1.solveNQueens(7);
	*/
	return 0;
}
