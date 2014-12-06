/**
	伸展树
*/

#include<stdio.h>
#include<stdlib.h>

/*数据结构*/
typedef struct ZJZ{
	int add,turn,max;				//为5.c而加，子孙的整体加减数，是否翻转，最大值 
}ZJZ;							//此域内值在计算时包括本身节点

typedef struct SPTNode{
	int value;
	int nc;						//为题目而加4.c,子孙节点数,此值不包括本身节点
	ZJZ *info;					//为5.c而加
	struct SPTNode *lchild,*rchild,*father;
}SPTNode;

/*函数原型*/
SPTNode* createNode();
ZJZ* createZJZNode();
void zig(SPTNode *);					//右旋
void zag(SPTNode *);					//左旋
void splay(SPTNode *);
void insert(SPTNode *, int);
SPTNode* delete(SPTNode *, int);			//返回删除节点后，合并的根节点
SPTNode* find(SPTNode *, int);				//将匹配到的元素旋转到根
SPTNode* findk(SPTNode *,int);				//找到第K大的节点
SPTNode* join(SPTNode *, SPTNode *);			//将两个子伸展树合并成一颗伸展树
void split(SPTNode *, int, SPTNode **, SPTNode **);	//以匹配到的元素为界，将其分为二颗子伸展树
SPTNode* SPTInit(int *);				//以二叉查找树的方法初始化
void scanPre(SPTNode *);				//遍历

/*函数定义*/
SPTNode* createNode(){
	return malloc(sizeof(SPTNode));
}

ZJZ* createZJZNode(){
	return malloc(sizeof(ZJZ));
}

void zig(SPTNode *T){
	int fc,mc,;
	if(T){
		if(T->rchild){		//当右子树存在的情况下
			if(T->father->value > T->rchild->value){
				mc = T->father->nc;
				fc = T->father->nc - T->nc - 1 + T->rchild->nc + 1;
				T->father->lchild = T->rchild;
				T->rchild->father = T->father;
				T->rchild = T->father;
				T->father = T->father->father;
				if(T->father){
					T->rchild->value < T->father->value ? (T->father->lchild = T) : (T->father->rchild = T);
				}
				T->rchild->father = T;
			}else{
				printf("这不是一颗查找树！");
			}
		}else{			//当右子树不存在的情况下
			mc = T->father->nc;
			fc = T->father->nc - T->nc - 1;
			T->father->nc = T->father->nc - T->nc - 1;
			T->father->lchild = NULL;
			T->rchild = T->father;
			T->father = T->father->father;
			if(T->father){
				T->rchild->value < T->father->value ? (T->father->lchild = T) : (T->father->rchild = T);
			}
			T->rchild->father = T;	
		}
		T->nc = mc;//变换节点后
		T->rchild->nc = fc;
	}
}

void zag(SPTNode *T){
	int fc,mc;
	if(T){
		if(T->lchild){
			if(T->father->value < T->lchild->value){
				mc = T->father->nc;
				fc = T->father->nc - T->nc - 1 + T->lchild->nc + 1;
				T->father->rchild = T->lchild;
				T->lchild->father = T->father;
				T->lchild = T->father;
				T->father = T->father->father;
				if(T->father){
					T->lchild->value > T->father->value ? (T->father->rchild = T) : (T->father->lchild = T);
				}
				T->lchild->father = T;
			}else{
				printf("这不是一颗查找树！");
			}
		}else{
			mc = T->father->nc;
			fc = T->father->nc - T->nc - 1;
			T->father->rchild = NULL;
			T->lchild = T->father;
			T->father = T->father->father;
			if(T->father){
				T->lchild->value > T->father->value ? (T->father->rchild = T) : (T->father->lchild = T);
			}
			T->lchild->father = T;
		}
		T->nc = mc;
		T->lchild->nc = fc;
	}
}

void splay(SPTNode *T){
	SPTNode *p = T;
	while(p&&p->father){
		p->value < p->father->value ? zig(p) : zag(p);
	}
}

SPTNode* find(SPTNode *T, int n){
	SPTNode *p = T;
	while(p){
		if(p->value == n){
			return p;
		}else{
			p = p->value > n ? p->lchild : p->rchild;
		}
	}
	return p;
}

SPTNode *findk(SPTNode *T,int k){
	if(T){
		int n;			//N为当前节点为第几大
		if(T->lchild){
			n = T->nc - T->lchild->nc;
		}else if(T->rchild){
			n = T->rchild->nc + 2;
		}else{
			n = 1;
		}

		if(n == k){
			return T;
		}else if(n > k){
			return findk(T->rchild,k);
		}else{
			return findk(T->lchild,k-n);
		}
	}
}

void insert(SPTNode *T, int n){
	SPTNode *p = T,*tmp;
	ZJZ *zjz;
	while(p){
		if(p->value == n){		//插入值重复，将其父节点多加的NC值减掉
			while(p->father){
				p->father->nc--;
				p = p->father;
			}
			break;
		}else{
			tmp = p->value > n ? p->lchild : p->rchild;
			p->nc++;		//在它插入的父路径上，nc值都要加1
			if(!tmp){
				tmp = createNode();
				zjz = createZJZNode();		//##
				tmp->info = zjz;		//##
				tmp->value = n;
				tmp->info->max = n;		//##初始化info域，以value为关键值生成伸展树
				p->value > n ? (p->lchild = tmp) : (p->rchild = tmp);
				tmp->father = p;
				break;
			}
			p = tmp;
		}
	}
}

SPTNode* delete(SPTNode *T, int n){
	SPTNode *p,*tmp;
	tmp = p = find(T,n);
	if(!tmp){
		printf("请选择存在的点");
		return T;
	}
	splay(p);
	p->lchild->father = p->rchild->father = NULL;
	p = join(p->lchild,p->rchild);	
	free(tmp);
	return p;
}

SPTNode* join(SPTNode *a, SPTNode *b){
	SPTNode *s = a;
	while(s->rchild){
		s = s->rchild;
	}
	splay(s);
	s->rchild = b;
	b->father = s;
	s->nc += b->nc + 1;
	return s;
}

void split(SPTNode *T, int n, SPTNode **s1, SPTNode **s2){
	*s1 = find(T,n);
	splay(*s1);
	*s2 = (*s1)->rchild;
	*s1 = (*s1)->lchild;
}

SPTNode* SPTInit(int *a){
	SPTNode *root;
	root = createNode();
	if(a[0]) root->value = a[1];
	for(int i = 2; i <= a[0]; i++){
		insert(root,a[i]);
	}
	return root;	
}

void scanPre(SPTNode *T){
	if(T){
		scanPre(T->lchild);
		printf("%d,%d\n",T->value,T->nc);
		scanPre(T->rchild);
	}
}
/*
int main(){
	int a[] = {20,6,2,4,5,3,8,3,5,9,7,10,19,11,18,12,17,13,16,14,15};
	SPTNode *root;
	root = SPTInit(a);
	scanPre(root);
	printf("-----%d-------\n",root->nc);
	root = delete(root,4);
	root = delete(root,14);
	scanPre(root);
	printf("-----%d-----\n",root->nc);
	return 0;
}
*/
