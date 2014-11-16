/**
	字符串翻转
*/

#include<stdio.h>
/*
	函数原型
*/

void strRev(char *s);

/*
	函数定义
*/

void strRev(char *s){
	char tmp,*h = s,*t = s;
	while(*(t+1)!='\0') t++;
	for(; h < t; h++,t--){
		tmp = *h;
		*h = *t;
		*t = tmp;
	}
}

int main(){
	char str[] = {'h','a','p','p','y',' ','e','n','d','i','n','g'};
	strRev(str);
	printf("%s\n",str);
	return 0;
}
