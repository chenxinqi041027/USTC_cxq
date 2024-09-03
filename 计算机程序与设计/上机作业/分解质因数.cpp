#include<stdio.h>
int Isprime(int n)
{
	for(int i=2;i<n;i++)
		if(n%i==0) return 1;
		return 0;
}
void fun(int n)
{
	int j,m=n,d;
	for(j=2;j<n/2;j++){
		while(m%j==0){
			printf("%d*",j);
			m/=j;
			d=Isprime(m);
			if(d!=1) goto there;
		}
	}
	there:printf("%d\n",m);
}
int main(){
	while(1){
	int n,c;
	scanf("%d",&n);
	printf("%d=",n);
	c=Isprime(n); 
	if(c) fun(n);
	else printf("%d ÊÇËØÊý\n",n);
	}
	return 0; 
}

