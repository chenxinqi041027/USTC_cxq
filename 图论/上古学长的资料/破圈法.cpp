#include<bits/stdc++.h>
#define ll long long
#define EOR(u,v) for(int u##_=head[u],v=edge[u##_].v;u##_;v=edge[u##_=edge[u##_].to].v)
using namespace std;
const int maxn=1e4+5;
const int maxm=2e5+5;
int n,m;
struct node{
	int v,w,to;
	bool operator <(const node &_)const{
		return w<_.w;
	}
}edge[maxm<<1];
int tot,head[maxn];
void Add(int u,int v,int w){
	edge[tot]=(node){v,w,head[u]};
	head[u]=tot++;
}
bool vis[maxn],exi[maxm];
int stk[maxn],top;
bool dfs(int u,int f,ll& ans){
	// printf("dfs %d %d %lld\n",u,f,ans);
	vis[u]=1;
	EOR(u,v)if(v!=f&&exi[u_]){
		stk[++top]=u_;
		if(vis[v]){
			int mxid=u_;
			printf("find circle %d->%d %d\n",v,u,edge[u_].w);
			while(--top&&edge[stk[top]].v!=v){
				printf("find circle %d->%d %d\n",edge[stk[top]^1].v,edge[stk[top]].v,edge[stk[top]].w);
				if(edge[mxid]<edge[stk[top]])
					mxid=stk[top];
				top--;
			}
			ans-=edge[mxid].w;
			exi[mxid]=exi[mxid^1]=0;
			printf("delete %d-%d %d\n",edge[mxid].v,edge[mxid^1].v,edge[mxid].w);
			top=0;
			vis[u]=0;
			return 1;
		}
		if(dfs(v,u,ans)){
			vis[u]=0;
			return 1;
		}
		top--;
	}vis[u]=0;
	return 0;
}
int main(){
	memset(vis,0,sizeof(vis));
	memset(head,-1,sizeof(head));
	memset(exi,1,sizeof(exi));
	tot=0;
	scanf("%d%d",&n,&m);
	int u,v,w;
	ll ans=0;
	while(m--){
		scanf("%d%d%d",&u,&v,&w);
		Add(u,v,w);
		Add(v,u,w);
		printf("%c((%d))--%d--%c((%d))\n",u+'A'-1,u,w,v+'A'-1,v);
		ans+=w;
	}
	while(dfs(1,0,ans));
	printf("%lld",ans);
}