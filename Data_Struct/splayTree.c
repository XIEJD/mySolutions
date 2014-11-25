/**
	伸展树
*/

#include<stdio.h>
#include<stdlib.h>

/*数据结构*/
typedef struct SPTNode{
	int value;
	struct SPTNode *lchild,*rchild,*father;
}SPTNode;

/*函数原型*/
SPTNode* createNode();
void zig(SPTNode *);					//右旋
void zag(SPTNode *);					//左旋
void splay(SPTNode *);
void insert(SPTNode *, int);
void delete(SPTNode *, int);
SPTNode* find(SPTNode *, int);				//将匹配到的元素旋转到根
SPTNode* join(SPTNode *, SPTNode *);			//将两个子伸展树合并成一颗伸展树
void split(SPTNode *, int, SPTNode *, SPTNode *);	//以匹配到的元素为界，将其分为二颗子伸展树
SPTNode* SPTInit(int *);				//以二叉查找树的方法初始化
void scan(SPTNode *);					//先序遍历

/*函数定义*/
SPTNode* createNode(){
	return malloc(sizeof(SPTNode));
}

void zig(SPTNode *T){
	if(T){
		if(T->father->value > T->rchild->value){
			T->father->lchild = T->rchild;
			if(T->rchild) T->rchild->father = T->father;
			T->rchild = T->father;
			T->father = T->father->father;
			if(T->father) T->father->lchild = T;
			T->rchild->father = T;
		}else{
			printf("这不是一颗查找树！");
		}
	}
}

void zag(SPTNode *T){
	if(T){
		if(T->father->value < T->lchild->value){
			T->father->rchild = T->lchild;
			if(T->lchild) T->lchild->father = T->father;
			T->lchild = T->father;
			T->father = T->father->father;
			if(T->father) T->father->rchild = T;
			T->lchild->father = T;
		}
	}
}

void splay(SPTNode *T){
	SPTNode *p = T;
	while(p&&p->father){
		p->value < p->father->father->value ? zig(p) : zag(p);
		p = p->father;
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
			break;
		}else{
			tmp = p->value > n ? p->lchild : p->rchild;
			if(tmp){
				if((n < tmp->value && tmp->value > p->value) || (n > tmp->value && tmp->value < p->value)){
					tmp = createNode();
					tmp->value = n;
					n < p->value ? (tmp->lchild = p->lchild) : (tmp->rchild = p->rchild);
					n < p->value ? (tmp->lchild->father = tmp) : (tmp->rchild->father = tmp);
					tmp->father = p;
					n < p->value ? (p->lchild = tmp) : (p->rchild = tmp);
					break;
				}else{
					p = tmp;
				}
			}else{
				tmp = createNode();
				tmp->value = n;
				p->value > n ? (p->lchild = tmp) : (p->rchild = tmp);
				tmp->father = p;
				break;
			}
		}
	}
}

void delete(SPTNode *T, int n){
	SPTNode *p = T;
	p = find(T,n);
	splay(p);
	T = join(p->lchild,p->rchild);
	free(p);
}

SPTNode* join(SPTNode *a, SPTNode *b){
	SPTNode *s = a;
	while(s->rchild){
		s = s->rchild;
	}
	splay(s);
	s->rchild = b;
	return s;
}

void split(SPTNode *T, int n, SPTNode *s1, SPTNode *s2){
	s1 = find(T,n);
	splay(s1);
	s2 = s1->rchild;
	s1 = s1->lchild;
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
	int a[] = {10,6,2,4,5,3,8,3,5,9,7};
	SPTNode *root;
	root = SPTInit(a);
	scan(root);
//	printf("%d\n",find(root,8)->value);
	return 0;
}
