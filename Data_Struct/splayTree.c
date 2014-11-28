/**
	伸展树
*/

#include<stdio.h>
#include<stdlib.h>

/*数据结构*/
typedef struct SPTNode{
	int value;
	int nc;	//为题目而加4.c,子孙节点数
	struct SPTNode *lchild,*rchild,*father;
}SPTNode;

/*函数原型*/
SPTNode* createNode();
void zig(SPTNode *);					//右旋
void zag(SPTNode *);					//左旋
void splay(SPTNode *);
void insert(SPTNode *, int);
SPTNode* delete(SPTNode *, int);			//返回删除节点后，合并的根节点
SPTNode* find(SPTNode *, int);				//将匹配到的元素旋转到根
SPTNode* join(SPTNode *, SPTNode *);			//将两个子伸展树合并成一颗伸展树
void split(SPTNode *, int, SPTNode **, SPTNode **);	//以匹配到的元素为界，将其分为二颗子伸展树
SPTNode* SPTInit(int *);				//以二叉查找树的方法初始化
void scan(SPTNode *);					//先序遍历

/*函数定义*/
SPTNode* createNode(){
	return malloc(sizeof(SPTNode));
}

void zig(SPTNode *T){
	int fc,mc;
	if(T){
		if(T->rchild){
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
		}else{
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

void insert(SPTNode *T, int n){
	SPTNode *p = T,*tmp;
	while(p){
		if(p->value == n){
			while(p->father){
				p->father->nc--;
				p = p->father;
			}
			break;
		}else{
			tmp = p->value > n ? p->lchild : p->rchild;
			p->nc++;
			if(!tmp){
				tmp = createNode();
				tmp->value = n;
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

void scan(SPTNode *T){
	if(T){
		scan(T->lchild);
		printf("%d\n",T->value);
		scan(T->rchild);
	}
}

int main(){
	int a[] = {20,6,2,4,5,3,8,3,5,9,7,10,19,11,18,12,17,13,16,14,15};
	SPTNode *root;
	root = SPTInit(a);
	scan(root);
	printf("-----%d-------\n",root->nc);
	root = delete(root,4);
	root = delete(root,14);
	scan(root);
	printf("-----%d-----\n",root->nc);
	return 0;
}
