#include<stdio.h>
#include<string.h>
#define N 100
//明文信息为：This is the homework of (Your name, such as Liu Xin) 
int main()
{
	char m[N+1],c[N+1];
	int k1,k2;
	printf("请输入原文:");
//以回车（换行）作为字符串读取的结束,默认遇空格、回车、跳格键结束。 
	scanf("%[^\n]",m);
//开始加密
	printf("\n请输入密钥k1,k2:");
//一次读取多个数值时的格式设置,默认以空格、回车分隔数值，若想以逗号分隔不同数值则需在""内将格式设置为"%d,%d"，如scanf("%d,%d",&k1,&k2)则输入时仅以逗号分隔。 
	scanf("%d%d",&k1,&k2); 

	for (int i=0;i<strlen(m);i++)
	{
////'a'对应97,'A'对应65. 以下两式子等价 
//c[i]=(m[i]-'a'+k2)%26+97;
//c[i]=(m[i]-97+k2)%26+97;
    	if(m[i]>='A'&&m[i]<='Z')
	    	c[i]='A'+(k1*(m[i]-'A')+k2)%26;
	else if(m[i]>='a'&&m[i]<='z')
	    	c[i]='a'+(k1*(m[i]-'a')+k2)%26;
	else c[i]=m[i];	
//单字符输出每一个密文：

	 } 
	printf("\n密文是: %s",c);
	int r0=26,t0=0,t1=1,r1=k1,r2,t2,q;
	while(r1!=0)
	{
		q=r0/r1;
		r2=r0-q*r1;
		t2=t0-q*t1;
		r0=r1;r1=r2;
		t0=t1;t1=t2;
	}
	int k1_inv=t0;//扩展欧几里得算法求逆元 
	printf("\n逆元 %d mod %d 是: %d",k1,r0,t0);
	
	for (int i=0;i<strlen(c);i++)
	{

    	if(c[i]>='A'&&c[i]<='Z')
	    	m[i]='A'+(t0*(c[i]-'A')-k2)%26;
	else if(c[i]>='a'&&c[i]<='z')
	    	m[i]='a'+(t0*(c[i]-'a')-k2)%26;
	else m[i]=c[i];	
	}//解密 
	printf("\n原文是: %s",m);
	
}
