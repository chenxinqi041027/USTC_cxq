# ch2线性表
> 这章涉及链表和线性表，记住一些相关操作~

线性表：用数据元素的有序序列表示。

起点，终点，直接前驱，直接后继



## **顺序存储结构**

> 用一组地址连续的存储单元依次存储线性表的元素，可通过数组V[n]来实现。

$$Loc(元素i)=Lo+（i-1)*m$$

**类型定义**

```cpp
#define MAXSIZE 100//最大长度
typedef struct{
    ElemType *elem;
    int length;
}SqList;
```

**例：图书表的顺序存储结构类型定义**

```cpp
#define MAXSIZE 10000
typedef struct{
    char no[20];
    char name[50];
    float price;
}Book;
typedef struct{
    Book *elem;
    int length;
}SqList;
```

**动态内存分配**

（<stdlib.h>）

```cpp
malloc(m)//开辟m字节长度的地址空间，并返回首地址
sizeof(x)//计算x长度
free(p)//释放指针p所指的变量的存储空间，删完之后要将p指针赋空
```



## **传值方式**

+ #### 传值：形参，只传数据进去，实参的值不变

+ #### 传址：形参变化影响实参

例：

**形参变化影响实参**

```cpp
void swap(float *m,float *n){
float t;
t = *m;
*m = *n;
*n = t;
}//交换了指针指向的数据的值
void main(){
float a,b,*p1,*p2;
cin>>a>>b;
p1 = &a,p2 = &b;
swap(p1,p2);
}
```

**形参变化不影响实参**

```cpp
void swap(float *m,float *n){
float *t;
t = m;
m = n;
n = t;
}//只是在函数中改变了地址的值，没有对地址对应的值进行交换
void main(){
float a,b,*p1,*p2;
cin>>a>>b;
p1 = &a,p2 = &b;
swap(p1,p2);
}
```

##  传地址方式

+ **引用类型作参数**

```cpp
void swap(float &m,float &n){
float temp;
temp = m;
m = n;
n = temp;
}
void main(){
float a,b;
cin>>a>>b;
swap(a,b);
cout<<a<<endl<<b<<endl;
}
```

+ **数组名作参数**

```cpp
//传递数组首地址
void sub(char)
void main(void){
    char a[10] = "hello";
    sub(a);
    cout<<a<<endl;
}
void sub(char b[]){
    b[] = "world";
}
```

+ **练习**

> 用数组作函数的参数，求10个整数的最大数

```cpp
int max(int b[]){
	int i,n;
	n = b[0]
	for(i = 0; i < N; i++){
	if(b[i]>n) n = b[i];
	}
	return n;
}
```

> 用数组作为函数的参数，将数组中n个整数按相反的顺序存放，要求输入和输出在主函数中完成

```cpp
void sub(int b[]){
	int i,j,temp,m;
	m = N/2;
	for(i = 0;i<m;i++){
	j = N-1-i;
	temp = b[i];
	b[i] = b[j];
	b[j] = temp;
	}
	return 0;
}
void main(){
	int a[10],i;
	for(i = 0; i<N;i++){
	cin >> a[i];
}
	sub(a);
	for(i = 0;i<N;i++){
	cout << a[i];
	}
}
```

##  线性表基本操作

1. 初始化线性表（传地址）

```cpp
Status InitList_Sq(SqList &L){
    L.elem = new ElemType[MAXSIZE];//分配空间
    if(!L.elem) exit(OVERFLOW);//判断是否失败
    L.length = 0;
    return OK;
}
```

2. 初始化线性表（传指针）

```cpp
Status InitList_Sq(SqList *L){
    L->elem = new ElemType[MAXSIZE];//分配空间
    if(!L->elem) exit(OVERFLOW);//判断是否失败
    L->length = 0;
    return OK;
}
```

3. 销毁线性表L

```cpp
void DestoryList(SqList &L){
	if(L.elem) delete[]L.elem;//释放空间
}
```

4. 清空线性表L

```cpp
void ClearList(SqList &L){
	L.length = 0;
}
```

5. 求线性表长度

```cpp
int GetLength(SqList L){
	return (L.length);
}
```

6. 判断线性表是否为空

```
int IsEmpty(SqList L){
if(L.length == 0) return 1;
else return 0;
}
```

7. 获取线性表中的某个元素的值

（**随机存取法**）

```cpp
int GetElem(SqList L,int i,ElemType &e){
	if(i<1 || i>L.length) return ERROR;
	e = L.elem[i-1];
	return OK;
}
```

8. 查找元素

```cpp
int LocateElem(SqList L,ElemType e){
	for(int i = 0; i < L.length; i++){
	if(L.elem[i] == e) return i+1;
	}
	return 0;
}
```

9. 插入元素（插入第i个结点之前，移动n-i-1次）

```cpp
Status ListInsert_Sq(SqList &L,int i,ElemeType e){
	if(i<1 || i>L.Length +1) return ERROR;
	if(L.length == MAXSIZE) retrun ERROR;
	for(int j = L.length-1;j>i;j++){
		L.elem[j+1] = L.elem[j];
	}
	L.elem[i-1] = e;
	L.length++;
}
```

