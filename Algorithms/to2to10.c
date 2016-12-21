/**
	将十进制转换成二进制
*/

#include<stdio.h>

/*
	函数原型
*/

void toBinary(int);
void toDecimal(int);

/*
	函数定义
*/

void toBinary(int n){
	int tmp;
	tmp = n % 2;
	if(n > 0){
		toBinary(n >> 1);
		putchar('0'+tmp);
	}
}

void toDecimal(int n){
	int tmp = 0,i = 1;
	while(n > 0){
		tmp += (n % 2)*i;
		n /= 10;
		i *= 2;
	}
	printf("%d",tmp);
}

int main(){
	int test2 = 10111,test10 = 23;
	toBinary(test10);
	toDecimal(test2);
	return 0;
}
//输出：
//10111
//23
