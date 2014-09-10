#include<string.h>
#include<string>
#include<stdio.h>
#include <iostream>
using namespace   std;
int deep(int pos ,int blackDeepth);
#define LENGTH 20000
//ÕâÀï¶¨ÒåµÄºìºÚÊ÷ÊÇ×ó±ßÐ¡£¬ÓÒ±ß´ó
struct treeNode{
    unsigned int hashValue;
    //@todo ÕâÀïÔÝÊ±Ê¹ÓÃÊý×é´úÌæ£¬½«À´¸ù¾Ý¾ßÌåµÄÊý¾Ý£¬¿¼ÂÇÊ¹ÓÃÁ´±íÓÅ»¯
    //±£´æhttpÁ¬½ÓµÄ×îºóÊ®¸ö×Ö·û£¬×÷ÎªÅÐÖØµÄ±ê×¼
    char httpBack[3][10];
    char color;// -1±íÊ¾nil£¬0±íÊ¾ºì£¬1±íÊ¾ºÚ
    int right,left, parent;
}list[LENGTH];
int queue[LENGTH][2];
//±íÊ¾list½«ÒªÊ¹ÓÃµÄÏÂ±í
int listPos = 0,ROOT;
//@todo ÒÔºóÔÙ¿¼ÂÇ×·¼ÓÊý×é
/**
 * time33Ëã·¨£¬½«×Ö·û´®×ª»¯³ÉÎª¶ÔÓ¦µÄint
 * @param	char *hash ÐèÒª×ª»¯µÄ×Ö·û´®
 */
unsigned int time33(char *hash){
    unsigned int ret = 0;
    while(*hash !='\0'){
        ret =( ret << 5) + ret + (*hash++);
    }
    ret &=(1 << 31) - 1;
    return ret;
}
/**
 * ×óÐý
 * @param	int		pos		¹Ø½Ú½Úµã
 */
void rotateLeft(int parent){
	int grandpa = list[parent].parent;
	int n = list[parent].right;
	//nºÍg Ïà»¥Á¬½Ó
	if(grandpa != -1){
		list[grandpa].left = n;
	}
	list[n].parent = grandpa;
	//pºÍnµÄ×ó½Úµã»¥Ïà½»»»
	if(list[n].left!= -1){
		list[list[n].left].parent = parent;
	}
	list[parent].right = list[n].left;
	//nºÍp»¥Ïà½»»»
	list[parent].parent = n;
	list[n].left = parent;
}
/**
 * ÓÒÐý
 *@param int parent
 */
void rotateRight(int parent){
	int grandpa = list[parent].parent;
	int n = list[parent].left;
	//n½ÚµãºÍ×æ¸¸½Úµã»¥Ïà½»»»
	if(grandpa != -1){
		list[grandpa].right = n;
	}
	list[n].parent= grandpa;
	//nÓÒ½ÚµãºÍp½ÚµãµÄ»¥Ïà½»»»
	list[parent].left = list[n].right ;
	if(list[n].right != -1){
		list[list[n].right].parent = parent;
	}
	//nºÍp»¥Ïà½»»»
	list[n].right = parent;
	list[parent].parent = n;
}
void rotate5(int pos){
	int parent = list[pos].parent;
	int grandpa = list[parent].parent;
	//¸¸½Úµã±ä³ÉºÚÉ«£¬×æ¸¸½Úµã±à³ÌºìÉ«
    list[parent].color = 1;
    list[grandpa].color = 0;
	//¶¼ÊÇ×ó½ÚµãµÄÇé¿ö£¬ÓÒÐý×ª
    if(list[parent].left == pos && list[grandpa].left == parent){
        rotateRight(grandpa);
    }else{
        rotateLeft(grandpa);
    }
}
/**
 *@param int  ½ÚµãÔÚÊ÷ÖÐµÄÎ»ÖÃ
 */
