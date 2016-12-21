/**
*
*	Enter a number and have the program generate PI up to that many decimal digital places,
*	keey a limit to how far the program will go.
*	
*	输入一个数n，找到PI的小数点后n位。设置一个n的最大值确保程序不会走的太远
*/
#include<stdio.h>
#include<math.h>
void main(){
    int Pi[]={20,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6},n,i;
   printf("Please Enter Your Number of Digits(Max 20,Min 1):\n");
   scanf("%d",&n);
   if(n>0&&n<=20) for( i = 1,printf("3.");i<=n;i++) printf("%d",Pi[i]);
}