> 算法分析：
>
> ​	算法时间耗费在移动元素操作上
>
> 平均移动次数$ AMN=\frac{\sum\limits_{i=1}^{n+1}(n-i+1)}{n+1}=\frac{1}{n+1} \frac{n(n+1)}{2} = \frac{n}{2}$

10. 删除第i个结点（删除第i个结点，移动n-i次）

```
Status ListDelete_Sq(SqList &L,inti){
	if(i<1 || i>L.length) return ERROR;
	for(j = i;j<L.length;j++){
		L.elem[j--1] = L.elem[j];
	}
	--L.length;
	return OK;
}
```

> 算法分析：
>
> ​	算法时间耗费在移动元素操作上
>
> $ AMN=\frac{\sum\limits_{i=1}^{n}(n-i)}{n}=\frac{1}{n} \frac{n(n-1)}{2} = \frac{n-1}{2}$



## **链式存储结构**

> 解决顺序存储存储空间分配不灵活，运算空间复杂度高的问题

>  线性表的链式表示又称为==非顺序映像==或==链式映像==

>  结点由==数据域==和==指针域==构成。

+ 头指针：指向链表中第一个结点的指针
+ 首元结点：指向链表中存储第一个数据元素a1的结点
+ 头结点：在链表的首元结点之前附设一个结点；数据域内只放空表标志和表长信息

**放图**

**有头结点**，**无头结点如图**

问题：

+ 如何表示空表：有头结点时，头结点指针域为空时表示空表。

+ 头结点的好处：1.便于首元结点的处理；2.便于空表和非空表的统一处理
+ 头结点的数据域内装什么：空/线性表长度（**头结点不计入链表长度**）



### 单链表

> 结点只有一个指针与域的链表——单链表

> 由表头唯一确定，单链表用头指针的名字命名

1. 存储结构定义

```cpp
typedef struct LNode{
	Elemtype data;//数据域
	struct LNOde *next;//指针域
}LNode,*LinkList;
//*LinkList是LNode类型的指针
//LNode *p 等价于LinkList p
```

2. 初始化

```cpp
Status InitList_L(LinkList &L){
	L = new LNode;
	L->next = NULL;
	return OK;
}
```

3. 销毁

```cpp
Status DestoryList_L(LinlList &L){
	LinkList p;
	while(L){
		p = L;
		L = L->next;
		delete p;
	}
	return OK;
}
```

4. 清空

```cpp
Status ClearList(LinkList &L){
	LinkList p,q;
	p = L->next;
	while (p){
		q = p->next;
		delete p;
		p = q;
	}
	L->next = NULL;//头结点指针域为空
	return OK;
}
```

5. 求表长

```cpp
Status Length(LinkList L){
	LinkList p;
	p = L->next;
	int i = 0;
	while(p){
		i++;
		p = p->next;
	}
	return i;
}
```

6. 判空

```cpp
int ListEmpty(LinkList L){
	if(L->next) return 0;
	else return 1;
}
```

7. 获取线性表中某个元素的内容

```cpp
Status GetElem_L(LinkList L,int i,ElemType &e){
	LinkList p = L-> next;
	int j = 1;
	while(p && j<i){
		p = p->next;
		j ++;
	}
	if(!p || j>i) return ERROR;//未找到
	e = p->data;
	return OK;
}
```

8. 查找

```cpp
LNode *LocateElem_L(LinkList L,ElemType e){
	LinkList p = L->next;
	while(p && p->data != e)
	p = p->next;
	retrurn p;
}//返回L中值为e的元素的地址
```

```cpp
int LocateElem_L(LinkList L,ElemType e){
	LinkList p = L->next;
	int j = 1;
	while(p && p->data != e){
		p = p->next;
		j++;
	}
	if(p) return j;
	else return 0;
}//返回值为数据元素的序号
```

9. 插入

==补图==

```cpp
Status LinkInsert_L(LinkList &L,int i,ElemType e){
	p = L;
	j = 0;
	while(!p || j<i-1){
		p = p->next;
		j++;
	}
	if(!p || j < i-1) return ERROR;
	s = new LNode;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}
```

10. 删除

==补图==

```cpp
Status ListDelete_L(LinkList &L,int i,ElemType &e){
	LinkList p = L;
	int j = 0;
	while (p->next && j<i-1){//第i个结点，并且p是其前驱
		p = p->next;
		j++;
	}
	if(!(p->next) || j > i-1) return ERROR;
	q = p->next;
	p->next = q->next;
	e = q->data;
	delete q;
	return OK;
}
```

> 算法分析：
>
> 查找：时间复杂度为O(n)
>
> 插入和删除：时间复杂度为O(1)

11. 前插法创建单链表（将新结点插入链表前端）

```cpp
void CreateList_F(LinkList &L,int n){
	L = new LNode;
	L->next = NULL;//创建头结点
	for(int i = 0; i<n;i++){
		p = new LNode;
		cin >> p->data;
		p->next = L->next;
		L->next = p;
	}
}
```

