#include<stdio.h>
int main(){
	while(1){
	int n,i,j; 
	printf("请输入杨辉三角形行数：");
	scanf("%d",&n);
	printf("%d阶杨辉三角形\n",n);
	int dp[n-1][n-1];
	dp[0][0]=dp[1][0]=dp[1][1]=1;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			dp[i][j]=1;
		}
	}
	for(i=1;i<n;i++){
		for(j=1;j<i;j++){
			dp[i][j]=dp[i-1][j-1]+dp[i-1][j];
			//printf("%d  ",dp[i][j]);
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<=i;j++){
			printf("%d  ",dp[i][j]);
		}
		printf("\n");
	}
	}
	return 0;
} 
