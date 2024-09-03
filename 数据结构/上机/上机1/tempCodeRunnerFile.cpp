#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAXSIZE 20
#define ERROR 0
#define OK 1

typedef int Status;

typedef struct{
    int weight;
    int sum;
}Point;

typedef struct SqStack{
    Point *base;
    Point *top;
    int stacksize;
}SqStack;

Status InitStack(SqStack *S)//顺序栈初始化
{
    S->base = (Point*)malloc(MAXSIZE * sizeof(Point));
    if(!S->base) return ERROR;
    S->top = S->base;
    S->stacksize = MAXSIZE;
    return OK;
}

bool StackEmpty(SqStack S)//顺序栈判空
{
    if (S.top == S.base) return true;
    return false;
}

int StackLength(SqStack S)//求顺序栈长度
{
    return S.top - S.base;
}

Status ClearStack(SqStack *S){
    if(S->base) S->top = S->base;
    return OK;
}

Status DestoryStack(SqStack *S){//顺序栈销毁
    if(S->base){
        free(S->base);
        S->stacksize = 0;
        S->base = S->top = NULL;
    }
    return OK;
}

Status Push(SqStack *S, Point e)    //顺序栈进栈
{
    if(StackLength(*S) == S->stacksize) return ERROR;
    e.sum += S->top->sum;
    *(S->top)++ = e;
    return OK;
}

Status Pop(SqStack *S, Point *e)    //顺序栈出栈
{
    if(S->top == S->base) return ERROR;
    *e = *--(S->top);
    return OK;
}

Status GetTop(SqStack S, Point *w){//取栈顶元素
    if(S.top == S.base) return ERROR;
    *w = *(S.top-1);
    return OK;
}

//判断新元素能否放进背包
Status CanPlaceIn(Point newpoint,SqStack BagStack,int T){
    if((newpoint.weight + BagStack.top->weight) > T) return ERROR;
    return OK;
}

Status OutputResult(SqStack Bag,int T){//输出结果
    Point *p = Bag.base;
    printf("(");
    while (p < Bag.top)
    {
       printf("%d ", p->weight);
       p++;
    }
    printf(")");
    return OK;
}

Status PLaceIn(int T, int n, int* a){
    SqStack BagStack;
    Point BagPoint;
    int result = 0;
    int i = 0;

    InitStack(&BagStack);
    BagPoint.sum = BagPoint.weight = a[i];
    Push(&BagStack, BagPoint);
    i++;
    int flag;

    BagPoint.weight = a[i];
    BagPoint.sum = a[i-1] + a[i];
    while(i < n)
    {
        while (BagPoint.sum < T)
        {
            flag = CanPlaceIn(BagPoint, BagStack, T);
            if (flag == OK) break;//可以放置
            i++;//不可以则向后搜索
            BagPoint.weight = a[i];
            //BagPoint.sum = BagStack.top->sum + a[i];
        }
        if (flag == OK)    //如果可以
        {
            Push(&BagStack, BagPoint);//压栈
            i++;
            BagPoint.weight = a[i];//继续向后搜索
            if(BagPoint.sum == n)    //已经找到一个解
            {
                OutputResult(BagStack, T);    //根据保存的栈，输出满足条件的结果
                result++;    //解的数量加1
                Pop(&BagStack, &BagPoint);    //弹栈
                i++;//继续向后搜索
                if(i >= n){//如果已经到结尾，必须回溯
                    Pop(&BagStack, &BagPoint);
                    i -= 2;
                }
                while((CanPlaceIn(BagPoint, BagStack, T) == ERROR) && !StackEmpty(BagStack))    //如果回退不成功则继续回退
                {
                    Pop(&BagStack, &BagPoint);
                    i--;
                }
            }
        }
        else    //不能放置
        {
            Pop(&BagStack, &BagPoint);
            i++;
            while((CanPlaceIn(BagPoint, BagStack, T) == ERROR) && !StackEmpty(BagStack))    //如果回退不成功则继续回退
            {
                Pop(&BagStack, &BagPoint);
                i--;
            }
        }
    }
    printf("解法个数:%d", result);
    DestoryStack(&BagStack);
    return OK;
}

int main()
{
    int T, n;
    printf("Input:");
    scanf("%d %d", &T, &n);
    if(n > MAXSIZE){
        printf("ERROR");
        return 0;
    }
    int *arr = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    printf("Output:\n");
    PLaceIn(T, n, arr);
    free(arr);
    return 0;
}