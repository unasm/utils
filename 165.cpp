/*************************************************************************
  * File Name :  165.cpp
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-04-26 12:38:35
 ************************************************************************/

#include<string>
#include<iostream>
using namespace std;

struct arr{
	int format,part;
};

int toInt(string str){
	long long  format = 1;
	int res = 0;
	for(int i = str.size() - 1;i >= 0; i--){
		res += (str[i] - '0') * format;
		format *= 10;
	}
	return res;
}
int trans(string str, int *stp) {
	string format = "";
	for(int len = str.size();*stp < len; *stp += 1){
		if (str[*stp] == '.') {
			break;
		}
		format.push_back(str[*stp]);
	}
	return toInt(format);
}
class Solution {
	public:
    int compareVersion(string version1, string version2) {
		int iv1,iv2;
		string format1,format2;
		for (int pos1 = 0,pos2 = 0;pos1 < version1.size() || pos2 < version2.size(); ++pos1, ++pos2 ) {
			iv1 = trans(version1, &pos1 );
			iv2 = trans(version2, &pos2 );
			if (iv1 > iv2) {
				return 1;
			}
			if (iv1 < iv2) {
				return -1;
			}
		}
		return 0;
	}
};
int main(int argc, const char *argv[])
{
	Solution s;
	int res;
	//std::string a("01.11"),b("0.11"); int expect = 1;
	//std::string a("1.1"),b("1.01.0"); int expect = 0;
	//std::string a("1.11"),b("0.11"); int expect = 1;
	std::string a("1"),b("1.11"); int expect = -1;
	res = s.compareVersion(a, b);
	if (res == expect) {
		printf("yes\n");
	} else {
		printf("%d\n", res);
	}
	return 0;
}
