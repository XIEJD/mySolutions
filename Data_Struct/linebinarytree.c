/**
	线段树
	lazy-tag和课堂上老师讲的不同
*/

#include<stdio.h>
#include<stdlib.h>

/*数据结构*/
typedef struct LBTNode{
	int left,mid,right;
	int cover;//记录区间是否覆盖
	int fv,count;//为了frequent value问题特别添加
	struct LBTNode *lchild,*rchild;
}LBTNode;

/*函数原型*/
LBTNode* createNode();				//创建节点
int insert_b(LBTNode *, int, int);		//插入区间
int delete_b(LBTNode *, int, int);		//删除区间
void insert_a(LBTNode *, int, int);
void delete_a(LBTNode *, int, int);		//a方法，正宗lazy-tag思想
int calLenght(LBTNode *);			//统计区间总有效长度
void serialize(int *, int *);			//前一个参数是原始数组，后一个为传出的连续化的数组
LBTNode* init(int, int);			//为了方便递归，单独出这个初始化函数
LBTNode* LBTInit(int *, int *);			//将数组初始化成线段树,后一个数组为连续化后数组，下标对应区间，值对应原值

/*函数定义*/
LBTNode* createNode(){
	return malloc(sizeof(LBTNode));
}

int insert_b(LBTNode *T, int l, int r){
	if(T){
		if(T->left == T->right){
			T->cover = 1;
			return 1;
		}else if(r <= T->mid){
			return insert_b(T->lchild,l,r);
		}else if(l > T->mid){
			return insert_b(T->rchild,l,r);
		}else if(l >= T->left && r <= T->right){
			if(insert_b(T->lchild,l,T->mid) + insert_b(T->rchild,T->mid+1,r) > 1){
				T->cover = 1;
				//T->lchild->cover = T->rchild->cover = 0; 想想还是不lazy-tag了，感觉对delete操作也没好多少
				return 1;
			}
		}
	}
	return 0;
}

void insert_a(LBTNode *T, int l, int r){
	if(T){
		if(l == T->left && r == T->right){
			T->cover = 1;
		}else if(l > T->mid){
			insert_a(T->rchild,l,r);
		}else if(r <= T->mid){
			insert_a(T->lchild,l,r);
		}else{
			insert_a(T->rchild,T->mid+1,r);
			insert_a(T->lchild,l,T->mid);
		}
	}
}

void delete_a(LBTNode *T, int l, int r){
	if(T){
		T->cover = 0;
		if(l > T->mid){
			delete_a(T->rchild,l,r);
			insert_a(T,T->left,l-1);
		}else if(r <= T->mid){
			delete_a(T->lchild,l,r);
			insert_a(T,r+1,T->right);
		}else if(l > T->left && r < T->right){
			delete_a(T->rchild,T->mid+1,r);
			delete_a(T->lchild,l,T->mid);
			insert_a(T,T->left,l-1);
			insert_a(T,r+1,T->right);
		}
	}
}

int delete_b(LBTNode *T, int l, int r){
	if(T){
		if(T->left == T->right){
			T->cover = 0;
			return 1;
		}else if(r <= T->mid){
			if(delete_b(T->lchild,l,r)){
				T->cover = 0;
				return 1;
			}
		}else if(l > T->mid){
			if(delete_b(T->rchild,l,r)){
				T->cover = 0;
				return 1;
			}
		}else if(l >= T->left && r <= T->right){
			if(delete_b(T->lchild,l,T->mid) + delete_b(T->rchild,T->mid+1,r) > 0){
				T->cover = 0;//此处只要字节点有被删除操作，父节点必须cover清零
				return 1;
			}
		}
	}
	return 0;
}

int calLength(LBTNode *T){
	if(T->cover > 0){
		return T->right - T->left + 1;
	}else if(T->lchild || T->rchild){
		return calLength(T->lchild) + calLength(T->rchild);
	}else{
		return 0;
	}
}

void serialize(int *a, int *s){
	int width = 0;
	for(int i = 2, tmp = a[1], j = 2; i <= a[0]; i++){
		if(tmp < a[i]){
			s[j++] = tmp = a[i];
			width++;
		}
	}
	s[0] = width + 1;
	s[1] = a[1];
}

LBTNode* init(int l, int r){
	LBTNode *T;
	if(T = createNode()){
		T->left = l;
		T->mid = (l+r)/2;
		T->right = r;
		if(l != r){
			T->lchild = init(l,(l+r)/2);
			T->rchild = init((r+l)/2+1,r);
		}
	}
	return T;
}

LBTNode* LBTInit(int *a, int *s){
	LBTNode *root;
	serialize(a,s);
	root = init(1,s[0]);
	return root;
}

int main(){
	int a[] = {20,1,1,1,2,2,2,2,4,5,6,7,7,7,8,9,10,10,11,20,21};
	int s[a[0]];
	LBTNode *root = LBTInit(a,s);
	insert_a(root,1,s[0]);
	printf("%d\n",calLength(root));
	delete_a(root,1,4);
	printf("%d\n",calLength(root));
	return 0;
}
