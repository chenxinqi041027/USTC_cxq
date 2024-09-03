#include<stdio.h>
#define N 6//可以为任意数 
void paixu(int*arr,int m){
	int i,j,temp;
	for(i=0;i<m;i++){
		scanf("%d",&arr[i]);
	}
	for(i=0;i<m;i++){
		if(arr[i-1]<arr[i]){
			temp=arr[i];
			for(j=i-1;j>=0&&arr[j]<temp;j--){
				arr[j+1]=arr[j];
			}
			arr[j+1]=temp; 
		}
	}
	//for(int i=0;i<6;i++){
	//	printf("%d",arr[i]);
//}
}
int main(){
	int arr[N];
	paixu(arr,N);
	for(int i=0;i<N;i++){
		printf("%d",arr[i]);
	}
}
