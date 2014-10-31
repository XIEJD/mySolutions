#include<stdio.h>

int main(int argc, char *argv[]){
	int n;	
	printf("Please input a number to show the fibonacci sequence:");
	scanf("%d",&n);
	for(int i=1; i<=n; i++)	
		printf("%d\n",fibonacci(i));
	return 0;
}

int fibonacci(int n){
	if(n==1||n==2){
		return 1;
	}
	return fibonacci(n-1)+fibonacci(n-2);
}
