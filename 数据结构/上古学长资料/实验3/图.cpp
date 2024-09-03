#include<bits/stdc++.h>
using namespace std;
void ERROR(const string& s){
	cerr<<"Error!"<<s<<endl;
	exit(114514);
}
namespace STL{
	template<class T>class Stack{
		int mxsz;
		T *stk,*top_;
		void reserve(int newsz){
			int num=top_-stk;
			top_=new T[mxsz=newsz];
			for(int i=0;i<num;i++)top_[i]=stk[i];
			free(stk);
			stk=top_;
			top_=stk+num;
		}
		bool full()const{return stk+mxsz==top_;}
	public:
		Stack(int mxsz=1):mxsz(mxsz){top_=stk=new T[mxsz];}
		~Stack(){free(stk);}
		bool empty()const{return top_==stk;}
		void push(const T& elem){
			if(full())reserve(mxsz<<1);
			*(top_++)=elem;
		}
		void pop(){
			if(empty())ERROR("The stack is empty!");
			top_--;
		}
		T top()const{
			if(empty())ERROR("The stack is empty!");
			return *(top_-1);
		}
		T& top(){
			if(empty())ERROR("The stack is empty!");
			return *(top_-1);
		}
	};
	template<class T>class Queue{
		int mxsz;
		T *q,*head,*tail;
		void reserve(int newsz){
			T* newq=new T[newsz=mxsz];
			int num=tail-head;
			for(int i=0;i<num;i++)newq[i]=*(head+i);
			delete[] q;
			head=q=newq;
			tail=head+num;
		}
		bool full()const{return tail-q==mxsz;}
	public:
		Queue(int mxsz=1):mxsz(mxsz){
			tail=head=q=new T[mxsz];
		}
		~Queue(){delete[] q;}
		bool empty()const{return head==tail;}
		void push(const T& elem){
			if(full())reserve(mxsz<<1);
			*tail++=elem;
		}
		void pop(){
			if(empty())ERROR("The queue is empty!");
			head++;
		}
		T front()const{
			if(empty())ERROR("The queue is empty!");
			return *head;
		}
	};
	template<class T>class Heap{
		int mxsz,sz;
		T* h;
		bool full()const{return sz==mxsz-1;}
		void reserve(int newsz){
			T* newh=new T[mxsz=newsz];
			for(int i=1;i<=sz;i++)newh[i]=h[i];
			delete[] h;
			h=newh;
		}
		void up(){
			if(empty())ERROR("The heap is empty!");
			int p=sz;
			T key=h[p];
			while(p>>1&&h[p>>1]<key){
				h[p]=h[p>>1];
				p>>=1;
			}h[p]=key;
		}
		void down(){
			if(empty())ERROR("The heap is empty!");
			int p=1;
			T key=h[p];
			while(p<<1<=sz){
				if(p<<1|1<=sz&&key<h[p<<1|1]&&h[p<<1]<h[p<<1|1]){
					h[p]=h[p<<1|1];
					p=p<<1|1;
				}else if(key<h[p<<1]){
					h[p]=h[p<<1];
					p=p<<1;
				}else break;
			}h[p]=key;
		}
	public:
		Heap(int mxsz=1):mxsz(mxsz+1),sz(0),h(new T[mxsz+1]){}
		~Heap(){delete[] h;}
		bool empty()const{return !sz;}
		void push(const T& elem){
			if(full())reserve(mxsz-1<<1|1);
			h[++sz]=elem;
			up();
		}
		void pop(){
			if(empty())ERROR("The heap is empty!");
			h[1]=h[sz--];
			if(sz)down();
		}
		T top()const{
			if(empty())ERROR("The heap is empty!");
			return h[1];
		}
		T& top(){
			if(empty())ERROR("The heap is empty!");
			return h[1];
		}
	};
}
using namespace STL;
namespace MyGraph{
	template<class V,class A>class Graph{
	public:
		Graph(){}
		~Graph(){}
		virtual int Arcnum()const=0;
		virtual int Vecnum()const=0;
		virtual void Init(int vn=0,int an=0)=0;
		virtual void InitVec(int vn,const V* vs)=0;
		virtual void AddArc(const V& u,const V& v,const A& d)=0;
		virtual void* GetNextArc(const V& u,void*& arc)const=0;
		virtual int GetId(const V& val)const=0;
		virtual V GetVec(void* arc)const=0;
		virtual A GetArc(void* arc)const=0;
		virtual V operator [](int id)const=0;
	};
	template<class V,class A>class ListGraph:public Graph<V,A>{
		int mxvecnum,mxarcnum;
		int vecnum,arcnum;
		class Arc;
		class Vec{
		public:
			V val;
			Arc* head;
			Vec():head(NULL){}
			Vec(const V& val):val(val){}
			~Vec(){delete head;}
		}*vecs;
		class Arc{
		public:
			Vec* v;
			A d;
			Arc* next;
			Arc():v(NULL),next(NULL){}
			Arc(Vec* v,const A& d,Arc* next):v(v),d(d),next(next){}
			~Arc(){delete next;}
		};
	public:
		int Arcnum()const{return arcnum;}
		int Vecnum()const{return vecnum;}
		void Init(int vn=0,int an=0){
			mxvecnum=vecnum=vn;
			mxarcnum=arcnum=an;
			vecs=new Vec[vn];
		}
		~ListGraph(){delete[] vecs;}
		void InitVec(int vn,const V* vs){
			if(vn>mxvecnum)ERROR("Too much vecs!");
			vecnum=vn;
			for(int i=0;i<vn;i++)vecs[i].val=vs[i];
		}
		void AddArc(const V& u,const V& v,const A& d){
			Vec *uid=&vecs[GetId(u)],*vid=&vecs[GetId(v)];
			uid->head=new Arc(vid,d,uid->head);
		}
		void* GetNextArc(const V& u,void*& arc)const{
			if(!arc)return (void*)(arc=vecs[GetId(u)].head);
			return arc=((Arc*)arc)->next;
		}
		int GetId(const V& val)const{
			for(int i=0;i<vecnum;i++)if(vecs[i].val==val)return i;
			ERROR("Can't find the vec!");
		}
		V GetVec(void* arc)const{
			if(!arc)ERROR("The arc is wrong!");
			return ((Arc*)arc)->v->val;
		}
		A GetArc(void* arc)const{
			if(!arc)ERROR("The arc is wrong!");
			return ((Arc*)arc)->d;
		}
		V operator [](int id)const{
			if(id<0||id>=vecnum)ERROR("Illegal vec index!");
			return vecs[id].val;
		}
	};
	template<class V,class A>class MatrixGraph:public Graph<V,A>{
		int mxvecnum,mxarcnum;
		int vecnum,arcnum;
		V* vecs;
		A* arcs_;
		A& arcs(int uid,int vid){return arcs_[uid*vecnum+vid];}
		A arcs(int uid,int vid)const{return arcs_[uid*vecnum+vid];}
		int getuid(void* arc)const{return ((A*)arc-arcs_)/vecnum;}
		int getvid(void* arc)const{return ((A*)arc-arcs_)%vecnum;}
	public:
		int Arcnum()const{return arcnum;}
		int Vecnum()const{return vecnum;}
		void Init(int vn=0,int an=0){
			mxvecnum=vecnum=vn;
			mxarcnum=arcnum=an;
			vecs=new V[vn];
			arcs_=new A[vn*vn];
			memset(arcs_,0,sizeof(A)*vn*vn);
		}
		~MatrixGraph(){
			delete[] vecs;
			delete[] arcs_;
		}
		void InitVec(int vn,const V* vs){
			if(vn>mxvecnum)ERROR("Too much vecs!");
			vecnum=vn;
			for(int i=0;i<vn;i++)vecs[i]=vs[i];
		}
		void AddArc(const V& u,const V& v,const A& d){
			arcs(GetId(u),GetId(v))=d;
		}
		void* GetNextArc(const V& u,void*& arc)const{
			int uid=arc?getuid(arc):GetId(u),vid=arc?getvid(arc):-1;
			while(++vid<vecnum&&!arcs(uid,vid));
			return (void*)(arc=vid==vecnum?NULL:(arcs_+uid*vecnum+vid));
		}
		int GetId(const V& val)const{
			for(int i=0;i<vecnum;i++)if(vecs[i]==val)return i;
			ERROR("Can't find the vec!");
		}
		V GetVec(void* arc)const{
			if(!arc)ERROR("The arc is wrong!");
			return vecs[getvid(arc)];
		}
		A GetArc(void* arc)const{
			if(!arc)ERROR("The arc is wrong!");
			return *(A*)arc;
		}
		V operator [](int id)const{
			if(id<0||id>=vecnum)ERROR("Illegal vec index!");
			return vecs[id];
		}
	};
	template<class V,class A>void CreateGraph(Graph<V,A>& G,const string& path){
		FILE* fp=freopen(path.c_str(),"r",stdin);
		int vn,an;
		cin>>vn>>an;
		G.Init(vn,an);
		V* vs=new V[vn];
		for(int i=0;i<vn;i++)cin>>vs[i];
		G.InitVec(vn,vs);
		V u,v;A d;
		while(an--){
			cin>>u>>v>>d;
			G.AddArc(u,v,d);
			G.AddArc(v,u,d);
		}
		fclose(fp);
		fclose(stdin);
		freopen("CON","r",stdin);cin.clear();
		delete[] vs;
	}
}
template<class V,class A>void dfs(const MyGraph::Graph<V,A>& G,const V& root){
	bool* vis=new bool[G.Vecnum()];
	memset(vis,0,sizeof(bool)*G.Vecnum());
	struct Tmp{
		int uid;
		void* arc;
		Tmp():arc(NULL){}
		Tmp(int uid,void* arc=NULL):uid(uid),arc(arc){}
	};
	Stack<Tmp>stk;
	int rootid=G.GetId(root);
	stk.push(Tmp(rootid));
	vis[rootid]=1;
	puts("dfs:");
	while(!stk.empty()){
		Tmp cur=stk.top();
		int uid=stk.top().uid;
		void*& arc=stk.top().arc;
		if(G.GetNextArc(G[uid],arc)){
			int vid=G.GetId(G.GetVec(arc));
			if(!vis[vid]){
				cout<<G[uid]<<"--->"<<G[vid]<<" dis="<<G.GetArc(arc)<<endl;
				vis[vid]=1;
				stk.push(Tmp(vid));
			}
		}else stk.pop();
	}
	puts("");
	delete[] vis;
}
template<class V,class A>void bfs(const MyGraph::Graph<V,A>& G,const V& root){
	bool* vis=new bool[G.Vecnum()];
	memset(vis,0,sizeof(bool)*G.Vecnum());
	vis[G.GetId(root)]=1;
	Queue<V>q;
	q.push(root);
	puts("bfs:");
	while(!q.empty()){
		V cur=q.front();q.pop();
		void* arc=NULL;
		while(G.GetNextArc(cur,arc)){
			V v=G.GetVec(arc);
			if(!vis[G.GetId(v)]){
				cout<<cur<<"---->"<<v<<" dis="<<G.GetArc(arc)<<endl;
				vis[G.GetId(v)]=1;
				q.push(v);
			}
		}
	}
	puts("");
	delete[] vis;
}
namespace Prim{
	template<class T>T* getMinElem(T* begin,T* end,bool* acce){
		while(begin!=end&&!*acce)begin++,acce++;
		if(begin==end)return begin;
		T* res=begin;
		while(++begin!=end)if(*++acce&&*begin<*res)res=begin;
		return res;
	}
	template<class V,class A>void Prim(const MyGraph::Graph<V,A>& G){
		puts("Prim:");
		A *key=new A[G.Vecnum()+1];
		int *fa=new int[G.Vecnum()];
		bool *acce=new bool[G.Vecnum()],*vis=new bool[G.Vecnum()];
		memset(acce,1,sizeof(bool)*G.Vecnum());
		memset(vis,0,sizeof(bool)*G.Vecnum());
		A ans=0;
		key[0]=0;
		vis[0]=1;
		for(int i=0;i<G.Vecnum();i++){
			int uid=getMinElem(key,key+G.Vecnum(),acce)-key;
			acce[uid]=0;
			if(i){
				cout<<"connect "
					<<G[fa[uid]]
					<<" and "
					<<G[uid]
					<<" dis="
					<<key[uid]<<endl;
				ans+=key[uid];
			}
			void* arc=NULL;
			while(G.GetNextArc(G[uid],arc)){
				int vid=G.GetId(G.GetVec(arc));
				A w=G.GetArc(arc);
				if(!vis[vid]||w<key[vid]){
					vis[vid]=1;
					key[vid]=w;
					fa[vid]=uid;
				}
			}
		}
		cout<<"total val:"<<ans<<'\n'<<endl;
		delete[] key;
		delete[] fa;
		delete[] vis;
		delete[] acce;
	}
}
namespace Dijkstra{
	template<class V,class A>void PrintPath(const MyGraph::Graph<V,A>& G,const int* fa,int uid){
		if(uid==-1)return;
		PrintPath(G,fa,fa[uid]);
		cout<<G[uid]<<' ';
	}
	template<class V,class A>void Dijkstra(const MyGraph::Graph<V,A>& G,const V& root){
		cout<<"Shortest pathes root="<<root<<endl;
		bool* vis=new bool[G.Vecnum()];
		A* dis=new A[G.Vecnum()];
		int* fa=new int[G.Vecnum()];
		struct node{
			int uid;
			A d;
			node(){}
			node(int uid,const A& d):uid(uid),d(d){}
			bool operator <(const node& _)const{return d>_.d;}
		};
		Heap<node>h;
		memset(vis,0,sizeof(bool)*G.Vecnum());
		int rootid=G.GetId(root);
		h.push(node(rootid,dis[rootid]=0));
		fa[rootid]=-1;
		vis[rootid]=1;
		while(!h.empty()){
			node cur=h.top();h.pop();
			int uid=cur.uid;
			if(vis[uid]&&dis[uid]<cur.d)continue;
			if(dis[uid]){
				PrintPath(G,fa,uid);
				cout<<"dis="<<dis[uid]<<endl;
			}
			void* arc=NULL;
			while(G.GetNextArc(G[uid],arc)){
				int vid=G.GetId(G.GetVec(arc));
				A w=G.GetArc(arc);
				if(!vis[vid]||dis[uid]+w<dis[vid]){
					vis[vid]=1;
					dis[vid]=dis[uid]+w;
					fa[vid]=uid;
					h.push(node(vid,dis[vid]));
				}
			}
		}
		delete[] vis;
		delete[] dis;
		delete[] fa;
	}
}
int main(){
	string s="data.in";
	MyGraph::ListGraph<char,int>lG;
	MyGraph::CreateGraph(lG,s);
	MyGraph::MatrixGraph<char,int>mG;
	MyGraph::CreateGraph(mG,s);
	puts("Done Create Graph");
	
	char root;
	cin>>root;
	dfs(lG,root);
	dfs(mG,root);

	bfs(lG,root);
	bfs(mG,root);

	MyGraph::ListGraph<char,int>nG;
	MyGraph::CreateGraph(nG,"data.in");
	Prim::Prim(nG);

	Dijkstra::Dijkstra(lG,root);
	Dijkstra::Dijkstra(mG,root);
}
/*
6 10
a b c d e f
a b 5
a c 12
a d 5
b d 7
b e 8
c f 3
c b 9
e d 8
e c 16
e f 4
e
*/