void fixColor(int pos){
    //µÚÒ»ÖÖÇé¿ö£¬¸¸Ç×½ÚµãÊÇºÚÉ«µÄ£¬²»ÓÃµ÷Õû
    //Èç¹ûµ±Ç°½ÚµãÎª¸ù½ÚµãµÄÇé¿ö,µ±×æ¸¸½ÚµãÎª-1£¬Ôò¸¸½ÚµãÎª¸ú½Úµã£¬Ö±½Ó¸ü¸Ä¸ù½ÚµãÎªºÚÉ«£¬³åÍ»½â¾ö
    int parent = list[pos].parent,grandpa = list[parent].parent;
    if(pos == 0 ){
		printf("ÕâÀï²»Ó¦¸ÃÓÐÊ²Ã´½ø\n");
		list[pos].color = 1;
    }
	if(parent == 0){
		list[parent].color = -1;
        return;
	}
	//µÚ¶þÇé¿ö£¬¸¸½ÚµãÎªºÚÉ«£¬²»³åÍ»
	if(list[parent].color == 1)return;

	int uncle ;
	//²éÕÒÊåÊå½Úµã
    if(list[grandpa].right == parent){
         uncle = list[grandpa].left;
    }else{
        uncle = list[grandpa].right;
    }
    //ÊåÊå²»Îª¿Õ£¬½ÚµãµÄÑÕÉ«Îªºì
    if(uncle != -1 && list[uncle].color == 0){
        list[uncle].color = 1;
        list[parent].color = 1;
        list[grandpa].color = 0;
        fixColor(grandpa);
    }else if(parent == list[grandpa].right && pos == list[parent].left){
        //ÊåÊå½ÚµãµÄÑÕÉ«ÎªºÚ»òÕßÊÇÒ¶×Ó½Úµã,¸¸Ç×ÎªÓÒ½Úµã£¬×Ô¼ºÎª×ó½Úµã
        rotateRight(parent);
		pos = list[pos].right;
        //fixColor(parent);
    }else if(parent == list[grandpa].left && pos == list[parent].right){
        rotateLeft(parent);
		pos = list[pos].left;
    }
	rotate5(pos);
}

/**
 * @param	int		hashValue	hash³öÀ´µÄÊýÖµ
 * @param	char *	url			ºó10Îª×Ö·û
 * @param	int		pos			½ÚµãµÄÎ»ÖÃ
 */
int rbtree(int hashValue , char *url, int pos){
    //´¦Àí¸ùÄ¿Â¼ºÍÏàÍ¬µÄÇé¿ö
	//½øÈëÒ¶×Ó½Úµã
    if(list[pos].color == -1){
        list[pos].hashValue = hashValue;
        list[pos].color = 0;
        int cnt = 0;
        //²éÒ»ÏÂÈçºÎ½«×Ö·û´®¸³Öµ¸ø×Ö·û
        while(*url !='\0'){
            list[pos].httpBack[0][cnt++] = *url++;
		//	printf("%s\n" , list[pos].httpBack[0]);
        }
        //Èç¹û¸¸½ÚµãÒ²ÎªºìÉ«£¬ÔòÃ¬¶Ü·¢Éú
        if(list[list[pos].parent].color == 0){
            fixColor(pos);
        }
		return -1;
    }
	//Èç¹û²»ÊÇÒ¶×Ó½Úµã£¬µ«ÊÇÊýÖµÏàÍ¬£¬´¦Àí³åÍ»
	if(list[pos].hashValue == hashValue){
		printf("·¢ÉúÁË³åÍ»\n");
		return -1;
	}
	if(hashValue > list[pos].hashValue){
        //´óÊý×ÖÔÚÓÒ±ß
		if(list[pos].right == -1){
			//Èç¹û×ó½Úµã»òÕßÊÇÓÒ½ÚµãÊôÓÚÉÐÎ´·ÖÅäµÄ½Úµã£¬½«ÆäÓë¸¸¹ØÏµÉùÃ÷
			list[listPos].parent = pos;
			list[pos].right = listPos++;
		}
        rbtree(hashValue,url,list[pos].right);
    }else{
        //Ð¡Êý×ÖÔÚ×ó±ß
		if(list[pos].left == -1){
			list[listPos].parent = pos;
			list[pos].left = listPos++;
		}
        rbtree(hashValue,url,list[pos].left);
    }
}
int findRoot(int node){
	while(list[node].parent != -1){
		node = list[node].parent;
	}
	return node;
}
/**
 * µ±µ±Ç°½ÚµãÎªºìÉ«µÄÊ±ºò£¬¶Ô×Ó½Úµã½øÐÐµÄ¼ìÑé
 */
