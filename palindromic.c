/*************************************************************************
  * File Name :  palindromic.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-04-28 16:43:31
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#define LEN 10000
int hash[30000],pos[30000];
char res[10000];
void init(){
	for (int i = 0;i < 2 * LEN;i++) {
		hash[i]	 = -1;
	}
}
char* longestPalindrome(char* s) {
	int len = 0;
	init();
	//让每个字符，指向前一个字符的存在未知
	for (len = 0; s[len] != '\0'; len++) {
		/*
		if(len && s[len] == s[len - 1]) {
			pos[len] = hash[s[len - 1]];
			hash[s[len]] = hash[s[len - 1]];
		} else {
		*/
			pos[len] = hash[s[len]];
			hash[s[len]]  = len;
		//}
		//printf("%c last is %d\n",s[len] , pos[len]);
	}
	init();
	int last;
	int cnt = 0;

	printf("len is : %d\n",len);
	int same = 0;
	for (int i = 0; s[i] != '\0' ; i++) {
		last = i;
		while(1) {
			cnt++;
			if (last == -1) {
				break;
			}
			int sum = last + i;
			if (hash[sum] == -1){
				if(i - last <= 2){
					hash[sum] = i;
				} 
				/* else if (pos[last + 1] == pos[i]) {
					printf("strage\n");
					hash[sum] = i;	
				}
				*/
			} else if ( i - hash[sum] == 1 ) {
				hash[sum] = i;
			} 
			last = pos[last];
		}
	}
	int length = 0,focus;
	printf("cnt num is : %d\n",cnt);
	for(int i = 0;i < 2 * len; i++) {
		if(hash[i] != -1 ) {

			int tmp =  2 * hash[i] - i + 1;
			//int tmp = 2 * ( hash[i] - (i / 2 + i % 2) );
			if( length < tmp) {
				length  = tmp;
				focus = i;
			}
		}
	}
	 cnt = 0;
	 printf("length is : %d\n" , length);
	for(int i = focus - hash[focus]; i <= hash[focus];i++) {
		res[cnt++] = s[i];
	}
	res[cnt] = '\0';
	return res;
}
int main(int argc, const char *argv[])
{
	
	//char str[] = "abcbcba" ,expect[] = "abcbcba";
	//char str[] = "abcbcbcbd" ,expect[] = "bcbcbcb";
	//char str[] = "aabaaa" ,expect[] = "aabaa";
	//char str[] = "aaabaaaa" ,expect[] = "aaabaaa";
	//char str[] = "abaa" ,expect[] = "aba";
	//char str[] = "a" ,expect[] = "a";
	/*
	char str[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabcaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" ,
		 expect[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabcaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
		 */
	char str[] = "baaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab" ,expect[] = "baaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
	//char str[] = "lphbehiapswjudnbcossedgioawodnwdruaaxhbkwrxyzaxygmnjgwysafuqbmtzwdkihbwkrjefrsgjbrycembzzlwhxneiijgzidhngbmxwkhphoctpilgooitqbpjxhwrekiqupmlcvawaiposqttsdgzcsjqrmlgyvkkipfigttahljdhtksrozehkzgshekeaxezrswvtinyouomqybqsrtegwwqhqivgnyehpzrhgzckpnnpvajqevbzeksvbezoqygjtdouecnhpjibmsgmcqcgxwzlzztdneahixxhwwuehfsiqghgeunpxgvavqbqrelnvhnnyqnjqfysfltclzeoaletjfzskzvcdwhlbmwbdkxnyqappjzwlowslwcbbmcxoiqkjaqqwvkybimebapkorhfdzntodhpbhgmsspgkbetmgkqlolsltpulgsmyapgjeswazvhxedqsypejwuzlvegtusjcsoenrcmypexkjxyduohlvkhwbrtzjnarusbouwamazzejhnetfqbidalfomecehfmzqkhndpkxinzkpxvhwargbwvaeqbzdhxzmmeeozxxtzpylohvdwoqocvutcelgdsnmubyeeeufdaoznxpvdiwnkjliqtgcmvhilndcdelpnilszzerdcuokyhcxjuedjielvngarsgxkemvhlzuprywlypxeezaxoqfges" ,expect[] = "a";
	//char str[] = "abc" ,expect[] = "a";
	char *p;
	p = longestPalindrome(str);
	if(strcmp(p, expect) == 0) {
		printf("yes\n");
	} else {
		printf("ans is  %s\n", p);
	}
	return 0;
}
