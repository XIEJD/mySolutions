#include<stdio.h>
/**
	查找最小子序列值
*/

/*
	function prototype
*/
int minSubseq(int *,int ,int);
int minSubseq_n(int *);

int main(){
	int a[] = {1,-2,3,-4,-5,-6,7,-9,8};
	printf("%d\n%d\n",minSubseq(a,0,8),minSubseq_n(a));
	return 0;
}

int minSubseq(int *a,int h,int t){
	int left,right,mid,tmp,i,m = (h+t)/2;
	if( t-h == 0 ){
		 return a[h];
	}
	if( t-h == 1 ){
		if( a[h]<0 && a[t]<0 ){
			 return a[h]+a[t];
		}else{
			 return a[h]<a[t]?a[h]:a[t];	
		}
	}
	left = minSubseq(a,h,m-1);
	right = minSubseq(a,m+1,t);
	for( tmp =  mid = a[m], i = m-1; i >= h; i-- ){
		tmp += a[i];
		if( tmp < mid ){ 
			mid = tmp;	
		}
	}
	for( tmp = mid, i = m+1; i <= t; i++ ){
		tmp += a[i];
		if( tmp < mid ){
			 mid = tmp;
		}
	}
	if( left < right ){
		 tmp = left;
	}else{
		 tmp = right;
	}
	return mid<tmp?mid:tmp;
}

int minSubseq_n(int *a){
	int min = 0,sum = 0;
	for(int i = 0; i < 9; i++){
		sum += a[i];
		min = min < sum ? min : sum;
		if(sum > 0){
			sum = 0;
		}
	}
	return min;
}
