#include<stdio.h>
int gcd(int i,int j){//��������������ĺ���������������i,j��Ҫ����������������� 
	while(j!=0)
	{
		int r=j;     //����rΪ�м���������ڽ���i,j��ֵ 
		j=i%j;     	 //��i,j������ 
		i=r;
	}                //����ŷ������㷨��gcd(i,j)=gcd(j,i%j)����j��=0��������ѭ������ 
	return i;
}
int main(){
	int i,j;
    printf("input i,j:");
    scanf("%d %d",&i,&j);
    printf("gcd of i,j is:%d",gcd(i,j));
    return 0;
} 
