#include<stdio.h>
#include<math.h>
int main()
{
	int t=3;
	while(t--){
	
	double x;//����x 
	double sum=0;//;
	printf("������x��ֵ");
	scanf("%lf",&x);
	
	int n=1;//ѭ��n�� 
	while(n<1024){
		float m=2*n-1; 
		float a=n%2;
		float b;
		if(a>=1) b=1;
		else b=-1;//�ж������� 
	
		double c=pow(x,m);//���x��m����
		
		double i;
		double fact=1;
		for(i=1;i<=m;i++) fact*=i;//���m�Ľ׳�	
		printf("%lf\n",fact);
		
		double result=b*c/fact;//�ó�ÿ����� 
	
		sum=sum+result;
		n++;
		 
	}
	
	printf("sinx=%.6lf\n",sum);
	}
	return 0;
}
//ѭ��n��,m=2n+1
//nΪż����-1��Ϊ������1������b,��n%2,if>=1,��1,if=0,��-1
//pow x��m����
//��m�Ľ׳�Ϊc 
//d=x��m����* b/(m�Ľ׳�)
//sum=sum+a
