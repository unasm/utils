/*************************************************************************
  * File Name :  28.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-05-10 15:20:53
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100000
int next[MAX];
int sta[MAX],resIdx[MAX],been[MAX];
struct hash{
	//不记录word的值，而是记录位置，保证不重复
	char* str;
	//cnt 表示该字符串在words中的全部数量，nowCnt 表示在窗口中的数量
	int cnt,nowCnt,times;
	struct hash *next;
}hash[MAX];
void getNext(char *need ,int size) {
	int pointer = -1 , idx = 0;
	next[0] = -1;
	while (idx < size) {
		if (pointer == -1 || need[pointer] == need[idx]) {
			idx++;
			pointer++;
			next[idx] = pointer;
		} else {
			pointer = next[pointer];
		}
	}
}

int cmp ( const void *a , const void *b)
{
        return *(int *)a - *(int *)b;
}

int strStr(char* haystack, char* needle) {
	int size = strlen(needle);
	if(size == 0) {
		return 0;
	}
	getNext(needle, size) ;
	int pointer = 0;
	int cnt = 0;
	for (int i = 0; haystack[i] != '\0';) {
		if( pointer == -1 || haystack[i] == needle[pointer]) {
			pointer++;
			i++;
			if(pointer == size ) {
				sta[cnt++] = i - size ;
				pointer = 0;
			}
		} else {
			pointer = next[pointer];
		}
	}
	return cnt;
}
//查找对应的节点，返回第几个窗的时候遍历的
struct hash* checkInHash(int pos, char *s){
	struct hash *pointer, *tail;
	pointer = &hash[pos];
	while(pointer != NULL && pointer->next != NULL){
		if( strcmp(s,pointer->str) == 0) {
			return pointer;
		}
		pointer = pointer->next;
	}
	return pointer;
}
//更新hash里面的次数
void updateHashTimes(int pos, char *s, int cnt, int times){
	struct hash *pointer, *tail;
	pointer = &hash[pos];
	while(pointer != NULL && pointer->next != NULL){
		if( strcmp(s,pointer->str) == 0) {
			pointer->nowCnt = cnt;
			//pointer->nowCnt += flag;
			pointer->times = times;
			return;
			//return 1;
		}
		pointer = pointer->next;
	}
}
void insertInHash(int pos, char* s){
	struct hash *pointer, *tail;
	pointer = &hash[pos];
	while(pointer != NULL && pointer->next != NULL){
		//因为肯定不存在相同的字符串，所以插入时候，不再比较
		if( strcmp(s,pointer->str) == 0) {
			pointer->cnt++;
			return;
		}
		pointer = pointer->next;
	}
	tail = (struct hash *)malloc(sizeof(struct hash));
	tail->next = NULL;
	pointer->str = s;
	pointer->cnt = 1;
	pointer->nowCnt = 0;
	pointer->times = -1;
	pointer->next = tail;
}

int times33( char *s) {
	int res = 0;
	for(int j = 0; s[j] != '\0'; j++) {
		res += res * 33 + s[j];
		res  %= MAX;
	}
	return res;
}

void disSta(int size) {
	printf("%d\n",size);
	for(int i = 0; i < size;i++) {
		printf("%d\t",sta[i]);
	}
	printf("\n");
}

void copyBuf(char * buf,char *s, int start,int wlen ) {
	for(int i = start; i < start + wlen; i++) {
			buf[i - start] = s[i];
	}
	buf[wlen] = '\0';
}
int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
	if(wordsSize <= 0) {
		*returnSize = 0;
		return  resIdx;
	}
	for(int i = 0;i < MAX;i++) {
		hash[i].next = NULL;
		hash[i].str = NULL;
		hash[i].times = -1;
		hash[i].cnt = 0;
		hash[i].nowCnt = 0;
		been[i] = 0;
	}
	int wlen = strlen(words[0]),slen = strlen(s);
	struct hash *pointer;
	for(int j = 0;j < wordsSize ; j++) {
		//printf("%d\t", times33(words[j]));
		insertInHash(times33(words[j]) , words[j]);
	}
	int size = strStr(s, words[0]),cnt,times, start;
	*returnSize = 0;
	//disSta(size);
	char buf[1000];
	for(int j = 0;j < size;j++) {
		for(int i = 0;i < wordsSize; i++) {
			updateHashTimes(times33(words[i]), words[i],0,j - 1);
		}
		start = sta[j];
		copyBuf(buf,s,start, wlen);
		pointer = checkInHash( times33(buf), buf);
		cnt = 1;
		if(pointer != NULL && cnt >= wordsSize) {
			resIdx[(*returnSize)] = start;
			been[start] = 1;
			(*returnSize)++;
			continue;	
		}
		updateHashTimes(times33(buf), buf, 1, j);
		//如果单纯是左边就可以，那右边就是另外的了，或者是两个凑成一个
		while ((start -= wlen) >= 0 && cnt < wordsSize && been[start] == 0) {
			for(int i = start; i < start + wlen; i++) {
				buf[i - start] = s[i];
			}
			buf[wlen] = '\0';
			//不能和中心点重复
			//times = checkInHash( times33(buf), buf);
			pointer = checkInHash( times33(buf), buf);
			if((pointer->times == j && pointer->nowCnt < pointer->cnt) || (pointer->times != j && pointer->cnt > 0)) {
				//出现过，但是还不够，或者是没出现但是在words中存在
				if((cnt + 1) == wordsSize) {
					//如果最后一个是
					resIdx[(*returnSize)] = start;
					been[start] = 1;
					(*returnSize)++;
					break;
				} else {
					cnt++;
					updateHashTimes(times33(buf), buf,pointer->nowCnt + 1, j);
				}
			} else {
				break;
			}
		}
		start = sta[j];

		while ( (start += wlen) < slen  && (start - cnt * wlen) <= sta[j] && been[start] == 0){
			for(int i = start; i < start + wlen; i++) {
				buf[i - start] = s[i];
			}
			buf[wlen] = '\0';
			pointer = checkInHash( times33(buf), buf);
			if(cnt < wordsSize)	{

				if((pointer->times == j && pointer->nowCnt < pointer->cnt) || (pointer->times != j && pointer->cnt > 0)) {
					cnt++;
					updateHashTimes(times33(buf), buf, pointer->nowCnt + 1, j);
					if (cnt == wordsSize) {
						//上一个	,更新临界窗口@todo
						int tmp = start  - (cnt - 1) * wlen;
						if(tmp > sta[j]) {
							//起始点不能超过原点
							break;
						}
						resIdx[(*returnSize)] = tmp;
						been[tmp] = 1;
						(*returnSize)++;
						copyBuf(buf, s, start, wlen);
						pointer = checkInHash( times33(buf), buf);
						updateHashTimes(times33(buf), buf, pointer->nowCnt - 1, j);
						cnt --;
					}
				} else {
					break;
				}
			} else {
				//是word里面的，但是cnt满了？？不应该存在
				printf("error occur\n");
				break;
			}
		} 
		//滑窗,以pos 为中心，滑窗
	}

	qsort(resIdx,*returnSize, sizeof(int), cmp);
	int resCnt = 0;
	for(int i = 1;i < *returnSize;i++) {
		printf("%d\t", resIdx[resCnt]);
		if(resIdx[i] != resIdx[resCnt]) {
			resCnt++;
			resIdx[resCnt] = resIdx[i];
		}
	}
	printf("\n");
	*returnSize = resCnt + 1;
	return resIdx;
}
void test( char *s , char **words, int wsize) {
	int reSize;
	int *res = findSubstring(s, words, wsize,&reSize);
	for (int i = 0; i < reSize; i++) {
		printf("%d\t",res[i]);
	}
	printf("\n");
}
int main(int argc, const char *argv[])
{
	char *words[1000];
	words[0] = "a"; 
	words[1] = "a"; 
	words[2] = "a"; 
	test("aaaaaa", words, 3)	;
	words[0] = "ab";
	test("abab", words, 1)	;
	/*
	char s[] = "pjzkrkevzztxductzzxmxsvwjkxpvukmfjywwetvfnujhweiybwvvsrfequzkhossmootkmyxgjgfordrpapjuunmqnxxdrqrfgkrsjqbszgiqlcfnrpjlcwdrvbumtotzylshdvccdmsqoadfrpsvnwpizlwszrtyclhgilklydbmfhuywotjmktnwrfvizvnmfvvqfiokkdprznnnjycttprkxpuykhmpchiksyucbmtabiqkisgbhxngmhezrrqvayfsxauampdpxtafniiwfvdufhtwajrbkxtjzqjnfocdhekumttuqwovfjrgulhekcpjszyynadxhnttgmnxkduqmmyhzfnjhducesctufqbumxbamalqudeibljgbspeotkgvddcwgxidaiqcvgwykhbysjzlzfbupkqunuqtraxrlptivshhbihtsigtpipguhbhctcvubnhqipncyxfjebdnjyetnlnvmuxhzsdahkrscewabejifmxombiamxvauuitoltyymsarqcuuoezcbqpdaprxmsrickwpgwpsoplhugbikbkotzrtqkscekkgwjycfnvwfgdzogjzjvpcvixnsqsxacfwndzvrwrycwxrcismdhqapoojegggkocyrdtkzmiekhxoppctytvphjynrhtcvxcobxbcjjivtfjiwmduhzjokkbctweqtigwfhzorjlkpuuliaipbtfldinyetoybvugevwvhhhweejogrghllsouipabfafcxnhukcbtmxzshoyyufjhzadhrelweszbfgwpkzlwxkogyogutscvuhcllphshivnoteztpxsaoaacgxyaztuixhunrowzljqfqrahosheukhahhbiaxqzfmmwcjxountkevsvpbzjnilwpoermxrtlfroqoclexxisrdhvfsindffslyekrzwzqkpeocilatftymodgztjgybtyheqgcpwogdcjlnlesefgvimwbxcbzvaibspdjnrpqtyeilkcspknyylbwndvkffmzuriilxagyerjptbgeqgebiaqnvdubrtxibhvakcyotkfonmseszhczapxdlauexehhaireihxsplgdgmxfvaevrbadbwjbdrkfbbjjkgcztkcbwagtcnrtqryuqixtzhaakjlurnumzyovawrcjiwabuwretmdamfkxrgqgcdgbrdbnugzecbgyxxdqmisaqcyjkqrntxqmdrczxbebemcblftxplafnyoxqimkhcykwamvdsxjezkpgdpvopddptdfbprjustquhlazkjfluxrzopqdstulybnqvyknrchbphcarknnhhovweaqawdyxsqsqahkepluypwrzjegqtdoxfgzdkydeoxvrfhxusrujnmjzqrrlxglcmkiykldbiasnhrjbjekystzilrwkzhontwmehrfsrzfaqrbbxncphbzuuxeteshyrveamjsfiaharkcqxefghgceeixkdgkuboupxnwhnfigpkwnqdvzlydpidcljmflbccarbiegsmweklwngvygbqpescpeichmfidgsjmkvkofvkuehsmkkbocgejoiqcnafvuokelwuqsgkyoekaroptuvekfvmtxtqshcwsztkrzwrpabqrrhnlerxjojemcxel"
		,*words[18] = {"dhvf","sind","ffsl","yekr","zwzq","kpeo","cila","tfty","modg","ztjg","ybty","heqg","cpwo","gdcj","lnle","sefg","vimw","bxcb"};int wsize = 18;
		*/
	
	//char s[] = "lingmindraboofooowingdingbarrwingmonkeypoundcake",*words[] = {"fooo","barr","wing","ding","wing"}; int wsize = 5;
	//char s[] = "", *words[3] = {"ab", "cd", "ef"}; int wsize = 3;
	words[0]	 = "ab";
	words[1]	 = "cd";
	words[2]	 = "ef";
	test("abefcdabef", words, 3)	;
