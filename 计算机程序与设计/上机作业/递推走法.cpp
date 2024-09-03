#include<stdio.h>
int main(){
	//while(1){
		int i,n;
		printf("请输入步数：");
		scanf("%d",&n);
		long long a[n+1];
		a[0] = 1;
		a[1] = 3;
		for(i=2;i<=n;i++){
			a[i]=a[i-1]*2+a[i-2];
		}
		printf("一共有%lld种走法！\n",a[n]);
	//}
	return 0;
} 
