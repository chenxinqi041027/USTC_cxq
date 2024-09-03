#include<stdio.h>
#include<math.h>
int main()
{
	int t=3;
	while(t--){
	
	double x;//定义x 
	double sum=0;//;
	printf("请输入x的值");
	scanf("%lf",&x);
	
	int n=1;//循环n次 
	while(n<1024){
		float m=2*n-1; 
		float a=n%2;
		float b;
		if(a>=1) b=1;
		else b=-1;//判断正负号 
	
		double c=pow(x,m);//解决x的m次幂
		
		double i;
		double fact=1;
		for(i=1;i<=m;i++) fact*=i;//解决m的阶乘	
		printf("%lf\n",fact);
		
		double result=b*c/fact;//得出每个结果 
	
		sum=sum+result;
		n++;
		 
	}
	
	printf("sinx=%.6lf\n",sum);
	}
	return 0;
}
//循环n次,m=2n+1
//n为偶数乘-1，为奇数乘1，定义b,用n%2,if>=1,乘1,if=0,乘-1
//pow x的m次幂
//求m的阶乘为c 
//d=x的m次幂* b/(m的阶乘)
//sum=sum+a
