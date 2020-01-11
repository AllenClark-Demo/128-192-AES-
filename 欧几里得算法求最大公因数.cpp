#include<stdio.h>
int gcd(int i,int j){//定义求最大公因数的函数，有两个参数i,j是要求最大公因数的两个数 
	while(j!=0)
	{
		int r=j;     //定义r为中间变量，用于交换i,j的值 
		j=i%j;     	 //求i,j的余数 
		i=r;
	}                //根据欧几里得算法，gcd(i,j)=gcd(j,i%j)，在j！=0的条件下循环计算 
	return i;
}
int main(){
	int i,j;
    printf("input i,j:");
    scanf("%d %d",&i,&j);
    printf("gcd of i,j is:%d",gcd(i,j));
    return 0;
} 
