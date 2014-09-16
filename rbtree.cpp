#include<string.h>
#include<string>
#include<stdio.h>
#include <iostream>
using namespace   std;
int deep(int pos ,int blackDeepth);
#define LENGTH 20000
#define TEST 10
//?a¨¤??¡§¨°?¦Ì?o¨¬o¨²¨º¡Â¨º?¡Á¨®¡À?D?¡ê?¨®¨°¡À?¡ä¨®
struct treeNode{
    unsigned int hashValue;
    //@todo ?a¨¤??Y¨º¡À¨º1¨®?¨ºy¡Á¨¦¡ä¨²¨¬?¡ê???¨¤¡ä?¨´?Y??¨¬?¦Ì?¨ºy?Y¡ê?????¨º1¨®?¨¢¡ä¡À¨ª¨®??¡¥
    //¡À¡ê¡ä?http¨¢??¨®¦Ì?¡Á?o¨®¨º???¡Á?¡¤?¡ê?¡Á¡Â?a?D??¦Ì?¡À¨º¡Á?
    char httpBack[3][10];
    char color;// -1¡À¨ª¨º?nil¡ê?0¡À¨ª¨º?o¨¬¡ê?1¡À¨ª¨º?o¨²
    int right,left, parent;
}list[LENGTH];
int queue[LENGTH][2];
//¡À¨ª¨º?list??¨°a¨º1¨®?¦Ì???¡À¨ª
int listPos = 0,ROOT;
//@todo ¨°?o¨®?¨´????¡Á¡¤?¨®¨ºy¡Á¨¦
/**
 * time33??¡¤¡§¡ê???¡Á?¡¤?¡ä?¡Áa?¡¥3¨¦?a??¨®|¦Ì?int
 * @param	char *hash D¨¨¨°a¡Áa?¡¥¦Ì?¡Á?¡¤?¡ä?
 */
unsigned int time33(string url){
    unsigned int ret = 0;
    for(std::string::iterator it = url.begin();it != url.end();it++){
		ret +=( ret << 5) + (*it);
	}
	ret &=(1<<31) - 1;
    return ret;
}
/**
 * ¡Á¨®Dy
 * @param	int		pos		1??¨²?¨²¦Ì?
 */
void rotateLeft(int parent){
	int grandpa = list[parent].parent;
	int n = list[parent].right;
	//no¨ªg ?¨¤?£¤¨¢??¨®
	if(grandpa != -1){
		list[grandpa].left = n;
	}
	list[n].parent = grandpa;
	//po¨ªn¦Ì?¡Á¨®?¨²¦Ì??£¤?¨¤????
	if(list[n].left!= -1){
		list[list[n].left].parent = parent;
	}
	list[parent].right = list[n].left;
	//no¨ªp?£¤?¨¤????
	list[parent].parent = n;
	list[n].left = parent;
}
/**
 * ¨®¨°Dy
 *@param int parent
 */
void rotateRight(int parent){
	int grandpa = list[parent].parent;
	int n = list[parent].left;
	//n?¨²¦Ì?o¨ª¡Á????¨²¦Ì??£¤?¨¤????
	if(grandpa != -1){
		list[grandpa].right = n;
	}
	list[n].parent= grandpa;
	//n¨®¨°?¨²¦Ì?o¨ªp?¨²¦Ì?¦Ì??£¤?¨¤????
	list[parent].left = list[n].right ;
	if(list[n].right != -1){
		list[list[n].right].parent = parent;
	}
	//no¨ªp?£¤?¨¤????
	list[n].right = parent;
	list[parent].parent = n;
}
void rotate5(int pos){
	int parent = list[pos].parent;
	int grandpa = list[parent].parent;
	//???¨²¦Ì?¡À?3¨¦o¨²¨¦?¡ê?¡Á????¨²¦Ì?¡À¨¤3¨¬o¨¬¨¦?
    list[parent].color = 1;
    list[grandpa].color = 0;
	//??¨º?¡Á¨®?¨²¦Ì?¦Ì??¨¦??¡ê?¨®¨°Dy¡Áa
    if(list[parent].left == pos && list[grandpa].left == parent){
        rotateRight(grandpa);
    }else{
        rotateLeft(grandpa);
    }
}
/**
 *@param int  ?¨²¦Ì??¨²¨º¡Â?D¦Ì?????
 */
