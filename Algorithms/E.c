/**
	Find e to the Nth digits
*/

#include<stdio.h>
#include<math.h>
void main(){
   int E[]={19,7,1,8,2,8,1,8,2,8,4,5,9,0,4,5,2,3,5,4},n,i;
   printf("Please Enter Your Number of Digits(Max 19,Min 1):\n");
   scanf("%d",&n);
   if(n>0&&n<=19) for( i = 1,printf("2.");i<=n;i++) printf("%d",E[i]);
}
