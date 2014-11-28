/**
	 郁闷的出纳员，基于伸展树
*/
#include <stdio.h>
#include "splayTree.c"

int basesalary;
int min;

/* 函数原型*/
int getBaseSalary(void);
void setBaseSalary(int );
int getMin(void);
void setMin(int);
void addAll(int );
void subAll(int );
int getSalary(int );
int findk(SPTNode *, int );				//找到第K大的工资
SPTNode *insertPerson(SPTNode *, int);			//创建节点
SPTNode *deletePerson(SPTNode *);			//将树中工资小于MIN的删除
SPTNode *setNobody(SPTNode *);				//找到离MIN最近的较大节点
void show(SPTNode*);
int stoi(char *);					//将字符串转化为整型值，此函数不能通用，仅此程序可用

/*函数定义*/
int getBaseSalary(void){
	return basesalary;
}

void setBaseSalary(int n){
	basesalary = n;
}	

void addAll(int n){
	basesalary += n;
}

void subAll(int n){
	basesalary = basesalary - n;
}

int getMin(void){
	return min;
}

void setMin(int n){
	min = n;
}

int getSalary(int n){
	return n + getBaseSalary();
}

int findk(SPTNode *T,int k){
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
			return T->value;
		}else if(n > k){
			return findk(T->rchild,k);
		}else{
			return findk(T->lchild,k-n);
		}
	}
}

SPTNode *setNobody(SPTNode *T){
	SPTNode *tmp = NULL;
	if(T){
		tmp = setNobody(T->lchild);
		if(!tmp){
			if(getSalary(T->value) > getMin()){
				return T;
			}
			return setNobody(T->rchild);
		}
	}
	return tmp;
}

SPTNode *deletePerson(SPTNode *T){
	SPTNode *p;
	p = setNobody(T);
	if(p){
		splay(p);
		if(p->rchild){
			p->nc = p->rchild->nc + 1;
			p->lchild = NULL;
		}
		return p;
	}else{
		return T;
	}
}

SPTNode *insertPerson(SPTNode *root, int n){ 
	if(root == NULL){
		root = createNode();
		root->value = n - getBaseSalary();	
	}else{
		insert(root,n);
	}
	return root;
}

void show(SPTNode *T){
	if(T!=NULL){
		show(T->lchild);
		printf("%d,%d\n",T->value + getBaseSalary(),T->nc);
		show(T->rchild);
	}
}

int stoi(char *a){
	int len = 0,i = 2,result,tmp = 1;
	while(a[i] != '\0' && i < 10){
		len++;
		tmp*=10;
		i++;
	}
	for(i = 2,result = 0,len--,tmp/=10; i <= len + 2; i++,tmp/=10){
		result += tmp * (a[i] - '0');
	}
	return result;
}

int main(){
	char cmd[20];
	int k,i=0;
	SPTNode *root = NULL;
	printf("----------------------------我是郁闷的出纳员-----------------------\n");
	printf("操作提示：\n");
	printf("\t\tI,k\t新建一个工资档案，初始工资为k\n");
	printf("\t\tA,k\t把每位员工的工资加上k\n");
	printf("\t\tS,k\t把每位员工的工资扣除k\n");
	printf("\t\tF,k\t查询第K多的工资\n");
	printf("\t\tM,K\t设置最低工资，低于这个标准将被公司除名（有点残忍）\n");
	printf("\t\tQ\t退出系统\n");
	printf("请选择操作:");
	scanf("%s",cmd); 
	getchar();
	while(cmd[0] != 'Q'){
		k = stoi(cmd);
		switch(cmd[0]){
			case 'I'	:root = insertPerson(root,k);
					if(root == NULL) printf("root为null");
					break;
			case 'A'	:addAll(k);
					break;
			case 'S'	:subAll(k);
					break;
			case 'F'	:printf("\n第%d多的工资为：%d",k,findk(root,k));
					break;
			case 'M'	:setMin(k);
					break;
			default		:printf("\n操作错误!\n");
		}
		root = deletePerson(root);
		show(root);
		printf("\n您可以继续操作：");
		scanf("%s",cmd);
		getchar();
	}
	return 0;
}