int redCheck(int pos ,int blackDeepth){
	if(pos != -1 && list[pos].color != -1){
		if(list[pos].color == 0)	{
			printf("ÑÕÉ«²»¶Ô,¸¸½ÚµãºÍ×Ó½Úµã¶¼ÎªºìÉ«ÁË");
			return -2;
		}
		//×Ó½ÚµãÎªÒ¶×Ó½Úµã£¬²»ÔÙ¼ÓÉî
		if(list[pos].color == 1){
			return deep(pos,blackDeepth);
		}
	}
	return blackDeepth;
}
/**
 * µÝ¹é¼ìÑéÊÇ²»ÊÇºìºÚÊ÷
 * @param int pos			µ±Ç°½ÚµãµÄÎ»ÖÃ
 * @param int blackDeepth	¾­ÀúµÄºÚ½ÚµãµÄÊýÄ¿
 */
int deep(int pos ,int blackDeepth){
	int rightValue = 0,leftValue = 0;
	//ºÚÉ«µÄ£¬²»ÓÃ¼Æ½Ï£¬Ö±½Ó+1
	if(list[pos].color == 1){
		if(list[pos].right != -1){
			rightValue = deep(list[pos].right , blackDeepth + 1);
		}
		if(list[pos].left != -1){
			leftValue = deep(list[pos].left , blackDeepth + 1);
		}
	}
	if(list[pos].color == 0){
		rightValue = redCheck(list[pos].left , blackDeepth);
		leftValue = redCheck(list[pos].right , blackDeepth);
	}
	if(list[pos].color == -1){
		printf("³öÏÖÁË²»Ó¦¸Ã³öÏÖµÄÇé¿ö£¬-1²»Ó¦¸Ã³öÏÖÔÚÕâÀï");
		return -2;
	}
	if(rightValue && leftValue ){
		return rightValue == leftValue ? leftValue : -2;
	}
	return rightValue | leftValue;
}
/**
 * ¼ìÑéÊ÷ÊÇ²»ÊÇºìºÚÊ÷
 */
int checkIsRBtree(int root ){
	int in = 0,out = 0;
	if(list[root].color != 1){
		printf("¸ù½ÚµãÃ»ÓÐÎªºÚÉ«");
		return -2;
	}
	int value = deep(root ,1 );
	if(value > 0){
		;
		//printf("ÊÇºìºÚÊ÷");
	}else{
		printf("error : %d\n", value);
	}
	return value;
}
int  main(){
	int i ,j;
    string urls[2][10] = {
        {"sdf" , "sdfsadf" , "sd"},    {"sdf" , "sdfsadf" , "sd"}
    };
    for(i = 0;i < LENGTH;i++){
        list[i].color =  -1;
        list[i].right =  -1;
        list[i].left =  -1;
    }
	//Ô¤´¦Àí¸ù½ÚµãÎª¿ÕµÄÇé¿ö
	listPos = 0;
	list[listPos].color = 1;
	//list[listPos].hashValue = time33(urls[0]);
	list[listPos].parent = -1;
	listPos++;
    /*
	for(j=0;j < 1;j++){
	    for(i = 1;i < 3;i++){
    	    unsigned int tmp = time33(urls[j][i].c_str());
	       // printf("%d\n" , tmp);
        	rbtree(tmp,urls[j][i].c_str(),findRoot(0));
    	}
   	}
    */
	printf("root : %d\n" , findRoot(0));
	if(checkIsRBtree(findRoot(0)) == -2){
		printf("²»ÊÇºìºÚÊ÷");
	}
    //cout << time33(hash)<< endl;
    return 0;
}
