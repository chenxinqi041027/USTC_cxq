#include<bits/stdc++.h>
using namespace std;
void ERROR(const string& s){
	cerr<<"Error!!!"<<s<<endl;
	exit(114514);
}
class iszero_{
	double eps=1e-7;
public:
	bool operator ()(const double& x)const{
		return fabs(x)<eps;
	}
}iszero;
class Superior_{
	const char operators[7]="+-*/()";
public:
	bool operator ()(char x,char y)const{
		int a,b;
		for(a=0;a<6&&operators[a]!=x;a++);
		for(b=0;b<6&&operators[b]!=y;b++);
		return (a>>1)<(b>>1);
	}
	int operator [](char x)const{
		int a;
		for(a=0;a<6&&operators[a]!=x;a++);
		return a;
	}
}Superior;
template<class T>class Queue{
	int mxsz;
	T *q,*head,*tail;
	bool full()const{return q+mxsz==tail;}
	void resize(int newsz){
		mxsz=newsz;
		T* newq=new T[mxsz];
		int num=tail-head;
		head=newq+num;
		while(num)newq[--num]=*(--tail);
		free(q);
		tail=head;
		q=head=newq;
	}
public:
	Queue(int sz=1){
		mxsz=sz;
		q=new T[mxsz];
		head=tail=q;
	}
	~Queue(){free(q);}
	bool empty(){return head==tail;}
	T& front(){
		if(empty())ERROR("The Queue is empty!");
		return *head;
	}
	T front()const{
		if(empty())ERROR("The Queue is empty!");
		return *head;
	}
	void pop(){
		if(empty())ERROR("The Queue is empty!");
		head++;
	}
	void push(const T& elem){
		if(full())resize(mxsz<<1);
		*(tail++)=elem;
	}
};
template<class T>class Stack{
	int mxsz;
	T *stk,*tp;
	bool full()const{return stk+mxsz==tp;}
	void resize(int newsz){
		mxsz=newsz;
		T* newstk=new T[mxsz];
		int num=tp-stk;
		for(int i=0;i<num;i++)newstk[i]=stk[i];
		free(stk);
		stk=newstk;
		tp=stk+num;
	}
public:
	Stack(int sz=1){
		mxsz=sz;
		tp=stk=new T[mxsz];
	}
	~Stack(){free(stk);}
	bool empty(){return tp==stk;}
	T& top(){
		if(empty())ERROR("The Stack is empty!");
		return *(tp-1);
	}
	T top()const{
		if(empty())ERROR("The Stack is empty!");
		return *(tp-1);
	}
	void pop(){
		if(empty())ERROR("The Stack is empty!");
		tp--;
	}
	void push(const T& elem){
		if(full())resize(mxsz<<1);
		*(tp++)=elem;
	}
};
class ndType{
	string s;
	double val;
public:
	ndType():s("Empty"),val(0){}
	ndType(const string& s):s(s),val(0){}
	ndType(const double& val):s("0"),val(val){}
	ndType(const string& s,double val):s(s),val(val){}
	bool empty()const{return s=="Empty";}
	friend bool ReadStr(string& s);
	bool ReadStr(){
		char c;
		s="";
		while((c=getchar())!=','&&c!='\n')s+=c;
		return s!=""&&!empty();
	}
	friend ostream& operator <<(ostream& os,const ndType& _);
	ndType operator +(const ndType& _)const{
		return ndType("+",val+_.val);
	}
	ndType operator -(const ndType& _)const{
		return ndType("-",val-_.val);
	}
	ndType operator *(const ndType& _)const{
		return ndType("*",val*_.val);
	}
	ndType operator /(const ndType& _)const{
		if(iszero(_.val))ERROR("Divided by zero!");
		return ndType("/",val/_.val);
	}
	void PrintVal()const{cout<<"val="<<val<<endl;}
};
ostream& operator <<(ostream& os,const ndType& _){
	if(_.s=="0")return os<<_.val;
	return os<<_.s;
}
class Tree{
	ndType val;
public:
	Tree *lson,*rson;
	bool ltag,rtag;
	Tree():lson(NULL),rson(NULL),ltag(false),rtag(false){}
	Tree(const ndType& val):val(val),lson(NULL),rson(NULL),ltag(false),rtag(false){}
	// ~Tree(){
	// 	if(!ltag&&lson)delete lson;
	// 	if(!rtag&&rson)delete rson;
	// }
	bool empty()const{return val.empty();}
	bool ReadStr(){return val.ReadStr();}
	friend ostream& operator <<(ostream& os,const Tree& _);
	void PostOrderTraversal(Queue<Tree*>& q){
		if(lson)lson->PostOrderTraversal(q);
		if(rson)rson->PostOrderTraversal(q);
		q.push(this);
	}
	void LinkLeft(Tree* pre){
		if(!lson&&pre){
			ltag=1;
			lson=pre;
		}
	}
	void LinkRight(Tree* nxt){
		if(!rson&&nxt){
			rtag=1;
			rson=nxt;
		}
	}
	void Divide(string s,int* jump){
		int mid=0;
		for(int i=0;i<(int)s.length();i+=jump[i])
			if(!Superior(s[mid],s[i]))mid=i;
		char op=s[mid];
		double v;
		istringstream is;
		switch(op){
			case '+':case '-':case '*':case '/':
				(lson=new Tree)->Divide(s.substr(0,mid),jump);
				(rson=new Tree)->Divide(s.substr(mid+1),jump+mid+1);
				switch(op){
					case '+':val=lson->val+rson->val;break;
					case '-':val=lson->val-rson->val;break;
					case '*':val=lson->val*rson->val;break;
					case '/':val=lson->val/rson->val;break;
				}
				break;
			case '(':Divide(s.substr(1,s.length()-2),jump+1);break;
			case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '.':
				is=istringstream(s);
				if(is>>v)val=ndType(v);
				else ERROR("Unknow character!");
				break;
			default:
				ERROR("Unknow character!");break;
		}
	}
	void PrintVal()const{val.PrintVal();}
};
ostream& operator <<(ostream& os,const Tree& _){return os<<_.val;}
void Read_I(Tree& T){
	cout<<"Start Read"<<endl;
	Queue<Tree*>q;
	if(!T.ReadStr())ERROR("The Tree is empty!");
	q.push(&T);
	ndType val;
	Tree* cur;
	while(!q.empty()){
		cur=q.front();q.pop();
		if(val.ReadStr())
			q.push(cur->lson=new Tree(val));
		if(val.ReadStr())
			q.push(cur->rson=new Tree(val));
	}
	cout<<"Done Read\n"<<endl;
}
void LevelOrderTraversal(const Tree& T){
	cout<<"Start LevelOrderTraversal"<<endl;
	Queue<const Tree*>q;
	q.push(&T);
	const Tree *empNode=new Tree(ndType("Empty")),*cur;
	while(!q.empty()){
		cur=q.front();q.pop();
		if(cur!=&T)cout<<',';
		cout<<*cur;
		if(!cur->empty()){
			q.push(cur->lson?cur->lson:empNode);
			q.push(cur->rson?cur->rson:empNode);
		}
	}
	cout<<"\nDone LevelOrderTraversal\n"<<endl;
}
void PostThread(Tree& T){
	cout<<"Start PostThread"<<endl;
	Queue<Tree*>q;
	T.PostOrderTraversal(q);
	Tree *pre=NULL,*cur;
	while(!q.empty()){
		cur=q.front();q.pop();
		if(pre)pre->LinkRight(cur);
		cur->LinkLeft(pre);
		pre=cur;
	}
	cout<<"Done PostThread\n"<<endl;
}
void PostThreadTraversal(Tree T){
	Tree* cur=&T;
	cout<<"Start PostThreadTraversal"<<endl;
	Stack<Tree*>stk;
	do{
		stk.push(cur);
		if(cur->ltag)cur=cur->lson;
		else if(!cur->lson)cur=NULL;
		else if(!cur->rtag&&cur->rson)cur=cur->rson;
		else cur=cur->lson;
	}while(cur);
	while(!stk.empty()){
		if(cur)cout<<',';
		cur=stk.top();stk.pop();
		cout<<*cur;
	}
	cout<<"\nDone PostThreadTraversal\n"<<endl;
}
void Expression(Tree& T){
	cout<<"Start Read Expression"<<endl;
	string s;
	cin>>s;
	int len=s.length();
	int* jump=new int[len];
	Stack<int>stk(len);
	for(int i=0;i<len;i++){
		jump[i]=1;
		if(s[i]=='(')stk.push(i);
		else if(s[i]==')'){
			if(stk.empty())ERROR("Unmatched brackets!");
			int lid=stk.top();stk.pop();
			jump[lid]=i-lid+1;
		}
	}
	if(!stk.empty())ERROR("Unmatched brackets!");
	T.Divide(s,jump);
	cout<<"Done Calc Expression\n"<<endl;
}
int main(){
	Tree T;
	Read_I(T);
	LevelOrderTraversal(T);
	PostThread(T);
	PostThreadTraversal(T);
	Tree exp;
	Expression(exp);
	LevelOrderTraversal(exp);
	exp.PrintVal();
	return 0;
}
/*
A,B,C,Empty,D,E,F,G,Empty,Empty,H,Empty,Empty,Empty,Empty,Empty,Empty
1+2*(3/2+4)
*/