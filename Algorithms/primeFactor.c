#include<stdio.h>
#include"math.h"
/*
	function prototype
*/

int isPrimeFactor(int);

int main(int argc, char *argv[]){
	int n;
	printf("Please enter a number:");
	scanf("%d",&n);
	for(int i=1; i<=n; i++) 
		if(isPrimeFactor(i)) printf("%d\n",i);	
	return 0;
}


int isPrimeFactor(int n){
	int tmp = sqrt(n);
	for(int i=2; n>0&&i<=tmp; i++)
		if(n%i==0) return 0;
	return 1;
}