void fixColor(int pos){
    //¦Ì¨²¨°????¨¦??¡ê????¡Á?¨²¦Ì?¨º?o¨²¨¦?¦Ì?¡ê?2?¨®?¦Ì¡Â??
    //¨¨?1?¦Ì¡À?¡ã?¨²¦Ì??a?¨´?¨²¦Ì?¦Ì??¨¦??,¦Ì¡À¡Á????¨²¦Ì??a-1¡ê??¨°???¨²¦Ì??a?¨²?¨²¦Ì?¡ê??¡À?¨®?¨¹???¨´?¨²¦Ì??ao¨²¨¦?¡ê?3?¨ª??a??
    int parent = list[pos].parent;
    //the first situation
    if(list[pos].parent == -1){
		list[pos].color = 1;
		return;
    }
    // only when pos and parent is the red ,we fix;
    if(list[pos].color != 0 || list[parent].color != 0){
    	return ;
    }
   	int grandpa = list[parent].parent,uncle;
   	//the second situation the grandpa is the root 
	//¦Ì¨²?t?¨¦??¡ê????¨²¦Ì??ao¨²¨¦?¡ê?2?3?¨ª?
	//get uncle
    if(list[grandpa].right == parent){
         uncle = list[grandpa].left;
    }else{
        uncle = list[grandpa].right;
    }
    //¨º?¨º?2??a??¡ê??¨²¦Ì?¦Ì???¨¦??ao¨¬
    if(uncle != -1 && list[uncle].color == 0){
        list[uncle].color = 1;
        list[parent].color = 1;
        list[grandpa].color = 0;
        fixColor(grandpa);
        return;
    }else if(parent == list[grandpa].right && pos == list[parent].left){
        //¨º?¨º??¨²¦Ì?¦Ì???¨¦??ao¨²?¨°??¨º?¨°?¡Á¨®?¨²¦Ì?,???¡Á?a¨®¨°?¨²¦Ì?¡ê?¡Á??o?a¡Á¨®?¨²¦Ì?
        rotateRight(parent);
		pos = list[pos].right;
       
    }else if(parent == list[grandpa].left && pos == list[parent].right){
        rotateLeft(parent);
		pos = list[pos].left;
    }
	rotate5(pos);
	fixColor(list[pos].parent);
}

/**
 * @param	int		hashValue	hash3?¨¤¡ä¦Ì?¨ºy?¦Ì
 * @param	char *	url			o¨®10?a¡Á?¡¤?
 * @param	int		pos			?¨²¦Ì?¦Ì?????
 */
