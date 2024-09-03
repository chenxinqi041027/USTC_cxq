#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,m,V;
struct Arc{
	int v;
	Arc* nxt;
	Arc():nxt(NULL){}
	Arc(int v):v(v),nxt(NULL){}
};
Arc *head[maxn],*tail[maxn],*curr[maxn];
void AddArc(int u,int v){
	Arc* tmp=new Arc(v);
	tail[u]->nxt=tmp;
	tail[u]=tmp;
	printf("tail %d =%d %p\n",u,v,tail[u]);
}
int stk[maxn],top;
bool vis[maxn];
int main(){
	cin>>n>>m>>V;
	int u,v;
	for(int i=1;i<=n;i++)head[i]=tail[i]=new Arc;
	for(int i=0;i<m;i++){
		cin>>u>>v;
		AddArc(u,v);
		AddArc(v,u);
	}
	vis[stk[top=1]=V]=1;
	curr[V]=head[V];
	while(top){
		int u=stk[top];
		if(curr[u]=curr[u]->nxt){
			int v=curr[u]->v;
			if(!vis[v]){
				vis[stk[++top]=v]=1;
				curr[v]=head[v];
				printf("%d->%d\n",u,v);
			}
		}else top--;
	}return 0;
}