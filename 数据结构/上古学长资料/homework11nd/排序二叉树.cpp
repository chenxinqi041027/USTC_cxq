#include<bits/stdc++.h>
using namespace std;
template<class T>class Tree{
public:
	T data;
	Tree *lchild,*rchild;
	Tree():lchild(NULL),rchild(NULL){}
	Tree(const T& data):data(data),lchild(NULL),rchild(NULL){}
};
template<class T>void AddData(Tree<T>*& Root,T data){
	if(!Root)Root=new Tree<T>(data);
	else{
		Tree<T>* cur=Root;
		while(1){
			if(data<cur->data){
				if(cur->lchild)cur=cur->lchild;
				else{
					cur->lchild=new Tree<T>(data);
					break;
				}
			}else{
				if(cur->rchild)cur=cur->rchild;
				else{
					cur->rchild=new Tree<T>(data);
					break;
				}
			}
		}
	}
}
template<class T>void dfs(const Tree<T>* cur,bool& flag,const T& x){
	if(!cur)return;
	if(!(cur->data<x))dfs(cur->lchild,flag,x);
	if(flag)cout<<',';
	if(flag|=!(cur->data<x))cout<<cur->data;
	dfs(cur->rchild,flag,x);
}
int main(){
	Tree<int>* T=NULL;
	int n,x;
	cin>>n;
	while(cin>>x,n--)AddData(T,x);
	bool flag=0;
	dfs(T,flag,x);
	return 0;
}
/*
12
3 4 5 7 24 30 42 54 63 72 87 95
24
*/