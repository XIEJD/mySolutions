/**
	Frequent values
*/

#include<stdio.h>
#include<stdlib.h>


/*节点结构体*/
typedef struct FVData{
	int fv,count;
	int lv,lcount;	//左边界值，频率
	int rv,rcount;	//右边界值，频率
}FVData;

typedef struct LBTNode{
	FVData *data;
	int left,mid,right;
	struct LBTNode *lchild,*rchild;
}LBTNode;

/*函数原型*/
LBTNode* createNode();
FVData* createDataNode();
LBTNode* init(int *);					/*在数组上生成二叉树节点（平衡树）*/
LBTNode* mergeNode(int *, int, int);			/*合并二个子节点，即生成父节点*/
FVData* find_fv(LBTNode *, int, int);			/*在树中找到出现最多的数*/
void mergeData(FVData *, FVData *, FVData *);		/*合并FV的数据包*/
int countMid(int *,int, int);				//废弃

/*函数定义*/
LBTNode *createNode(){
	return malloc(sizeof(LBTNode));
}

FVData *createDataNode(){
	return malloc(sizeof(FVData));
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
	FVData *data;
	int max;
	if(!(node = createNode())){
		printf("无法创建节点!\n");
	}
	if(!(data = createDataNode())){
		printf("无法创建数据节点\n");
	}
	node->left = l;
	node->right = r;
	node->mid = (l+r)/2;
	node->data = data;
	if(l == r){
		data->lv = data->rv = data->fv = a[l];
		data->lcount = data->rcount = 1;
		data->count = 1;
	}else{
		node->lchild = mergeNode(a,l,(l+r)/2);
		node->rchild = mergeNode(a,(l+r)/2+1,r);
		mergeData(data,node->lchild->data,node->rchild->data);
	}
	return node;
}

void mergeData(FVData *out, FVData *inl, FVData *inr){

	if(inl->fv == inr->fv){
		out->count = inl->count + inr->count;
		out->fv = inl->fv;
	}else{
		out->fv = inl->count > inr->count ? (out->count = inl->count, inl->fv) : (out->count = inr->count, inr->fv);
		if(inl->rv == inr->lv && inl->rcount + inr->lcount > out->count){
			out->fv = inl->rv;
			out->count = inl->rcount + inr->lcount;
		}
	}

	if(inl->lv == inl->rv && inl->rv == inr->lv){
		out->lv = inl->lv;
		out->lcount = inl->count + inr->lcount;
	}else{
		out->lv = inl->lv;
		out->lcount = inl->lcount;
	}

	if(inr->lv == inr->rv && inl->rv == inr->lv){
		out->rv = inr->rv;
		out->rcount = inr->count + inl->rcount;
	}else{
		out->rv = inr->rv;
		out->rcount = inr->rcount;
	}
}

FVData* find_fv(LBTNode *root, int l, int r){
	if(l == root->left && r == root->right){
		return root->data;
	}else{
		if(l > root->mid){
			return find_fv(root->rchild,l,r);
		}else if(r <= root->mid){
			return find_fv(root->lchild,l,r);
		}else{
			FVData *tmp = createDataNode();
			mergeData(tmp,find_fv(root->lchild,l,root->mid),find_fv(root->rchild,root->mid+1,r));
			return tmp;
		}
	}
}


int main(){
	int a[] = {20,1,1,1,2,2,2,2,3,3,3,4,4,5,5,5,5,5,5,7,8};		//0下标为数组有效值长度
	LBTNode *root;
	FVData* result;
	root = init(a);
	result = find_fv(root,6,10);
	printf("fv = %d\ncount = %d\n",result->fv,result->count);
	return 0;
}
