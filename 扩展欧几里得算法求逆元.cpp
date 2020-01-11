#include<stdio.h>
int exgcd(int m,int n,int &x,int &y)//扩展欧几里得算法
{
    int x1,y1,x0,y0;
    x0=1; y0=0;
    x1=0; y1=1;
    x=0; y=1;						//初始化x0,y0,x1,y1 
    int r=m%n;						//令r=i mod j
    int q=(m-r)/n;					
    while(r)
    {
        x=x0-q*x1; y=y0-q*y1;		
        x0=x1; y0=y1;
        x1=x; y1=y;					//x0=y1,y0=x1-(m/n)y1
        m=n; n=r; r=m%n;
        q=(m-r)/n;
    }
    return n;
}

int mod_reverse(int a,int n)//ax=1(mod n) 求a的逆元x 
{
    int d,x,y;
    d=exgcd(a,n,x,y);		//调用扩展欧几里得算法求最大公因数 
    if(d==1)				//如果做大公因数是1，gcd(a,n)=1则存在逆元 
        return (x%n+n)%n;	//求a的逆相当于求解ax=1(mod n),这个方程可以转化为ax-my=1,
		//然后套用二元一次方程的方法，用扩展欧几里得算法求得一组x0,y0和gcd
    else
        return -1;
}

int main(){
	int i,j;
	printf("input a,n(ax=1(mod n)):") ;
	scanf("%d%d",&i,&j);
	printf("mod_reverse a is:%d",mod_reverse(i,j));
	return 0;
} 

/*int exgcd(int a,int b,int &x,int &y)       //扩展欧几里得 
{
    if(b==0)
    {
        x=1;
        y=0;
        return a;
    }
    int r=exgcd(b,a%b,x,y);
    int t=x;
    x=y;
    y=t-a/b*y;
    return r;
}*/
