/**
	线段树
	以及由线段树衍生的应用
*/

#include<stdio.h>
#include<stdlib.h>

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
int find_count(LBTNode *);		/*最多出现的次数*/
int countMid(int *,int, int);

/*函数定义*/
LBTNode *createNode(){
	return malloc(sizeof(LBTNode));
}

LBTNode* init(int *a){
	LBTNode *root;
	root = mergeNode(a,1,a[0]);
	return root;	
}

int countMid(int *a, int l, int r){
	int mid = (l+r)/2;
	int i = mid, j = mid+1;
	if(a[i] == a[j]){
			do{
				i--;
			}while(a[i] == a[mid] && i >= l);
			do{
				j++;
			}while(a[j] == a[mid] && j <= r);
	}else{
		return 0;
	}
	return j-i-1;
}

LBTNode* mergeNode(int *a, int l, int r){
	LBTNode *node;
	int midc,max,fv;
	if(!(node = createNode())){
		printf("无法创建节点!\n");
	}
	if(l == r){
		node->fv = a[l];
		node->count = 1;
	}else{
		node->lchild = mergeNode(a,l,(l+r)/2);
		node->rchild = mergeNode(a,(l+r)/2+1,r);
		max = midc = countMid(a,l,r);
		max = max > node->lchild->count ? (fv = a[(l+r)/2], max) : (fv = node->lchild->fv, node->lchild->count);
		max = max > node->rchild->count ? (fv = a[(l+r)/2], max) : (fv = node->rchild->fv, node->rchild->count);
		node->fv = fv;
		node->count = max;
	}
	return node;
}

int find_fv(LBTNode *root){
	return root->fv;
}	

int find_count(LBTNode *root){
	return root->count;
}

int main(){
	int a[] = {20,1,1,1,2,2,2,2,3,3,3,4,4,5,5,5,5,5,5,7,8};
	LBTNode *root;
	root = init(a);
	printf("fv = %d\ncount = %d\n",find_fv(root),find_count(root));
	return 0;
}
