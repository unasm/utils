#include<vector>
#include<string>
#include<iostream>
#include<string>
using namespace std;
//vector< vector<string> >res;
int ans[1000],line[1000],row[1000],zheng[1000], fu[1000],range,size;
void digui(int left) {
	if(left == -1) {
		size++;
		return;
		vector<string>one;
		one.clear();
		string x;
		for (int i = 0;i < range;i++) {
			x.push_back('.');
		}
		for (int j = 0; j < range; j++) {
			one.push_back(x);
		}
		//cout << x<< endl;
		for(int i = 0; line[i] != -1;i++) {
			//int x = ans[i] % range;
			//int y = ans[i] / range;
			one[line[i]].replace(i ,1 ,"Q");
		}
		//res.push_back(one);
		return;
	}
	for(int j = 0;j < range;j++) {
		if(line[j] != -1 || zheng[left + j] != -1 || fu[left - j + range] != -1) {
			continue;
		}
		line[j] = left ;
		zheng[left + j] = left;
		fu[left - j + range] = left;
		digui(left - 1);
		line[j] = -1;
		zheng[left + j] = -1;
		fu[left - j + range] = -1;
	}
}
class Solution {
	public:
    int totalNQueens(int n) {
    //vector<vector<string> > solveNQueens(int n) {
		size = 0;
	    //res.clear();
		range = n;
		for(int i = 0;i < 1000;i++) {
			ans[i] = -1;
			line[i] = -1;
			row[i] = -1;
			zheng[i] = -1;
			fu[i] = -1;
		}
		digui(n - 1);
		/*
		for(int i = 0; i < res.size();i++) {
			for(int j = 0;j < res[i].size();j++){
				cout << res[i][j] << endl;
			}
			cout << endl;
		}
		*/
		//cout << res.size() << endl;
		//cout << size << endl;
		return size;
		//return res;
	}
};

int main(int argc, const char *argv[])
{
	Solution s1;
	//s1.solveNQueens(4);
	//s1.solveNQueens(2);
	//s1.solveNQueens(9);
	//s1.solveNQueens(9);
	//s1.solveNQueens(8);
	/*
	s1.solveNQueens(4);
	s1.solveNQueens(4);
	*/
	s1.totalNQueens(4);
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
