#include<stdio.h>

/*

int gcd(int i; int j){
    int i,j;
	int temp;
	
	scanf("%d",&i);
	scanf("%d",&j);
	while(j!=0){
		temp=j;
		j=i%j;
		i=temp;
		
	}
	/*printf("GCD is :%d\n",i);
	return 0;*/
/*eturn i
	
}
int main()
{ 
	int a,b,c;
	printf("please input a,b,c:");
	scanf("%d,%d,%d",&a,&b,&c);
	if()
    gcd(a,b);
	return 0;
}
*/


void exEuclidean(int a,int b,int &s,int &t){
	
int r1 = a, r2 = b , s1 = 1, s2 = 0, t1 = 0, t2 = 1;//初始化
	
int q,r; 
	
while(r2 > 0)
{
        
q = r1 / r2;
 
       	
r = r1 - q * r2; //也就是r = r1%r2;
      	
r1 = r2;
       	
r2 = r;
 
      	
s = s1 - q * s2;
	  	
s1 = s2;
	  	
s2 = s;
	  
	  	
t = t1 - q * t2;
	  	
t1 = t2;
	  	
t2 = t; 
	
}
	
//gcd(a,b) = r1; 
	
s = s1; 
	
t = t1;

}
 

int gcd(int x,int y){
	
return y == 0 ? x : gcd(y,x%y); 

} 

int main()
{
	
int a,b,c;
	
printf("请依次输入ax + by = c中的参数a,b,c！\n");
	
scanf("%d %d %d",&a,&b,&c); 
	
//首先求出gcd(a,b),利用朴素欧几里得算法 
	
int gcd_a_b = gcd(a,b);
	
if(c % gcd_a_b != 0){
		
printf("c不能整出gcd(a,b)，该方程无整数解!\n");
		
return 0; 
	
}
	
else{ //会有无穷多个解 
		
int a1 = a / gcd_a_b;
		
int b1 = b / gcd_a_b;//这个时候a1和b1肯定互质了 
		
int c1 = c / gcd_a_b;
		
//变成解方程 a1 * x + b1 * y = c1
		
		
//利用扩展的欧几里得算法求 a1 * s + b1 * t = 1（注意：1是a1和b1的gcd） 
		
int s,t;
		
exEuclidean(a1,b1,s,t); //因为传引用，s和t得到解了
		
//得到特解
		
int x0 = c / gcd_a_b * s , y0 = c / gcd_a_b * t;
		
printf("得到特解：%d 和 %d\n",x0,y0);
		
printf("通解是 x = %d + k * %d 和 y = %d - k * %d,(k为任意整数)\n",x0,b1,y0,a1);
	
}
}
/*

s0=1;
s1=0;
s2=0;
t0=0;
t1=1;
t2=0;
while(t1!=0)
{
	q=r0/r1;
	r2=r0-q*r1;
	s2=s0-q*s1;
	t2=t0-q*t1;
	r0=r1;
	r1=r2;
	t0=t1;
	t1=t2;
	s0=s1;
	s1=s2;
	printf("\nr0,r1:%d,%d",r0,r1);
	printf("\ns2,t2:%d,%d",s2,t2);
	
}
if(t0<0){
	t0=t0+a
}
if(r0==1)
{
	printf("\nInreverse of %d mod %d is::%d",b,a,t0)
	
}
return 0;
}
*/
