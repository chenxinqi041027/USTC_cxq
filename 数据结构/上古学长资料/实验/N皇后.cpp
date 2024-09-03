#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#define ll long long
using namespace std;
const int maxn=20;
void Print(int N,int* sol,int& ind){
	printf("The %dnd solution\n",++ind);
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++)printf("%d ",sol[i]==j);
		puts("");
	}puts("");
}
// int cur[maxn],ind;
// void dfs(int N,int n,ll a,ll b,ll c){
// 	if(n==N)return Print(N,cur,ind);
// 	ll s=a|b|c;
// 	for(int i=0;i<N;i++)if(~s>>i&1){
// 		cur[n]=i;
// 		dfs(N,n+1,(a|1<<i)<<1,b|1<<i,(c|1<<i)>>1);
// 	}
// }
struct node{
	int n,i;
	ll a,b,c;
	node* pre;
	node():n(0),i(0),a(0),b(0),c(0),pre(NULL){}
	node(int n,int i,ll a,ll b,ll c,node* pre):n(n),i(i),a(a),b(b),c(c),pre(pre){}
	friend void recall(node*& nd);
	friend bool next(int N,node*& cur,int* queens,int& ind);
	void Print(){
		printf("n=%d i=%d (%lld,%lld,%lld) this=%p pre=%p\n",n,i,a,b,c,this,pre);
	}
};
void recall(node*& nd){
	node* tmp=nd;
	nd=nd->pre;
	free(tmp);
}
bool getnext(int N,node*& cur,int* queens,int& ind){
	int n=cur->n,&i=cur->i;
	ll a=cur->a,b=cur->b,c=cur->c;
	if(n==0&&i==N)return 0;
	if(n==N){
		Print(N,queens,ind);
		recall(cur);
		cur->i++;
	}else{
		while(i<N&&((a|b|c)>>i&1))i++;
		if(i<N){
			queens[n]=i;
			node* nxt=new node(n+1,0,(a|1<<i)<<1,b|1<<i,(c|1<<i)>>1,cur);
			cur=nxt;
		}else{
			recall(cur);
			cur->i++;
		}
	}
	return 1;
}
int main(){
	int N;
	scanf("%d",&N);
	// dfs(N,0,0,0,0);
	node *cur=new node;
	int queens[maxn],ind=0;
	while(getnext(N,cur,queens,ind));
	return 0;
}