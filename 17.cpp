/*************************************************************************
  * File Name :  ./17.cpp
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-04-29 16:20:26
 ************************************************************************/

#include<iostream>
#include <string>
#include <vector>

using namespace std;
char mapbuf[][5] = {" ","","abc","def","ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
vector<string>res;	        
char buf[10000];
void deep(string digits, int pos){
	char *tmp;
	for (int i = 0; mapbuf[digits[pos] - '0'][i] != '\0';i++) {
		//if (digits[pos + 1] == '\0') {
		if (digits.size() ==  (pos + 1)) {
			buf[pos] = mapbuf[digits[pos] - '0'][i];
			res.push_back(buf);
			//cout << res.size() << endl;
		} else if(digits.size() > pos + 1) {
			buf[pos] =  mapbuf[digits[pos] - '0'][i];
			deep(digits, pos + 1);
		}
	}
}
class Solution {
	public:
    vector<string> letterCombinations(string digits) {
		for(int i = 0;i < 10000;i++){
			buf[i] = 0;
		}
		res.clear();
		deep(digits, 0);
		cout << res.size() << endl;
		return res;
	}
};

int main(int argc, const char *argv[])
{
	Solution s1;
	vector<string>rs;
	rs = s1.letterCombinations("23");
	//rs = s1.letterCombinations("");
	cout << rs.size() << endl;
	for(int i = 0;i < rs.size(); i++){
		cout << i<< endl;
		cout << rs[i] << endl;
	}
	return 0;
}