12. 尾插法创建单链表（将新结点逐个插入到链表的尾部）

```cpp
void CreateList_L(LinkList &L,int n){
	L = new LNode;
	L->next = NULL;
	r = L;
	for(int i = 0;i < n;i++){
		p = new LNode;
		cin >> p->data;
		p->next = NULL;
		r->next = p;
		r = p;
	}
}
```



### 循环链表

> 首尾相接的链表——循环链表

==补图==

```cpp
L->next = L
```

+ 循环链表中任何一个结点的位置都可以找到其他结点，单链表不行
+ ==循环条件（避免死循环）==

```cpp
p != NULL ->p! = L 
p->next != NULL -> p->next != L
```

+ 循环链表有时候不给出头指针，而给出尾指针更方便找到第一个和最后一个

```cpp
开始：rear->next->next
终端：rear
```

1. 循环链表的合并

==补图==

```cpp
LinkList Connect(LinkList Ta,LinkList Tb){//Ta、Tb都是尾结点
	LinkList p = Ta->next;//p存储表头
	Ta->next = Tb->next->next//Tb表头连接Ta表尾
	delete Tb->next;
	Tb->next = p;
	return Tb;
}
```



### 双链表

> 结点有俩个指针域的链表——双链表

1. 数据结点

==补图==

```cpp
typedef struct DuLNode{
	ElemType data;
	struct DuLNode *prior;
	struct DuLNode *next;
}DuLNode, *DuLinkList;
```

**双向循环链表的特点**

```cpp
d->next->prior = d->prior->next = d;
```

2. 双向链表的插入

==补图==

```cpp
Status ListInsert_DuL(DuLinkList &L,int i,ElemType e){
	if(!(p = GetElemP_DuL(L,i))) return ERROR;
	s = new DuLNode;
	s->data = e;
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;
	return OK;
}
```

3. 双向链表的删除

```cpp
Status ListDelete_DuL(DuLinkList &L,int i, ElemTypr e){
	if(!(p = GetElemP_DuL(L,i))) return ERROR;
	e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	delete p;
	return OK;
}
```

==补图，ppt124页==







### 问题应用

+ #### **合并问题**

> 假设利用两个线性表La和Lb分别表示两个集合A和B,现要求一个新的集合

依次取出Lb中的每个元素，在La中查找如果找不到则插入la的最后，如果有则继续向后遍历

```cpp
void union(List &La,List &Lb){
	La_len = ListLength(La);
	Lb_len = ListLength(Lb);
	for(i = 1;i<= Lb_len;i++){
	GetElem(Lb,i,e);
	if(!LocateElem(La,e))
		ListInsert(&La,++La_len,e);
	}
}//O(ListLength(LA))*O(ListLength(LB))
```

+ #### 有序表合并

> 非递减排序，要求归并成一个新的线性表Lc，要求仍非递减排序

创建，依次摘取元素值较小的元素插入到Lc最后，直至其中一个表变空

```cpp
void MergeList_Sq(SqList LA,SqList Lb,SqList Lc){
	pa = LA.elem;
	pb = LB.elem;
	LC.length = LA.length +LB.length;
	LC.elem = new ElemType[LC.length];
	pc = LC.elem;
	pa_last = LA.elem + LA.length +1;//尾指针
	pb_last = Lb.elem + LB.length +1;//尾指针
	while(pa<=pa_last && pb<=pb_last){
		if(*pa<=*pb){
			*pc++ = *pa++;
		}else *pc++ = *pb++;
	}
	while(pa<=pa_last) *pc++ = *pa++;//LB表先到达表尾
	while(pb<=pb_last) *pc++ = *pb++;//LA表先到达表尾
}
```

$$T(n) = O(ListLength(LA))+ListLength(LB)$$

$$S(n)=O(n)$$

==见ppt135页后的步骤==

>  **仍然使用原来两个链表的存储空间，不额外占用空间**

```cpp
void MergeList_L(LinkList &La,LinkList &Lb,LinkList &Lc){
	pa = La->next;
	pb = Lb->next;
	pc = Lc = La;
	while(pa && pb){
		if(pa->data <= pb->data){
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		} else{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa?pa:pb;
	delete Lb;
}
```

$$T(n)=O(ListLength(LA))+ListLength(LB)$$

$$S(n)=O(1)$$

> 若不能有重复数据要单独考虑相等的情况

+ #### 多项式

  + 创建

  ==补图==

  ```cpp
  void CreatePolyn(Polynomial &P,int n){
  	Polynomial P = new PNode;
  	P->next = NULL;
  	for(int i = 1;i<n;i++){
  		s = new PNode;
  		cin>>s->coef>>s->expn;//系数和指数
  		pre = P;//前驱
  		q = p->next;
  		while(q && q->expn<s->expn){
  			pre = q;
  			q = q->next;
  		}
  		s->next = q;
  		pre->next = s;
  	}
  }
  ```

  + 相加

  ==补图==

  









