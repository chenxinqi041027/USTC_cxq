#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,m;
int A[maxn],B[maxn];
void Read(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			scanf("%d",&A[i*m+j]);
}
bool Sort(int* A,int n){
	if(n<=1)return 0;
	int mid=n>>1;
	if(Sort(A,mid)||Sort(A+mid,n-mid))return 1;
	int i=0,j=mid,k=0;
	while(i<mid&&j<n){
		if(A[i]<A[j])B[k++]=A[i++];
		else if(A[i]>A[j])B[k++]=A[j++];
		else return 1;
	}
	while(i<mid)B[k++]=A[i++];
	while(j<n)B[k++]=A[j++];
	for(int i=0;i<n;i++)A[i]=B[i];
	return 0;
}
int main(){

}