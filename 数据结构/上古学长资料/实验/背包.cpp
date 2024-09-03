#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxT=1e4;
const int maxN=1e3;
int T,N;
int W[maxN];
bool take[maxN];
void dfs(int T,int n){
	if(!n--){
		if(!T){
			for(int i=0;i<N;i++)if(take[i])
				printf("%d ",W[i]);
			puts("");
		}return;
	}
	if(T>=W[n]){
		take[n]=1;
		dfs(T-W[n],n);
		take[n]=0;
	}
	dfs(T,n);
}
int main(){
	scanf("%d%d",&T,&N);
	for(int i=0;i<N;i++)scanf("%d",&W[i]);
	dfs(T,N);
	return 0;
}