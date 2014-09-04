#include<string.h>
#include<stdio.h>
#define LENGTH 20000
//这里定义的红黑树是左边小，右边大
struct treeNode{
	unsigned int hashValue;
	//@todo 这里暂时使用数组代替，将来根据具体的数据，考虑使用链表优化
	//保存http连接的最后十个字符，作为判重的标准
	char httpBack[3][10];
	char color;// -1表示nil，0表示红，1表示黑
}list[LENGTH];
//@todo 以后再考虑追加数组
/**
 * time33算法，将字符串转化成为对应的int
 * @param	char *hash 需要转化的字符串
 */
unsigned int time33(char *hash){
	unsigned int ret = 0;
	while(*hash !='\0'){
		ret =( ret << 5) + ret + (*hash++);
	}
	return ret;
}
/**
 * 左旋
 * @param	int		pos		关节节点
 */
void rotateLeft(int pos){
	list[pos*2] = list[pos];
	list[pos] = list[pos*2+1] ;
	list[pos*2+1].color = -1;
}
/**
 * 右旋
 */
void rotateRight(int pos){
	list[pos*2+1] = list[pos];
	list[pos] = list[pos*2];
	list[pos*2].color = -1;
}
/**
 *@param int  节点在树中的位置
 */
void fixColor(int pos){
	//第一种情况，父亲节点是黑色的，不用调整
	int fa = pos/2;
	if(pos == 1){
		return;
	}
	//如果父节点为根节点的情况
	if(pos%2){
		int uncle = pos + 1;
	}else{
		int uncle = pos - 1;
	}
	printf("%d\n" , uncle);
	//叔叔节点的颜色为红
	if(list[uncle].color == 0){
		list[uncle].color = 1;
		list[fa].color = 1;	
		list[fa/2].color = 0;
		fixColor(fa/2);
	}else if((fa%2) && !(pos%2)){
		//叔叔节点的颜色为黑,父亲为右节点，自己为左节点
		rotateRight(fa);
		fixColor(pos+1);
	}else if(!(fa%2) && (pos%2)){
		rotateLeft(fa);
		fixColor(pos - 1);
	}
}
void roate5(int pos){
	int fa = pos/2;
	list[fa].color = 1;
	list[fa/2].color = 0;	
	if((fa%2) && (pos%2)){
		rotateRight(fa/2)	;
	}else{
		rotateLeft(fa/2);
	}
}
/**
 * @param	int		hashValue	hash出来的数值
 * @param	char *	url			后10为字符
 * @param	int		pos			节点的位置
 */
int rbtree(int hashValue , char *url, int pos){
	//处理根目录和相同的情况
	if(list[pos].color = -1 || hashValue == list[pos].hashValue){
		list[pos].hashValue = hashValue;		
		if(pos == 1){
			list[pos].color = 1;
			return;
		}
		list[pos].color = 0;
		int cnt = 0;
		//查一下如何将字符串赋值给字符
		while(*url !='\0'){
			list[pos].httpBack[0][cnt++] = *url++;
		}
		//如果父节点也为红色，则矛盾发生
		if(list[pos/2].color == 0){
			fixColor(pos);
		}
	}else if(hashValue > list[pos].hashValue){
		//大数字在右边
		rbtree(hashValue,url,pos * 2+1);
	}else{
		//小数字在左边
		rbtree(hashValue,url,pos * 2);
	}
}
int  main(){
	char urls[10][100] = {
		"hello,world!" , "testing" ,"sdf"
	};
	for(int i = 0;i < LENGTH;i++){
		list[i].color =  -1;
	}
	for(int i = 0;i < 3;i++){
		unsigned int tmp = time33(urls[i]);
		/*
		if(tmp < 0){
			printf("wired!\n");
		}else{
			printf("no\n");
		}
		*/
		printf("%d\n" , tmp);
		//rbtree(tmp,str,position);
	}
	//cout << time33(hash)<< endl;
	return 0;
}
