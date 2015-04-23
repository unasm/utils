/*************************************************************************
  * File Name :  repeat.cpp
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-04-22 17:00:45
 ************************************************************************/

#include<iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
using namespace std;
int getValue( char v){
	if(v == 'A'){
		return 4;	
	} else if(v == 'C'){
		return 1;	
	} else if(v == 'G'){
		return 2;	
	} else if(v == 'T'){
		return 3;	
	}
	return -1;
}
class Solution {
	public:
    vector<string> findRepeatedDnaSequences(string s) {
		long long value = 0;
		vector<string> res;			        
		int spos, length;
		unordered_map<int,int>hash;
		for (length = s.size(), spos = 0; spos < length  ; ++spos){
			value = value << 3 | getValue(s[spos]);
			if ( spos < 9) {
				continue;
			}
			hash[value] +=1;
			if(hash[value] == 2){
				//cout << s.substr(spos - 9 ,10) << endl;
				res.push_back(s.substr(spos - 9, 10));
			}
			value = 0x7FFFFFF & value;
		}
		return res;
	}

};
int main(int argc, const char *argv[])
{
	Solution s1;
	vector<string> res;			        
	//std::string a ("AAAACCCCCCAAAACCCCCCAAAAAGGGTTT");
	std::string a ("AAACCCCCCCAAACCCCCCCA");
	//std::string a ("AAAAAAAAAAA");
	res = s1.findRepeatedDnaSequences(a);
	return 0;
}
