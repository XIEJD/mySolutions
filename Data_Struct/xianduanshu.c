/**
	线段树
	以及由线段树衍生的应用
*/

#include<stdio.h>

#define MAX_SIZE 100000

/*节点结构体*/
typedef struct LBTNode{
	int fv,count;
	struct LBTNode *lchild,*rchild;
}LBTNode;

/*函数原型*/
LBTNode* createNode();
LBTNode* init(int *);			/*在数组上生成二叉树节点（平衡树）*/
LBTNode* mergeNode(int *, int, int);	/*合并二个子节点，即生成父节点*/
int find_fv(LBTNode *);			/*在树中找到出现最多的数*/
int countMid(int *,int, int);

/*函数定义*/
LBTNode *createNode(){
	return malloc(sizeof(LBTNode));
}

LBTNode* init(int *a){
	LBTNode *root;
	
}

int countMid(int *a, int l, int r){
	int mid = (l+r)/2;
	int i = mid, j = mid+1;
	if(a[i] == a[j]){
			do{
				a[i] == a[mid] ? i-- : break;
			}while(i >= l);
			do{
				a[j] == a[mid] ? j++ : break;
			}while(j <= r);
		}
	}else{
		return 0;
	}
	return j-i-1;
}
