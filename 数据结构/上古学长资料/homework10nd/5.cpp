#include<bits/stdc++.h>
using namespace std;
void ERROR(const string& s){
	cerr<<"ERROR!!!"<<s<<endl;
	exit(114514);
}
template<class T>class Graph{
	int vecs,arcs;
	struct Arc{
		int vec; 
		T dis;
		Arc* next;
		Arc(int vec,T dis,Arc* next):vec(vec),dis(dis),next(next){}
		~Arc(){free(next);}
	};
	Arc** head;
public:
	Graph():vecs(0),head(NULL){}
	Graph(int vecs,int arcs):vecs(vecs),arcs(arcs),head(new Arc*[vecs]){
		for(int i=0;i<vecs;i++)head[i]=NULL;
	}
	~Graph(){delete[] head;}
	int Vecs()const{return vecs;}
	int Arcs()const{return arcs;}
	void AddArc(int u,int v,const T& d){
		Arc* arc=new Arc(v,d,head[u]);
		head[u]=arc;
	}
	const void* GetNextArc(int u,const void* arc)const{
		if(u>=vecs||u<0)ERROR("Unknow vec!");
		if(!arc)return (void*)head[u];
		return ((Arc*)arc)->next;
	}
	int GetVec(const void* arc)const{
		if(!arc)ERROR("Can't get the vec from NULL!");
		return ((Arc*)arc)->vec;
	}
	T GetDis(const void* arc)const{
		if(!arc)ERROR("Can't get the dis from NULL!");
		return ((Arc*)arc)->dis;
	}
};
void dfs(const Graph<int>& G,int u,int len,int end,bool* instk){
	if(len==0&&u==end){
		puts("YES");
		exit(0);
	}
	if(len<=0||u==end)return;
	instk[u]=1;
	const void* edge=NULL;
	while(edge=G.GetNextArc(u,edge)){
		int v=G.GetVec(edge),d=G.GetDis(edge);
		if(!instk[v])dfs(G,v,len-d,end,instk);
	}instk[u]=0;
}
int main(){
	int vecs,arcs,s,t,k;
	cin>>vecs>>arcs>>s>>t>>k;
	Graph<int>G(vecs,arcs);
	int u,v,d;
	while(arcs--){
		cin>>u>>v>>d;
		G.AddArc(u,v,d);
	}
	bool* instk=new bool[vecs];
	memset(instk,0,sizeof(instk));
	dfs(G,s,k,t,instk);
	puts("NO");
	return 0;
}
/*
7 11 0 1 18
0 1 15
0 2 2
0 3 12
1 4 6
2 4 8
2 5 4
3 6 3
4 6 9
5 3 5
5 6 10
6 1 4
*/