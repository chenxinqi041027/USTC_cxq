#include<stdio.h>
#include<math.h>
#define Max  20
#define N   3
int minor(int a[Max][Max],int i,int n);
int det(int arr[Max][Max],int n){
	int sum=0,i,M;
	if(n==1) return arr[0][0];
	else{
		for(i=0;i<n;i++){
			M=minor(arr,i,n);
			sum+=(pow(-1,i+2))*M*arr[0][i];//第一行展开 
		}
	}
	return sum;
}
int minor(int arr1[Max][Max],int i,int n){
	int  j, k,result;
	int arr2[Max][Max];
		for (j = 0; j < n - 1; j++)
		{
			for (k = 0; k < n - 1; k++)
			{
				if (k < i)
					arr2[j][k] = arr1[j + 1][k];
				else if (k >= i)
					arr2[j][k] = arr1[j + 1][k + 1];
			}
		}	
	return det(arr2, n - 1);
}
int main(){
	int a[Max][Max]={{1,10,2},{0,2,1},{0,0,3}};
	int b[Max][Max]={{1,2,3},{4,5,6},{7,8,9}};
	printf("%d\n",det(a,N));
	printf("%d",det(b,N));
	return 0;
	
} 
