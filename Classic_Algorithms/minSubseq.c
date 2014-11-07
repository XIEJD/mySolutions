#include<stdio.h>
/**
	查找最小子序列值
*/

/*
	function prototype
*/
int minSubseq(int *,int ,int);

int main(){
	int a[] = {1,2,3,4,5,6,7,8,9};
	printf("%d\n",minSubseq(a,0,8));
	return 0;
}

int minSubseq(int *a,int h,int t){
	int left,right,mid,tmp,i;
	if(t-h==0) return a[h];
	if(t-h==1){
		if(a[h]<0&&a[t]<0) return a[h]+a[t];
		else return a[h]<a[t]?a[h]:a[t];	
	}
	left = minSubseq(a,h,(t+h)/2-1);
	right = minSubseq(a,(t+h)/2+1,t);
	for(tmp=0,mid=a[(h+t)/2],i=(h+t)/2-1; i>=h; i--){
		tmp+=a[i];
		if(tmp<mid) mid=tmp;	
	}
	for(tmp=mid,i=(h+t)/2+1; i<=t; i++){
		tmp+=a[i];
		if(tmp<mid) mid=tmp;
	}
	if(left<right) tmp = left;
	else tmp = right;
	return mid<tmp?mid:tmp;
}
