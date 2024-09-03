#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const double eps=1e-7;
bool iszero(double x){return fabs(x)<eps;}
void ERROR(const string& s){
	cerr<<"error!! "<<s<<endl;
	exit(1);
}
template<class T>class stack{
	T* A;
	int cap,sz;
	bool full(){return sz==cap;}
public:
	stack(){
		cap=8;
		sz=0;
		A=new T[cap];
	}
	int size()const{return sz;}
	bool empty()const{return !sz;}
	void reserve(int newcap){
		if(newcap<=cap)return;
		cap=newcap;
		T* B=new T[cap<<1];
		for(int i=0;i<cap;i++)
			B[i]=A[i];
		delete[] A;
		A=B;
	}
	void push(const T& x){
		if(full())reserve(cap<<1);
		A[sz++]=x;
	}
	void pop(){
		if(empty())ERROR("The stack is empty, can't pop.");
		sz--;
	}
	T top()const{
		if(empty())ERROR("The stack is empty.");
		return A[sz-1];
	}
	~stack(){
		delete[] A;
	}
	void Print(){
		printf("stack:");
		for(int i=0;i<sz;i++)cout<<A[i]<<' ';
		puts("");
	}
};
int main(){
	enum Operators{
		Terminator=0,LeftBracket,RightBracket,Add,Subtract,Multiply,Divide,Numbers
	};
	char ops[]="#()+-*/0";
	stack<double>operands;
	char c=getchar();
	double res;
	stack<Operators>operators;
	Operators curOp;
	while(cin>>c){
		curOp=Numbers;
		switch(c){
			case '+':
				curOp=Add;
				break;
			case '-':
				curOp=Subtract;
				break;
			case '*':
				curOp=Multiply;
				break;
			case '/':
				curOp=Divide;
				break;
			case '(':
				curOp=LeftBracket;
				break;
			case ')':
				curOp=RightBracket;
				break;
			case '#':
				curOp=Terminator;
				break;
			case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '.':
				res=0;
				cin.putback(c);
				cin>>res;
				break;
			default:
				ERROR("Unknow character.");
				break;
		}
		if(curOp!=Numbers){
			if(curOp!=LeftBracket){
				while(!operators.empty()&&operators.top()>=curOp){
					double opd2=operands.top();operands.pop();
					double opd1=operands.top();operands.pop();
					Operators op=operators.top();operators.pop();
					switch(op){
						case Add:
							res=opd1+opd2;
							break;
						case Subtract:
							res=opd1-opd2;
							break;
						case Multiply:
							res=opd1*opd2;
							break;
						case Divide:
							if(iszero(opd2))ERROR("Divide by zero.");
							res=opd1/opd2;
							break;
						default:
							ERROR("Unknow operator");
					}
					operands.push(res);
				}
			}
			if(curOp==Terminator){
				if(!operators.empty())ERROR("Unmatched brackets");
				if(operands.size()!=1)ERROR("Multiple numbers");
				printf("%lf",operands.top());
				return 0;
			}
			if(curOp==RightBracket){
				if(operators.top()!=LeftBracket)ERROR("Unmatched brackets.");
				operators.pop();
			}else operators.push(curOp);
		}else operands.push(res);
	}
	return 0;
}