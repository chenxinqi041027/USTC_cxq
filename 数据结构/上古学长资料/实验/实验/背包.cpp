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
void dfs(int T,int n,FILE* ofp){
	if(!n--){
		if(!T){
			for(int i=0;i<N;i++)if(take[i])
				fprintf(ofp,"%d ",W[i]);
			fprintf(ofp,"\n");
		}return;
	}
	if(T>=W[n]){
		take[n]=1;
		dfs(T-W[n],n,ofp);
		take[n]=0;
	}
	dfs(T,n,ofp);
}
int main(int argc,char* argv[]){
	FILE* ifp=fopen(argv[1],"r");
	FILE* ofp=fopen("result_dp.out","w");
	char ops[]="#()+-*/0";
	fscanf(ifp,"%d",&T);
	for(int i=0;~fscanf(ifp,"%d",&W[i]);i++);
	dfs(T,N,ofp);
	return 0;
}
