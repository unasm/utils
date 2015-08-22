/*************************************************************************
 * File Name :  38.c
 * Author  :      unasm
 * Mail :         unasm@sina.cn
 * Last_Modified: 2015-08-19 11:47:02
 ************************************************************************/

#include<iostream>
using namespace std;

//string store[1000000];
char buf[1000000];
class Solution {
	public:
		string countAndSay(int n) {
			string res;
			int tmp,bits = 0, lastlength = 1;
			res = "1";
			for (int cnt = 1;cnt < n ;cnt++) {
				tmp = 0;
				bits = 0;
				lastlength -= 1;
				for (int i = 0; i <= lastlength; i++) {
				//for (int i = lastlength -1; i >= 0; i--) {
					bits++;
					if ((i < lastlength && res[i + 1] != res[i]) || (i == lastlength)) {
						buf[tmp++] = bits+'0';
						buf[tmp++] = res[i];
						//tmp += 2;
						bits = 0;		
					}
				}
				buf[tmp] = '\0';
				//printf("%s\n", buf);
				res = string(buf);
				lastlength = tmp;
			}
			return res;
		}
};

int main(int argc, const char *argv[])
{
	Solution s1;
	cout << s1.countAndSay(1) << endl;
	cout << s1.countAndSay(2) << endl;
	cout << s1.countAndSay(3) << endl;
	cout << s1.countAndSay(4) << endl;
	return 0;
}
