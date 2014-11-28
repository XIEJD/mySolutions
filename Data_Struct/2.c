/**
	序列和的前n小元素
	input		：A，B两个数组
	output		：所有从A取一个数，B取一个数组成的和的前N小元素
	思路		：直接加起来用堆排序，其实在建堆时就已经排好了
*/

#include "binaryHeap.c"


int main(){
	int A[] = {10,1,2,3,4,5,5,6,7,8,9};
	int B[] = {10,1,2,9,12,13,16,18,21,23,33};
	int result[A[0]*B[0]],ma,mb;
	BTNode *re;
	re = createNode();
	re->value = A[1] + B[1] ;
	for(int i = 1; i < A[0]; i++){
		for(int j = 1; j < B[0]; j++){
			if(i == 1) continue;
			insert(re,A[i]+B[j]);	
		}	
	}
	
	for(int i = 0; i < A[0]; i++){
		printf("%d\n",getRoot(re));
		deleteRoot(re);
	}
	return 0;
}
