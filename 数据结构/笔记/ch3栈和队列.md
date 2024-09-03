# ch3栈和队列

> 这章涉及栈和队列，记住一些相关操作~

## 栈

> 只能在表的一端进行插入和删除运算的线性表
>
> 可用顺序栈或者链栈存储
>
> 运算规则：后进先出，先进后出

顺序栈顺序表区别==补图==



**top指针指示真正的栈顶元素之上的下标地址**

1. 表示

```cpp
# define MAXSIZE 100
typedef struct{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;
```

2. 初始化

```cpp
Status InitStack(SqStack &S){
	S.base = new SElemType[MAXSIZE];
	if(!S.base) return OVERFOLW;
	S.top = S.base;
	S.stackSize = MAXSIZE;
	return OK;
}
```

3. 判空

```cpp
bool StackEmpty(SqStack S){
	if(S.top = S.base) return true;
	else return false;
}
```

3. 求长度

```cpp
int StackLength(SqStack S){
	return S.top - S.base;
}
```

4. 清空顺序栈

```cpp
Status ClesarStack(SqStack S){
	if(S.base) S.top = S.base;
	return Ok;
}
```

5. 销毁顺序栈

```cpp
Status DestoryStack(SqStack &S){
	if(S.base){
	delete S.base;
	S.stacksize = 0;
	S.base = S.top = NULL;
	}
	return OK;
}
```

6. 顺序栈进栈

```cpp
Status Push(SqStack &S,SElemType e){
	if(S.top - S.base == S.stacksize)//栈满 return ERROR;
	*S.top++ = e;//相当于S.top = e,S.top++
	return OK;
}
```

7. 顺序栈出栈

```cpp
Status Pop(SqStack &S,SElemType e){
	if(S.top == S.base)//栈空 return ERROR;
	e = *--S.top;//相当于S.top--,e = *S.top
	return OK;
}
```

8. 获取栈顶指针

```cpp
Status GetTop(SqStack S,SElemType &e){
	if(S.top == S.base) return ERROR;
	e = *(S.top-1);
	return OK;
}
```

#### 链栈

> 运算受限的单链表，只能在链表头进行操作，栈顶指针就是链表的头指针

```cpp
typedef struct StackNode{
	SElemType data;
	struct StackNode *next;
}StackNode, *LinkStack;
LinkStack S;
```

1. 初始化

```cpp
void InitStac(LinkStack &S){
	S = NULL;
}
```

2. 判空

```cpp
Status StackEmpty(LinkStack S){
	if(S==NULL) return TRUE;
	else return FALSE;
}
```

3. 进栈

```cpp
Status Push(LinkStack &S,SElemTyep e){
	p = new StackNode;
	if(!p) exit(OVERFLOW);
	p->data = e;
	p->next = S;
	S = p;
	return OK;
}
```

4. 出栈

```cpp
Status Pop(LinkStack &S,SElemType &e){
	if(S == NULL) return ERROR;
	e = S->data;
	p = S;
	S = S->next;
	delete p;
	return OK; 
}
```

5. 取栈顶元素

```cpp
SElemType GetTop(LinkStack S){
	if(S == NULL) exit(1);//exit(非零)表示没有正常结束
	else return S->data;
}
```

#### 栈与递归

> 递归：一个对象包含他自己或者自己给自己定义

**后调用先返回->栈**

**函数调用过程**

+ 调用前
  + 传递实参，返回地址
  + 局部变量分配存储区
  + 控制转移到被调用函数的入口
+ 调用后
  + 保存被调用函数的计算结果
  + 释放数据
  + 依照返回地址将控股、将控制转移到调用函数

> 空间效率：O(n)
>
> 时间效率：O(2^n)

**递归->非递归**

> 尾递归->循环
>
> 栈

### 练习

1. 输出2进制

```cpp
void conversion(int n){
	if(n == 0) return ;
	else {
		conversion(n/2);
		cout<<n%2;
	}
}
void main(){
	int n;
	cin>>n;
	conversion(n);
	cout<<endl;//输出换行
}
```

2. 找出从自然数1、2、……、m中任取k个数的所有组合。

+ 一般递归

```cpp
void comb(int m,int k){
	int i,j;
	for(i = m;i>=k;i--){
		a[k] = i;
		if(k>1) comb(i-1,k-1);
		else {
			for(j = a[0];j>0;j--) printf("%4d",a[j]);
			printf("\n");
		}
	}
}
```







## 队列

> 在表（队尾）一端插入，在另一端（队头）删除
>
> 顺序队列或链队
>
> 运算规则：先进先出

1. 表示

```cpp
#define M 100
Typedef struct{
	QElemType *base;
	int front;//队首
	int rear;//队尾
}SqQueue;
```

2. 一维数组表示

```cpp
front == rear;//空队
base[rear++] = X；//入队
X = base[front++];//出队
```

3. 初始化

```cpp
Status InitQueue(SqQueie &Q){
	Q.base = new QElemType[MAXQSIZE];
	if(!Q.base) exit(OVERFLOW);
	Q.front = Q.rear = 0;
	return OK;
}
```

4. 求循环队列的长度

```cpp
int  QueueLength (SqQueue Q){
    return (Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;                             
 }

```

5. 循环队列入队

```cpp
Status EnQueue(SqQueue &Q,QElemType e){
    if((Q.rear+1)%MAXQSIZE==Q.front)  return ERROR;
    Q.base[Q.rear]=e;
    Q.rear=(Q.rear+1)%MAXQSIZE;
     return OK;
}
```

6. 循环队列出队

```cpp
Status DeQueue (LinkQueue &Q,QElemType &e){
   if(Q.front==Q.rear) return ERROR;
   e=Q.base[Q.front];
   Q.front=(Q.front+1)%MAXQSIZE;
   return OK;
}
```





## 循环队列







### 链队列

```cpp
typedef struct QNode{
   QElemType   data;
   struct Qnode  *next;
}Qnode, *QueuePtr;
typedef struct {
   QueuePtr  front;            //队头指针   
   QueuePtr  rear;             //队尾指针
}LinkQueue;  
```

初始化

销毁

判空

求队头

入队

出队











