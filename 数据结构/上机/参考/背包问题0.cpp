#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;

// 定义节点结构体
typedef struct {
    ElemType weight;
    int sum;
} Point;

// 定义栈结构体
typedef struct {
    Point *base;
    Point *top;
    int stacksize;
} SqStack;

// 初始化栈
Status InitStack(SqStack* S) {
    S->base = (Point*)malloc(MAXSIZE * sizeof(Point));
    if (!S->base) exit(OVERFLOW);
    S->top = S->base;
    S->stacksize = MAXSIZE;
    return OK;
}

// 销毁栈
Status DestroyStack(SqStack* S) {
    free(S->base);
    S->base = NULL;
    S->top = NULL;
    S->stacksize = 0;
    return OK;
}

// 判断栈是否为空
Status StackEmpty(SqStack S) {
    if (S.top == S.base)
        return TRUE;
    else
        return FALSE;
}

// 入栈
Status Push(SqStack* S, Point e) {
    if (S->top - S->base >= S->stacksize)
        return ERROR;
    *(S->top) = e;
    S->top++;
    return OK;
}

// 出栈
Status Pop(SqStack* S, Point* e) {
    if (S->top == S->base)
        return ERROR;
    *e = *(--S->top);
    return OK;
}

// 判断当前节点是否可以加入背包
Status CanPlaceIn(Point newpoint, SqStack BagStack, int T) {
    if ((BagStack.top - BagStack.base) >= MAXSIZE)
        return ERROR;
   if ((newpoint.sum + BagStack.top[-1].sum) <= T) // 总重量不超过背包容量
        return OK;
    return ERROR;
}

// 输出结果
void OutputResult(SqStack BagStack, int T) {
    for (Point* p = BagStack.base; p != BagStack.top; p++) {
        printf("%d ", p->weight); // 输出结果
    }
    printf("\n");
}

// 主函数
Status PlaceIn(int T, int n, int* a) {
    SqStack BagStack;
    Point BagPoint;
    int result = 0;
    int i = 0;
    int reach_end = false;
    InitStack(&BagStack);

    // 处理第一个元素
    i++;
    BagPoint.weight = a[i-1];
    BagPoint.sum = a[i-1];
    Push(&BagStack, BagPoint);

    while (!reach_end || !StackEmpty(BagStack)) {
        // 处理当前元素
        BagPoint.weight = a[i];
        BagPoint.sum = BagStack.top[-1].sum + BagPoint.weight;

        if (CanPlaceIn(BagPoint, BagStack, T)) { // 能够入栈
            Push(&BagStack, BagPoint);
            i++;
            if (BagPoint.sum == T) {
                result++;
                Pop(&BagStack, &BagPoint);
                OutputResult(BagStack, T); // 输出结果
                i++;
                if (i < n) continue; // 继续处理下一个元素
                else reach_end = true;
            }
        }

        if ((!CanPlaceIn(BagPoint, BagStack, T)) || (reach_end && StackEmpty(BagStack))) { // 不能入栈或已达到终止条件
            if (StackEmpty(BagStack)) {
                reach_end = true;
                i--;
                continue;
            }
            Pop(&BagStack, &BagPoint);
            i--;
            if (i < n - 1) continue; // 继续处理当前元素的下一个元素
            else reach_end = true;
        }

        if (i >= n) { // 处理完所有元素
            if (StackEmpty(BagStack)) {
                reach_end = true;
                continue;
            }
            Pop(&BagStack, &BagPoint);
            i--;
            if (i < n - 1) continue; // 继续处理当前元素的下一个元素
            else reach_end = true;
        }
    }

    while (!StackEmpty(BagStack)) { // 确保将栈中所有元素弹出
        Pop(&BagStack, &BagPoint);
    }
    printf("The number of the result: %d\n", result);
    DestroyStack(&BagStack);
    return OK;
}

int main() {
    int T = 10, n = 6;
    int a[] = {1, 8, 4, 3, 5, 2};
    PlaceIn(T, n, a);
    return 0;
}