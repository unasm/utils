/*************************************************************************
  * File Name :  30.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-13 23:48:01
 ************************************************************************/

#include<iostream>
#include<vector>
#include<climits>
using namespace std;
#define MAX 100000

struct rehash {
	int cnt,all,idx;
	//char *str;
	struct rehash *next;
}rehash[MAX];
//int resIdx[MAX];
void insertrehash(int pos, char *str, vector<string> words) {
	struct rehash *p, *tail;
	p = &rehash[pos];
	while (p != NULL && p->next != NULL) {
		if (strcmp(p->str , str) == 0) {
			p->all++;
		}
		p = p->next;
	}
	tail = (struct rehash *)malloc( sizeof (struct rehash));
	tail->next = NULL;
	tail->cnt = 0;
	tail->all = 0;
	tail->str = NULL;
	p->next = tail;
	p->cnt = 0;
	p->all = 1;
	p->str = str;
}


void setrehash(int pos, char *str, int flag) {
	struct rehash *p;
	p = &rehash[pos];
	while (p != NULL && p->next != NULL) {
		if (strcmp(p->str , str) == 0) {
			p->cnt += flag;
			return;
		}
		p = p->next;
	}
}

struct rehash * getrehash(int pos, char *str) {
	struct rehash *p;
	p = &rehash[pos];
	while (p != NULL && p->next != NULL ) {
		if (strcmp(p->str , str) == 0) {
			break;
		}
		p = p->next;
	}
	return p;
}
int times33( char *s) {
	int res = 0;
	for(int j = 0; s[j] != '\0'; j++) {
		res += res * 33 + s[j];
		res  %= MAX;
	}
	return res;
}
int times33( string &s) {
	int res = 0;
	for(int j = 0,size = s.size(); j < size; j++) {
		res += res * 33 + s[j];
		res  %= MAX;
	}
	return res;
}

