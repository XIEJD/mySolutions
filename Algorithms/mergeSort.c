#include<stdio.h>

/*
	function prototype
*/
void mergeSort(int a[], int length);
void merge(int a[], int h, int m, int t);

int main(){
	int a[] = {9,8,7,6,5,4,3,2,0,1};
	mergeSort(a,10);
	for(int i=0; i<10; i++){
		 printf("%d ",a[i]);
	}
	return 0;
}

void mergeSort(int a[],int length){
	int d = 2,z,y,m;
	for(; d/2<length; d*=2){
		z = length/d;
		y = length%d;
		for(int i=0,h=0; i<=z; i++,h=i*d){
			if(i<z){
				 merge(a,h,h+d/2,h+d-1);
			}else if(y>d/2){
				 merge(a,h,h+d/2,h+y-1);
			}
		}
	}
}

void merge(int a[], int h, int m, int t){
	int tmp[t-h+1],i=0,j,k;
	for(j = h,k = m; j < m && k <= t; i++){
		if(a[j] > a[k]){
			tmp[i] = a[k];
			k++;
		}else{
			tmp[i] = a[j];
			j++;
		}
	}
	if(j<m){
		 for(; j<m; i++,j++) tmp[i] = a[j];
	}
	if(k<=t){
		for(; k<=t; i++,k++) tmp[i] = a[k];
	}
	for(int j = h,i = 0; i<t-h+1; i++,j++) a[j] = tmp[i];
}
