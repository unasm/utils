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
    int right,left, parent;
}list[LENGTH];
//表示list将要使用的下表
int listPos = 0,ROOT;
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
    int tmp= (1 << 31) -1 ;
    ret &=(1 << 31) -1;
    return ret;
}
/**
 * 左旋
 * @param	int		pos		关节节点
 */
void rotateLeft(int parent){
	int grandpa = list[parent].parent;
	int n = list[parent].right;
	//n和g 相互连接
	if(grandpa != -1){
		list[grandpa].left = n;
	}
	list[n].parent = grandpa;
	//p和n的左节点互相交换
	if(list[n].left!= -1){
		list[list[n].left].parent = parent;
	}
	list[parent].right = list[n].left;
	//n和p互相交换
	list[parent].parent = n;
	list[n].left = parent;

}
/**
 * 右旋
 *@param int parent
 */
void rotateRight(int parent){
	int grandpa = list[parent].parent;
	int n = list[parent].left;
	//n节点和祖父节点互相交换
	if(grandpa != -1){
		list[grandpa].right = n;
	}
	list[n].parent= grandpa;
	//n右节点和p节点的互相交换
	list[parent].left = list[n].right ;
	if(list[n].right != -1){
		list[list[n].right].parent = parent;	
	}
	//n和p互相交换 
	list[n].right = parent;
	list[parent].parent = n;
}
void rotate5(int pos){
	int parent = list[pos].parent;
	int grandpa = list[parent].parent;
	//父节点变成黑色，祖父节点编程红色
    list[parent].color = 1;
    list[grandpa].color = 0;
	//都是左节点的情况，右旋转
    if(list[parent].left == pos && list[grandpa].left == parent){
        rotateRight(grandpa);
    }else{
        rotateLeft(grandpa);
    }
}
/**
 *@param int  节点在树中的位置
 */
void fixColor(int pos){
    //第一种情况，父亲节点是黑色的，不用调整
    //如果当前节点为根节点的情况,当祖父节点为-1，则父节点为跟节点，直接更改根节点为黑色，冲突解决
    int parent = list[pos].parent,grandpa = list[parent].parent;
    if(pos == 0 ){
		printf("这里不应该有什么进\n");
		list[pos].color = 1;
    }
	if(parent == 0){
		list[parent].color = -1;
        return;
	}
	//第二情况，父节点为黑色，不冲突
	if(list[parent].color == 1)return;

	int uncle ;
	//查找叔叔节点
    if(list[grandpa].right == parent){
         uncle = list[grandpa].left;
    }else{
        uncle = list[grandpa].right;
    }
    printf("%d\n" , uncle);
    //叔叔不为空，节点的颜色为红
    if(uncle != -1 && list[uncle].color == 0){
        list[uncle].color = 1;
        list[parent].color = 1;
        list[grandpa].color = 0;
        fixColor(grandpa);
    }else if(parent == list[grandpa].right && pos == list[parent].left){
        //叔叔节点的颜色为黑或者是叶子节点,父亲为右节点，自己为左节点
        rotateRight(parent);
		pos = list[pos].left;
        //fixColor(parent);
    }else if(parent == list[grandpa].left && pos == list[parent].right){
        rotateLeft(parent);
		pos = list[pos].right;
    }
	rotate5(pos);
}

/**
 * @param	int		hashValue	hash出来的数值
 * @param	char *	url			后10为字符
 * @param	int		pos			节点的位置
 */
int rbtree(int hashValue , char *url, int pos){
    //处理根目录和相同的情况
	//进入叶子节点
    if(list[pos].color == -1){
        list[pos].hashValue = hashValue;
        list[pos].color = 0;
        int cnt = 0;
        //查一下如何将字符串赋值给字符
        while(*url !='\0'){
            list[pos].httpBack[0][cnt++] = *url++;
			printf("%s\n" , list[pos].httpBack[0]);
        }
        //如果父节点也为红色，则矛盾发生
        if(list[list[pos].parent].color == 0){
            fixColor(pos);
        }
		return;
    }
	//如果不是叶子节点，但是数值相同，处理冲突
	if(list[pos].hashValue == hashValue){
		printf("发生了冲突\n");
		return;	
	}
	if(hashValue > list[pos].hashValue){
        //大数字在右边
		if(list[pos].right == -1){
			//如果左节点或者是右节点属于尚未分配的节点，将其与父关系声明
			list[listPos].parent = pos;
			list[pos].right = listPos++;
		}
        rbtree(hashValue,url,list[pos].right);
    }else{
        //小数字在左边
		if(list[pos].left == -1){
			list[listPos].parent = pos;
			list[pos].left = listPos++;	
		}
        rbtree(hashValue,url,list[pos].left);
    }
}
int  main(){
	int i;
    char urls[10][100] = {
        "a" , "aa" ,"aaa"
    };
    for(i = 0;i < LENGTH;i++){
        list[i].color =  -1;
        list[i].right =  -1;
        list[i].left =  -1;
    }
	//预处理根节点为空的情况
	listPos = 0;	
	list[listPos].color = 1;
	list[listPos].hashValue = time33(urls[0]);
	list[listPos].parent = -1;
	listPos ++;
    for(i = 1;i < 3;i++){
        unsigned int tmp = time33(urls[i]);
        printf("%d\n" , tmp);
        rbtree(tmp,urls[i],0);
    }
    //cout << time33(hash)<< endl;
    return 0;
}
