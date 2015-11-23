/*
 *装配线调度问题，用动态规划的思想解决。
 *
 * 假设有两条装配线，a和b，它们执行的是相同的功能
 * 每条装配线上有n个站。
 * 每个站的装配时间a[i],b[j],i,j=1,2,...n
 * 物品进入装配线的时间ae,be
 * 物品离开装配线的时间ax,bx
 * 
 * 当物品在不同装配线之间调度的时候
 * 离开a装配线到b的时间为ab[i],i表示装配站
 * 离开b装配线到a的时间为ba[i],i表示装配站
 *
 * 问题：如何调度一个物品，使其最快通过装配线。
 *
 * 按书中方法，但是复杂度太高。
 * */

#include<stdio.h>

#define MAX_SIZE 6

int result[MAX_SIZE+1][3];
int currentp = 0;
int a[MAX_SIZE+1] = {MAX_SIZE,7,9,3,4,8,4};
int b[MAX_SIZE+1] = {MAX_SIZE,8,5,6,4,5,7};
int ae = 2;
int be = 4;
int ab[MAX_SIZE] = {MAX_SIZE-1,2,3,1,3,4};
int ba[MAX_SIZE] = {MAX_SIZE-1,2,1,2,2,1};
int ao = 3;
int bo = 2;

int findFast(int, int);
int assemblyLine(int, int);
void push(int, int, int);

int main(){
	int desassm,desline,cost;

	desassm = 7;
	desline = 2;
	assemblyLine(desassm,desline);

	printf("To line %d, assem %d\n",desline,desassm);
	for(int i = 0; i <= desassm && i <= MAX_SIZE; i++){
		printf("line %d, station %d ->\n",result[i][0], result[i][1]);
	}
	printf("over\n");
	printf("total cost: %d\n",desassm < MAX_SIZE ? result[desassm][2] : result[MAX_SIZE][2]);
	return 0;
}

//当一个物品以最快速度经过j站时，那它肯定时以最快速度经过j－1站
//由此递归。
int assemblyLine(int desassm, int desline){
	int costa,costb,cost;
	if(desassm > MAX_SIZE){
		costa = findFast(MAX_SIZE,1)+a[MAX_SIZE]+ao; 
		costb = findFast(MAX_SIZE,2)+b[MAX_SIZE]+bo;
		if(costa < costb){
			push(MAX_SIZE,1,costa-a[MAX_SIZE]-ao);
			return costa;
		}else{
			push(MAX_SIZE,2,costb-b[MAX_SIZE]-bo);
			return costb;
		}
	}else{
		cost = findFast(desassm,desline);
	}	
	push(desassm, desline, cost);
	return cost;
}

//返回到达该点的cost
int findFast(int desassm,int desline){
	int da,dl;
	int costaa,costbb,costab,costba;
	if(desassm == 1){
		if(desline == 1 ){
			return ae + a[1];
		}else{
			return be + b[1];
		}
	}else{
		if(desline == 1){
			costaa = findFast(desassm-1,1) + a[desassm];
			costba = findFast(desassm-1,2) + ba[desassm-1] + a[desassm];//ba为前一个点到此点的转移时间
			if(costaa < costba){
				dl = 1;
				push(desassm-1,dl,costaa - a[desassm]);
				return costaa;
			}else{
				dl = 2;
				push(desassm-1,dl,costba - ba[desassm-1] - a[desassm]);
				return costba;
			}
		}else{
			costbb = findFast(desassm-1,2) + b[desassm];
			costab = findFast(desassm-1,1) + ab[desassm-1] + b[desassm];
			if(costbb < costab){
				dl = 2;
				push(desassm-1,dl,costbb - b[desassm]);
				return costbb;
			}else{
				dl = 1;
				push(desassm-1,dl,costab - ab[desassm-1] - b[desassm]);
				return costab;
			}
		}
	}
}

void push(int desassm, int desline, int cost){
	if(result[desassm][2] == 0 || result[desassm][2] > cost){
		result[desassm][0] = desline;
		result[desassm][1] = desassm;
		result[desassm][2] = cost;
	}
}