//char s[] = "hmtsvuabdjitpfehczyfliomwqkelhcstxmrsmuxxcrohxwjzuqkegwawigjskdliqeaeyzcasskqovpkmzosyqriwaaheoruutytscvlvhbldqyprojrfacdbekfsbbpwzkpefazpdmsvkjmzsgevkhwoudjxeyufijjplkeoxwlhhzgafmvpwtgqyppcpljxwvohftxcrimzisbphyhdtnvremvtyequzeefzdjtmvuwqvlxvucohzfnlagleyggfmnepwxbsrzionhjhjzrkeevelhljptobgvscuuwovgcinoqynjiungaapnkggajmxbrsxpitwmblatkqcumqcmsraczifixemowjfecbrgptbzlevxwykormttuadrephdznhdqalfwnghtefperfvdaqzaurhjykkntoeuzlsoszhwgyazgxegqejkvsvvcglvuprvclmwlvutuutcuzkkdtwalrypxjntaercqfzdatywqtymtjyweuxsnvhnguggbzitejyfdwdvqchjlfhrbgjodrbjnkpqlyjqhjxmgahyeqjpvqhyxspclqmzcbrobdgjmdxufhskxdbvukttdivobhpflhtmmzxyevtkenwbrxynksincfdfntlacemogkokhjwlxumqsldefltjqwrfrefvkulqeadljzwiukyoxbseonqhjhoblwyvqkoukrhvsfempccpgwtujjbtsswdowbegpasghoymsndupsaomxxxasqsqvgpwkvnkovtcufwjlqadtorqorqihlberqdclqobmifipbrasrenixfyovgxgjcazhenxsolcuvsvmupgaeqyjoohwopgspfztuyojksffmcuhuchyuhiiypgmgmewudrobfznygvklrtfvbfpkpzigfwnuajqdaehigwiotuzkogfrmwbdvmkdixxjinoktxsbwcqpxralyhcmefpbrbecydnisdtmbnpxqfopxoaxycjehafbcmdarqlkvgywtnvltmasacpaeaeoamrcawfrosdjybgtpdfkpheskvuqvbgxpxcrvjijbotzpbsggzswjwqttmlqnsqcrstnbeyeurflszszzmxilpdebqxrinvcfrrixpmrjtcbswcrjbbuqgauxxlhmijrzcbwupndiqebmjsxkwtdcuxztkjgsuzuxbqrsgubwacklwkwudbxzayvkjdeecybfruyxqbvqfhebrawxdvydvtnfwtjbumingikwjhooousiuqfzndcizrpxlayhohuupgsbnjrddjlazszmyexxvmuipvpdclatruwedoijxvlzomnmqklmzfuoamrextapowvrkfckbplrcydsjqgivbyynrcmlcbzbzsnexzhmkyojdjutpcrscpfttugyxfbwaodxokjalajqjfmyhfrlwyfpunpstqovhtsvgdxrdhjmmxn", 
char s[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 

		 *wordsLong[28] = {"xbqrsgubwacklwkwudbxzayvkjde","ltjqwrfrefvkulqeadljzwiukyox","ccpgwtujjbtsswdowbegpasghoym","tywqtymtjyweuxsnvhnguggbzite","vmkdixxjinoktxsbwcqpxralyhcm","gzswjwqttmlqnsqcrstnbeyeurfl","ycjehafbcmdarqlkvgywtnvltmas","fztuyojksffmcuhuchyuhiiypgmg","acpaeaeoamrcawfrosdjybgtpdfk","fdfntlacemogkokhjwlxumqsldef","mewudrobfznygvklrtfvbfpkpzig","fwtjbumingikwjhooousiuqfzndc","upndiqebmjsxkwtdcuxztkjgsuzu","pheskvuqvbgxpxcrvjijbotzpbsg","bmifipbrasrenixfyovgxgjcazhe","cufwjlqadtorqorqihlberqdclqo","bseonqhjhoblwyvqkoukrhvsfemp","sndupsaomxxxasqsqvgpwkvnkovt","yjqhjxmgahyeqjpvqhyxspclqmzc","fwnuajqdaehigwiotuzkogfrmwbd","nxsolcuvsvmupgaeqyjoohwopgsp","brobdgjmdxufhskxdbvukttdivob","szszzmxilpdebqxrinvcfrrixpmr","ecybfruyxqbvqfhebrawxdvydvtn","jyfdwdvqchjlfhrbgjodrbjnkpql","jtcbswcrjbbuqgauxxlhmijrzcbw","hpflhtmmzxyevtkenwbrxynksinc", "efpbrbecydnisdtmbnpxqfopxoax" };
	test(s, wordsLong, 28);
	return 0;
}
// ab cd ab
