/**
	二叉堆
*/

#include<stdio.h>
#include<stdlib.h>

/*
	数据结构
*/
typedef struct BTNode{
	int value;
	struct BTNode *lchild,*rchild,*father;
}BTNode;

/*
	基本操作 (函数原型)
*/
void swap(BTNode*,BTNode*);		//交换元素
void sink(BTNode*);			//元素“下沉”
void swim(BTNode*);			//元素“上浮”
BTNode* creatNode();			//创建节点
void insert(BTNode*,int);		//插入元素到堆
int getRoot(BTNode*);			//获得根元素
void deleteRoot(BTNode*);		//删除根元素
BTNode* init(int*);			//把数组建立成堆
BTNode* findFather(BTNode*);		//找到新节点应该插入的指针的地址
BTNode* findTail(BTNode*);		//找到“尾巴”元素

/*
	函数定义
*/
void swap(BTNode *a,BTNode *b){
	int tmp;
	tmp = a->value;
	a->value = b->value;
	b->value = tmp;
}

BTNode* createNode(){
	return malloc(sizeof(BTNode));
}

BTNode* init(int* d){							//传入数组0下标的值为有效数的个数
	BTNode* root = createNode();
	root->value = d[1];
	for(int i = 2; i <= d[0]; i++) insert(root,d[i]);
	return root;
}

void sink(BTNode* a){
	if(a->lchild && a->value > a->lchild->value){
		swap(a,a->lchild);
		sink(a->lchild);
	}
	if(a->rchild && a->value > a->rchild->value){
		swap(a,a->rchild);
		sink(a->rchild);
	}
}

BTNode* findFather(BTNode* T){						//树满没满的问题，所以挖右节点的深度
	int ll = 0, rl = 0;
	BTNode *r = T->rchild, *l = T->lchild;
	if(!T->lchild || !T->rchild){
		return T;
	}
	while(l){
		l = l->rchild;
		ll++;
	}	
	while(r){
		r = r->rchild;
		rl++;
	}
	if(ll == rl) return findFather(T->lchild);
	if(ll-rl == 1) return findFather(T->rchild);
}

BTNode* findTail(BTNode* T){						//树有没有的问题，所以挖左节点的深度
	int ll = 0, rl = 0;
	BTNode *r = T->rchild, *l = T->lchild;
	if(!r && !l) return T;
	while(l){
		l = l->lchild;
		ll++;
	}
	while(r){
		r = r->lchild;
		rl++;
	}
	if(ll == rl) return findTail(T->rchild);
	if(ll-rl == 1) return findTail(T->lchild);
}

void swim(BTNode* a){
	if(a->father && a->value < a->father->value){
		swap(a,a->father);
		swim(a->father);
	}
}
void insert(BTNode *T,int v){
	BTNode *newnode = createNode(),*father;
	newnode->value = v;
	newnode->father = father = findFather(T);
	if(!father->lchild && !father->rchild){
		 father->lchild = newnode;
	}else{
		 father->rchild = newnode;
	}
	swim(newnode);
}

void deleteRoot(BTNode *T){
	BTNode* tmp = findTail(T);
	T->value = tmp->value;
	if(!T->lchild && !T->father){
		free(T);
	}else{
		if(tmp->father->rchild) tmp->father->rchild = NULL;
		else tmp->father->lchild = NULL; 
		free(tmp);
		sink(T);
	}	
}

int getRoot(BTNode *T){
	return T->value;
}
/*
int main(){
	int n[] = {10,9,8,7,6,5,4,3,2,1,0};	
	BTNode *root = init(n);
	for(int i = 1; i <= n[0]; i++){
		printf("%d\n",getRoot(root));
		deleteRoot(root);
	}
	return 0;
}
*/

