/**
	每个数的前面数中，和它最接近的数
*/
#include<stdio.h>
#include<stdlib.h>
/*数据结构*/
typedef struct LNode{
	int value;
	struct LNode *n,*p;
}LNode;

/*函数原型*/
LNode *createNode();
LNode *init(int *);		//将一个数组初始化成一个有序非递减的双向链表
void insert(LNode **, int);
void delete(LNode *);
LNode *init(int *);
LNode *find(LNode *, int );



/*函数定义*/
LNode *createNode(){
	return malloc(sizeof(LNode));
}

void insert(LNode **L, int n){
	LNode *tmp = createNode(),*p = *L;
	tmp->value = n;
	if(*L){
		if((*L)->value > n){
			tmp->n = *L;
			(*L)->p = tmp;
			*L = tmp;	
		}else{
			while(p){
				if(p->n){
					if(p->n->value >= n && n >= p->value){
						tmp->p = p;
						tmp->n = p->n;
						p->n->p = tmp;
						p->n = tmp;
						break;
					}else{
						p = p->n;
					}
				}else{
					p->n = tmp;
					tmp->p = p;
					break;
				}
			}
		}
	}
}

void delete(LNode *L){
	if(L->n && L->p){
		L->n->p = L->p;
		L->p->n = L->n;
	}else if(L->p){
		L->p->n = NULL;
	}else if(L->n){
		L->n->p = NULL;
	}
	free(L);
}

LNode *init(int *a){
	LNode *head = createNode();
	head->value = a[1];
	for(int i = 2; i <= a[0]; i++){
		insert(&head,a[i]);
	}
	return head;
}

LNode *find(LNode *L, int n){
	LNode *p = L;
	while(p && n!=p->value){
		p = p->n;
	}
	return p;
}

int main(){
	int a[] = {9,2,7,1,6,8,2,5,3,4};
	int result[a[0]+1];
	LNode *head,*k;
	head = init(a);
	for(int i = a[0]; i > 0; i--){
		k = find(head,a[i]);
		if(k->p && k->n){
			result[i] = a[i] - k->p->value < k->n->value - a[i] ? k->p->value : k->n->value;
		}else if(k->p){
			result[i] = k->p->value;
		}else if(k->n){
			result[i] = k->n->value;
		}else{
			result[i] = 0;
		}
		delete(k);
	}
	for(int i = 1; i <= a[0]; i++){
		printf("%d---%d\n",a[i],result[i]);
	}
	return 0;
}

