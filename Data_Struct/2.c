/**
	序列和的前n小元素
	input		：A，B两个数组
	output		：所有从A取一个数，B取一个数组成的和的前N小元素
*/

#include "binaryHeap.c"

int main(){
	int A[] = {10,3,4,6,1,8,9,7,2,5,5};
	int B[] = {10,23,1,2,33,12,13,9,21,16,18};
	int result[10],tmp;
	BTNode *a,*b;
	a = init(A);
	b = init(B);
	tmp = getRoot(a) > getRoot(b) ? getRoot(b) :getRoot(a);
	if(getRoot(a) > getRoot(b)){
		for(int i = 0; i < A[0]; i++){
			result[i] = tmp + getRoot(a);
			deleteRoot(a);
			printf("%d\n",result[i]);
		}
	}else{
		for(int i = 0; i < A[0]; i++){
			result[i] = tmp +getRoot(b);
			deleteRoot(b);
			printf("%d\n",result[i]);
		}
	}
	return 0;
}
