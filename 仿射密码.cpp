#include<stdio.h>
#include<string.h>
#define N 100
//������ϢΪ��This is the homework of (Your name, such as Liu Xin) 
int main()
{
	char m[N+1],c[N+1];
	int k1,k2;
	printf("������ԭ��:");
//�Իس������У���Ϊ�ַ�����ȡ�Ľ���,Ĭ�����ո񡢻س�������������� 
	scanf("%[^\n]",m);
//��ʼ����
	printf("\n��������Կk1,k2:");
//һ�ζ�ȡ�����ֵʱ�ĸ�ʽ����,Ĭ���Կո񡢻س��ָ���ֵ�������Զ��ŷָ���ͬ��ֵ������""�ڽ���ʽ����Ϊ"%d,%d"����scanf("%d,%d",&k1,&k2)������ʱ���Զ��ŷָ��� 
	scanf("%d%d",&k1,&k2); 

	for (int i=0;i<strlen(m);i++)
	{
////'a'��Ӧ97,'A'��Ӧ65. ������ʽ�ӵȼ� 
//c[i]=(m[i]-'a'+k2)%26+97;
//c[i]=(m[i]-97+k2)%26+97;
    	if(m[i]>='A'&&m[i]<='Z')
	    	c[i]='A'+(k1*(m[i]-'A')+k2)%26;
	else if(m[i]>='a'&&m[i]<='z')
	    	c[i]='a'+(k1*(m[i]-'a')+k2)%26;
	else c[i]=m[i];	
//���ַ����ÿһ�����ģ�

	 } 
	printf("\n������: %s",c);
	int r0=26,t0=0,t1=1,r1=k1,r2,t2,q;
	while(r1!=0)
	{
		q=r0/r1;
		r2=r0-q*r1;
		t2=t0-q*t1;
		r0=r1;r1=r2;
		t0=t1;t1=t2;
	}
	int k1_inv=t0;//��չŷ������㷨����Ԫ 
	printf("\n��Ԫ %d mod %d ��: %d",k1,r0,t0);
	
	for (int i=0;i<strlen(c);i++)
	{

    	if(c[i]>='A'&&c[i]<='Z')
	    	m[i]='A'+(t0*(c[i]-'A')-k2)%26;
	else if(c[i]>='a'&&c[i]<='z')
	    	m[i]='a'+(t0*(c[i]-'a')-k2)%26;
	else m[i]=c[i];	
	}//���� 
	printf("\nԭ����: %s",m);
	
}