/*
int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {

}
*/
class Solution {
	public:
    vector<int> findSubstring(string s, vector<string>& words) {
	    vector<int>resIdx; 
		int wordsSize = words.size();
		if(wordsSize <= 0)	{
			return resIdx;
		}
		for (int i = 0;i < wordsSize;i++) {
			insertrehash(times33(words[i]), i)	;
		}
		int wlen = words[0].size(), pos, cnt;
		char buf[1000];
		struct rehash *p;
		for (int i = 0, end = s.size() - wlen * wordsSize;i <= end ;i++) {
			for (cnt = 0; cnt < wordsSize;cnt++) {
				for (int ksta = i + cnt * wlen,k = ksta; k < ksta + wlen; k++ ) {
					buf[k - ksta] = s[k];
				}
				buf[wlen] = '\0';
				pos = times33(buf);
				p = getrehash(pos, buf);
				if(p != NULL && p->cnt < p->all) {
					setrehash(pos, buf, 1)	;
				} else {
					break;
				}
			}
			if (cnt == wordsSize) {
				resIdx.push_back(i);
			}
			for (int j = 0; j < cnt; j++) {
				for (int ksta = i + j * wlen,k = ksta; k < ksta + wlen; k++ ) {
					buf[k - ksta] = s[k];
				}
				buf[wlen] = '\0';
				pos = times33(buf);
				//p = getrehash(pos, buf);
				setrehash(pos, buf, - 1)	;
			}
			
		}
		return resIdx;
	}
};
void test(  string s , vector<string>words) {
	struct Solution s1;
	vector<int> res = s1.findSubstring(s, words);
	for (int i = 0,reSize = res.size(); i < reSize; i++) {
		printf("%d\t",res[i]);
	}
	printf("\n");
}
int main(int argc, const char *argv[])
{
	//char *words[1000];
	vector<string> words;	
	words.push_back("a");
	words.push_back("b");
	/*
	words[0] = "a"; 
	words[1] = "b"; 
	*/
	test(string("aaa"), words)	;
/*
	words[0] = "a"; 
	words[1] = "a"; 
	words[2] = "a"; 
	test("aaaaaa", words, 3)	;
	*/
	words.clear();
	words.push_back("ab");
	//words[0] = "ab";
	test("abab", words)	;
	/*
	char s[] = "pjzkrkevzztxductzzxmxsvwjkxpvukmfjywwetvfnujhweiybwvvsrfequzkhossmootkmyxgjgfordrpapjuunmqnxxdrqrfgkrsjqbszgiqlcfnrpjlcwdrvbumtotzylshdvccdmsqoadfrpsvnwpizlwszrtyclhgilklydbmfhuywotjmktnwrfvizvnmfvvqfiokkdprznnnjycttprkxpuykhmpchiksyucbmtabiqkisgbhxngmhezrrqvayfsxauampdpxtafniiwfvdufhtwajrbkxtjzqjnfocdhekumttuqwovfjrgulhekcpjszyynadxhnttgmnxkduqmmyhzfnjhducesctufqbumxbamalqudeibljgbspeotkgvddcwgxidaiqcvgwykhbysjzlzfbupkqunuqtraxrlptivshhbihtsigtpipguhbhctcvubnhqipncyxfjebdnjyetnlnvmuxhzsdahkrscewabejifmxombiamxvauuitoltyymsarqcuuoezcbqpdaprxmsrickwpgwpsoplhugbikbkotzrtqkscekkgwjycfnvwfgdzogjzjvpcvixnsqsxacfwndzvrwrycwxrcismdhqapoojegggkocyrdtkzmiekhxoppctytvphjynrhtcvxcobxbcjjivtfjiwmduhzjokkbctweqtigwfhzorjlkpuuliaipbtfldinyetoybvugevwvhhhweejogrghllsouipabfafcxnhukcbtmxzshoyyufjhzadhrelweszbfgwpkzlwxkogyogutscvuhcllphshivnoteztpxsaoaacgxyaztuixhunrowzljqfqrahosheukhahhbiaxqzfmmwcjxountkevsvpbzjnilwpoermxrtlfroqoclexxisrdhvfsindffslyekrzwzqkpeocilatftymodgztjgybtyheqgcpwogdcjlnlesefgvimwbxcbzvaibspdjnrpqtyeilkcspknyylbwndvkffmzuriilxagyerjptbgeqgebiaqnvdubrtxibhvakcyotkfonmseszhczapxdlauexehhaireihxsplgdgmxfvaevrbadbwjbdrkfbbjjkgcztkcbwagtcnrtqryuqixtzhaakjlurnumzyovawrcjiwabuwretmdamfkxrgqgcdgbrdbnugzecbgyxxdqmisaqcyjkqrntxqmdrczxbebemcblftxplafnyoxqimkhcykwamvdsxjezkpgdpvopddptdfbprjustquhlazkjfluxrzopqdstulybnqvyknrchbphcarknnhhovweaqawdyxsqsqahkepluypwrzjegqtdoxfgzdkydeoxvrfhxusrujnmjzqrrlxglcmkiykldbiasnhrjbjekystzilrwkzhontwmehrfsrzfaqrbbxncphbzuuxeteshyrveamjsfiaharkcqxefghgceeixkdgkuboupxnwhnfigpkwnqdvzlydpidcljmflbccarbiegsmweklwngvygbqpescpeichmfidgsjmkvkofvkuehsmkkbocgejoiqcnafvuokelwuqsgkyoekaroptuvekfvmtxtqshcwsztkrzwrpabqrrhnlerxjojemcxel"
		,*words[18] = {"dhvf","sind","ffsl","yekr","zwzq","kpeo","cila","tfty","modg","ztjg","ybty","heqg","cpwo","gdcj","lnle","sefg","vimw","bxcb"};int wsize = 18;
		*/
	
	//char s[] = "lingmindraboofooowingdingbarrwingmonkeypoundcake",*words[] = {"fooo","barr","wing","ding","wing"}; int wsize = 5;
	//char s[] = "", *words[3] = {"ab", "cd", "ef"}; int wsize = 3;
	/*
	words[0]	 = "ab";
	words[1]	 = "cd";
	words[2]	 = "ef";
	test("abefcdabef", words, 3)	;
	*/
	/*
//char s[] = "hmtsvuabdjitpfehczyfliomwqkelhcstxmrsmuxxcrohxwjzuqkegwawigjskdliqeaeyzcasskqovpkmzosyqriwaaheoruutytscvlvhbldqyprojrfacdbekfsbbpwzkpefazpdmsvkjmzsgevkhwoudjxeyufijjplkeoxwlhhzgafmvpwtgqyppcpljxwvohftxcrimzisbphyhdtnvremvtyequzeefzdjtmvuwqvlxvucohzfnlagleyggfmnepwxbsrzionhjhjzrkeevelhljptobgvscuuwovgcinoqynjiungaapnkggajmxbrsxpitwmblatkqcumqcmsraczifixemowjfecbrgptbzlevxwykormttuadrephdznhdqalfwnghtefperfvdaqzaurhjykkntoeuzlsoszhwgyazgxegqejkvsvvcglvuprvclmwlvutuutcuzkkdtwalrypxjntaercqfzdatywqtymtjyweuxsnvhnguggbzitejyfdwdvqchjlfhrbgjodrbjnkpqlyjqhjxmgahyeqjpvqhyxspclqmzcbrobdgjmdxufhskxdbvukttdivobhpflhtmmzxyevtkenwbrxynksincfdfntlacemogkokhjwlxumqsldefltjqwrfrefvkulqeadljzwiukyoxbseonqhjhoblwyvqkoukrhvsfempccpgwtujjbtsswdowbegpasghoymsndupsaomxxxasqsqvgpwkvnkovtcufwjlqadtorqorqihlberqdclqobmifipbrasrenixfyovgxgjcazhenxsolcuvsvmupgaeqyjoohwopgspfztuyojksffmcuhuchyuhiiypgmgmewudrobfznygvklrtfvbfpkpzigfwnuajqdaehigwiotuzkogfrmwbdvmkdixxjinoktxsbwcqpxralyhcmefpbrbecydnisdtmbnpxqfopxoaxycjehafbcmdarqlkvgywtnvltmasacpaeaeoamrcawfrosdjybgtpdfkpheskvuqvbgxpxcrvjijbotzpbsggzswjwqttmlqnsqcrstnbeyeurflszszzmxilpdebqxrinvcfrrixpmrjtcbswcrjbbuqgauxxlhmijrzcbwupndiqebmjsxkwtdcuxztkjgsuzuxbqrsgubwacklwkwudbxzayvkjdeecybfruyxqbvqfhebrawxdvydvtnfwtjbumingikwjhooousiuqfzndcizrpxlayhohuupgsbnjrddjlazszmyexxvmuipvpdclatruwedoijxvlzomnmqklmzfuoamrextapowvrkfckbplrcydsjqgivbyynrcmlcbzbzsnexzhmkyojdjutpcrscpfttugyxfbwaodxokjalajqjfmyhfrlwyfpunpstqovhtsvgdxrdhjmmxn", 
	char s[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 
		 *wordsLong[28] = {"xbqrsgubwacklwkwudbxzayvkjde","ltjqwrfrefvkulqeadljzwiukyox","ccpgwtujjbtsswdowbegpasghoym","tywqtymtjyweuxsnvhnguggbzite","vmkdixxjinoktxsbwcqpxralyhcm","gzswjwqttmlqnsqcrstnbeyeurfl","ycjehafbcmdarqlkvgywtnvltmas","fztuyojksffmcuhuchyuhiiypgmg","acpaeaeoamrcawfrosdjybgtpdfk","fdfntlacemogkokhjwlxumqsldef","mewudrobfznygvklrtfvbfpkpzig","fwtjbumingikwjhooousiuqfzndc","upndiqebmjsxkwtdcuxztkjgsuzu","pheskvuqvbgxpxcrvjijbotzpbsg","bmifipbrasrenixfyovgxgjcazhe","cufwjlqadtorqorqihlberqdclqo","bseonqhjhoblwyvqkoukrhvsfemp","sndupsaomxxxasqsqvgpwkvnkovt","yjqhjxmgahyeqjpvqhyxspclqmzc","fwnuajqdaehigwiotuzkogfrmwbd","nxsolcuvsvmupgaeqyjoohwopgsp","brobdgjmdxufhskxdbvukttdivob","szszzmxilpdebqxrinvcfrrixpmr","ecybfruyxqbvqfhebrawxdvydvtn","jyfdwdvqchjlfhrbgjodrbjnkpql","jtcbswcrjbbuqgauxxlhmijrzcbw","hpflhtmmzxyevtkenwbrxynksinc", "efpbrbecydnisdtmbnpxqfopxoax" };
	test(s, wordsLong, 28);
	*/
	return 0;
}

