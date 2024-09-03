#include<bits/stdc++.h>
using namespace std;
template<class T>struct Node{
	T val;
	Node<T>* next;
};
template<class T>struct List{
	Node<T>* head;
};
//含头节点
template<class T>void initList(List<T>& list){
	list.head=new Node<T>;
	list.head->next=NULL;
}
template<class T>void addElement(List<T>& list,const T& val){
	if(!list.head)initList(list);
	Node<T>* cur=list.head;
	while(cur->next)cur=cur->next;
	cur->next=new Node<T>;
	cur=cur->next;
	cur->val=val;
	cur->next=NULL;
}
template<class T>void Reverse(const List<T>& list){
	if(!list.head||!list.head->next)return;
	Node<T>* first=list.head->next;
	for(Node<T> *cur=list.head->next,*nxt;cur;cur=nxt){
		nxt=cur->next;
		cur->next=list.head->next;
		list.head->next=cur;
	}
	first->next=NULL;
}
template<class T>void findMaxNode(const List<T>& list,Node<T>*& MaxNode){
	if(!list.head||!list.head->next)return MaxNode=NULL,void();
	MaxNode=list.head->next;
	for(Node<T>* cur=list.head->next;cur;cur=cur->next)
		if(MaxNode->val<cur->val)
			MaxNode=cur;
}
template<class T>void Merge(List<T>& A,List<T>& B,List<T>& C){
	if(!A.head||!B.head)return C.head=max(A.head,B.head),void();
	if(!C.head)initList(C);
	Node<T>* cur=C.head;
	Node<T> *curA=A.head->next,*curB=B.head->next;
	while(curA&&curB){
		if(curA->val<curB->val){
			cur->next=curA;
			curA=curA->next;
		}else{
			cur->next=curB;
			curB=curB->next;
		}
		cur=cur->next;
	}
	cur->next=max(curA,curB);
}
template<class T>void invertedMerge(List<T>& A,List<T>& B,List<T>& C){
	Merge(A,B,C);
	Reverse(C);
}
template<class T>void Print(const List<T>& A,const string& s=""){
	cout<<s<<':';
	for(Node<T>* cur=A.head;cur->next;cur=cur->next)
		cout<<cur->next->val<<' ';
	puts("");
}
int main(){
	srand(time(NULL));
	int n=4;
	List<int>A,B,C;
	initList(A);
	initList(B);
	initList(C);
	for(int i=1;i<=n;i++)addElement(A,i<<2|(rand()%4));
	for(int i=1;i<=n;i++)addElement(B,i<<2|(rand()%4));
	Print(A,"A");
	Print(B,"B");
	Node<int>* maxNode;
	findMaxNode(A,maxNode);
	cout<<"A:maxNode val="<<maxNode->val<<endl;
	invertedMerge(A,B,C);
	Print(C,"inverted merge");
	Reverse(C);
	Print(C,"reverse C");
	return 0;
}