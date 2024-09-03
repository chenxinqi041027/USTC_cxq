#include<stdio.h>
int main()
{
	int m=1;
	while(m++){
	printf("请输入三个数字：");
	int a,b,c;
	int x;
	scanf("%d %d %d",&a,&b,&c);
	int t;
	if(a+b>c&&a+c>b&&b+c>a){
		t=1;
		if(a==b&&b!=c||a==c&&c!=b||b==c&&c!=a) t=2;
		if(a*a+b*b==c*c||a*a+c*c==b*b||b*b+c*c==a*a) t=3;
		if(a==b&&b==c) t=4;
	} else t=5;
	switch(t){
		case 1:
			printf("YES\n");
			break;
		case 2:
			printf("等腰\n");
			break;
		case 3:
			printf("Right Triangle\n");
			break;
		case 4:
			printf("Equilatera; Triangle\n");
			int i,j,k;
			for(i=1;i<=a;i++){
				for(j=1;j<=a-i;j++){
					printf(" ");
				}
				for(k=1;k<=(2*i-1);k++){
					printf("*");
				} 
				printf("\n");
			}
			
			break;
		case 5:
			printf("No\n");
			break; 
	}
}
	
	return 0; 
}
//判断两边之和大于第三百边
//判断是否有三边相等
//判断是否有直角 