void rbtree(int hashValue , string url, int pos){
    //¡ä|¨¤¨ª?¨´????o¨ª?¨¤¨ª?¦Ì??¨¦??
	//??¨¨?¨°?¡Á¨®?¨²¦Ì?
    if(list[pos].color == -1){
        list[pos].hashValue = hashValue;
        list[pos].color = 0;
        int cnt = 0;
        //2¨¦¨°???¨¨?o???¡Á?¡¤?¡ä??3?¦Ì??¡Á?¡¤?
        for(string::iterator it = url.begin();it != url.end();it++){
        	list[pos].httpBack[0][cnt++]= *it;
        }
        //¨¨?1????¨²¦Ì?¨°2?ao¨¬¨¦?¡ê??¨°???¨¹¡¤¡é¨¦¨²
     fixColor(pos);
		return ;
    }
	//¨¨?1?2?¨º?¨°?¡Á¨®?¨²¦Ì?¡ê?¦Ì?¨º?¨ºy?¦Ì?¨¤¨ª?¡ê?¡ä|¨¤¨ª3?¨ª?
	if(list[pos].hashValue == hashValue){
		printf("-1 the sameing is coming\n");
		return;
	}
	if(hashValue > list[pos].hashValue){
        //¡ä¨®¨ºy¡Á??¨²¨®¨°¡À?
		if(list[pos].right == -1){
			//¨¨?1?¡Á¨®?¨²¦Ì??¨°??¨º?¨®¨°?¨²¦Ì?¨º?¨®¨²¨¦D?¡ä¡¤???¦Ì??¨²¦Ì?¡ê?????¨®???1??¦Ì¨¦¨´?¡Â
			list[listPos].parent = pos;
			list[pos].right = listPos++;
		}
        rbtree(hashValue,url,list[pos].right);
    }else{
        //D?¨ºy¡Á??¨²¡Á¨®¡À?
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
 * ¦Ì¡À¦Ì¡À?¡ã?¨²¦Ì??ao¨¬¨¦?¦Ì?¨º¡Ào¨°¡ê???¡Á¨®?¨²¦Ì???DD¦Ì??¨¬?¨¦
 */
int redCheck(int pos ,int blackDeepth){
	if(pos != -1 && list[pos].color != -1){
		if(list[pos].color == 0)	{
			printf("??¨¦?2???,???¨²¦Ì?o¨ª¡Á¨®?¨²¦Ì????ao¨¬¨¦?¨¢?");
			return -2;
		}
		//¡Á¨®?¨²¦Ì??a¨°?¡Á¨®?¨²¦Ì?¡ê?2??¨´?¨®¨¦?
		if(list[pos].color == 1){
			return deep(pos,blackDeepth);
		}
	}
	return blackDeepth;
}
/**
 * ¦ÌY1¨¦?¨¬?¨¦¨º?2?¨º?o¨¬o¨²¨º¡Â
 * @param int pos			¦Ì¡À?¡ã?¨²¦Ì?¦Ì?????
 * @param int blackDeepth	?-¨¤¨²¦Ì?o¨²?¨²¦Ì?¦Ì?¨ºy??
 */
int deep(int pos ,int blackDeepth){
	int rightValue = 0,leftValue = 0;
	//o¨²¨¦?¦Ì?¡ê?2?¨®?????¡ê??¡À?¨®+1
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
		printf("-1 is coming back");
		return -2;
	}
	if(rightValue && leftValue ){
		return rightValue == leftValue ? leftValue : -2;
	}
	return rightValue | leftValue;
}
/**
 * ?¨¬?¨¦¨º¡Â¨º?2?¨º?o¨¬o¨²¨º¡Â
 */
int checkIsRBtree(int root ){
	int in = 0,out = 0;
	if(list[root].color != 1){
		printf("");
		return -2;
	}
	int value = deep(root ,1 );
	if(value > 0){
		;
	}else{
		printf("error : %d\n", value);
	}
	return value;
}
int  main(){
	int i ,j;
    string urls[TEST][20] = {
		{"sbbf" , "bbb" , "sbb","s" , "sdf" , "dsfa" , "sdfad"},
		{"sbbsf" , "bbb" , "sbb","s" , "sdf" , "dsfa" , "sdfad"},
		{"sbbsf" ,"sbb","s" , "sdf" , "sdfad"},
		{"sbbsf" , "bbb" , "sbb","s" , "sdf" , "dsfa" , "sdfad","sbbsf" , "bbb" , "sbb","s" , "sdf" , "dsfa" , "sdfad"}
    };
	for(j=0;j < TEST && urls[j][0] != "";j++){
 		for(i = 0;i < LENGTH;i++){
        	list[i].color =  -1;
	        list[i].right =  -1;
    	    list[i].left =  -1;
	    }
		listPos = 0;
		list[listPos].color = 1;
  		cout << time33(urls[j][0]) << endl;
		list[listPos].hashValue = time33(urls[j][0]);
		list[listPos].parent = -1;
		listPos++;
	    for(i = 1;urls[j][i] != "";i++){ 
		    ROOT = findRoot(0);
		    cout << time33(urls[j][i]) << endl;
        	rbtree(time33(urls[j][i]),urls[j][i],ROOT);
   			if(checkIsRBtree(findRoot(0)) == -2){
				printf("return value is -2\n");
				if(getchar() == '\n'){
					;
				}
   			}
 		}
    	for(i=0;i < listPos;i ++){
	    	printf("%d \thashValue = %d , left is %d , right is %d  , parent is %d ",i,list[i].hashValue,list[i].left , list[i].right ,list[i].parent);
	    	if(list[i].color == 0){
				printf("red");
			} else if(list[i].color == 1){
				printf("black");
			} else{
				printf("sec:%d" , list[i].color);
			}
			printf("\n");
	    }
   		printf("root : %d\n" , findRoot(0));
		if(checkIsRBtree(findRoot(0)) == -2){
			printf("return value is -2\n");
		}
		if(getchar()== '\n'){
			;
		}
   	}

    return 0;
}
