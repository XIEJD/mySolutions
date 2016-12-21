#include<stdio.h>

/*
	function prototype
*/
int collatz(int);

int main(int argc, char* argv[]){
	int n;
	printf("Please enter a number:");
	scanf("%d",&n);
	printf("%d\n",collatz(n));
	return 0;
}

int collatz(int n){
	if(n==1) return 0;
	else if(n%2==0) return collatz(n/2)+1;
	else return collatz(3*n+1)+1;
}
