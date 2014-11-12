/*
	Name: big heap
*/
#include<stdio.h>
void swap(int *n, int a, int b){
	int temp;
	temp = n[a];
	n[a] = n[b];
	n[b] = temp;
}

void sink(int *n, int index){
	int maxi = index;
	if(2*index <= n[0]){
		if(n[index] < n[2*index]) maxi = index*2;
		if(2*index+1 <= n[0]&&n[maxi] < n[2*index+1]) maxi += 1;
		if(maxi != index){
			swap(n,maxi,index);
			sink(n,maxi);
		}
	}
} 

void swim(int *n, int index){
	int maxi = index;
	if(index >= 1){
		if(n[index] < n[index/2]) maxi = index/2;
		if(maxi == index){
			swap(n,maxi,maxi/2);
			swim(n,maxi/2);
		}
	}
}

void init(int *n){
	int p;
	for(p = n[0]/2; p >= 1; p--) sink(n,p);
}

int delete(int *n, int index){
	int re = n[index];
	n[index] = n[n[0]--];
	sink(n,index);
	return re;
}

void insert(int *n, int e){
	n[++n[0]] = e;
	swim(n,n[0]);
}

void main(){
	int i,n[] = {10,0,1,2,3,4,5,6,7,8,9};
	int length = n[0];
	init(n);
	printf("init result:\n"); 
	for(i = 1; i <= length; i++)
		printf("%d ",n[i]);
	printf("\noutput heap in order:\n");
	for(i = 1; n[0]; i++)
		printf("%d ",delete(n,1));
}
