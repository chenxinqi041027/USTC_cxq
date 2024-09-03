#include<stdio.h>
#include<malloc.h>

//结构体：定义栈的每一个结点
typedef struct Node
{
	//数据域
	int data;
	//指针域
	Node* next;
//重命名，将struct Node 重命名为Node
}Node;
/*
	求链表中的最大整数
*/
//结构体：定义链栈
typedef struct LinkList
{
	//链栈里只需要存放头结点就可以
	Node* head;
//重命名，将struct Stack 重命名为Stack
}LinkList;

int GetMax(LinkList &L){
	int m;
	if(!L->next){
		return L->data;
	}
	m=Max(L->next);
	return m>=L->data?m:L->data;
}
//函数：栈的初始化
//定义了结构体，我们首先需要一个函数来初始化链栈
//主要用途就是分配空间
//返回值自然是一个栈指针Stack*，以便我们能找到这个初始化的栈
//传参为空，因为不需要任何参数，我们直接在函数里初始化
LinkList* initialStack()
{
	//为栈分配空间
	LinkList* s = (LinkLIst*)malloc(sizeof(LinkLIst));
	//初始化头结点，将头结点指向空
	Node* ret = (Node*)malloc(sizeof(Node));
	ret->next = NULL;
	s->head = ret;
	//返回栈指针
	return s;
}
//函数：栈的插入操作
//很明显需要用头插法
//因为头插法，头结点指向的始终是栈顶元素，
//找到栈顶元素的时间复杂度为O(1),与栈的大小无关
//如果用尾插法，就麻烦了，找到栈顶元素的时间复杂度为O(N)
//或者使用双向链表，但都很麻烦
//返回值：void，因为我们是对栈进行操作，不需要返回值
//参数：传入要操作的栈的指针即可
void push(LinkList* s)
{
	//首先创建一个结点指针，并分配内存空间
	Node* cur = (Node*)malloc(sizeof(Node));
	//为其赋值
	int value;
	scanf("%d", &value);
	cur->data = value;
	//有了值还不够，因为指针域还未初始化
	//所以需要进行指针域的初始化
	//先让这个指针的next指向头结点的next
	cur->next = s->head->next;
	//再让头结点的next指向他
	s->head->next = cur;
	//这样就完成了
}
/*
	求链表的结点个数
*/
int Length(LinkList &L){
	if(!L->next){
		return 1;
	}else{
		return Length(L->next)+1;
}

/*
	求所有整数的平均值
*/
double Average(LinkList &L,int n){
	double a;
	if(!L->next){
		return L->data;
	}else{
		a=Average(L->next,n-1);
		return (a*(n-1)+L->data)/n;
	}
}
