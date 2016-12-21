#include<stdio.h>

/*
	function prototype
*/
void bubleSort(int *);

int main(){
	int a[]={10,9,8,7,6,5,4,3,2,1,10};
	bubleSort(a);
	for(int i=1; i<=a[0]; i++) printf("%d ",a[i]);
	return 0;
}

void bubleSort(int *n){
	for(int i = 1; i<=n[0]; i++){
		for(int tmp,t = i+1; t<=n[0]; t++){
			if(n[i] > n[t]){
				tmp = n[i];
				n[i] = n[t];
				n[t] = tmp;		
			}
		}
	}
}
