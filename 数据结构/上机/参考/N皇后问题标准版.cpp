#include <stdio.h>
#include <stdbool.h>

#define MAX_N 20

int stack[MAX_N]; // Stack to store the column number of queens
int top = -1;     // Stack top pointer

// Checks whether a queen can be placed at the given position
bool canPlaceQueen(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (stack[i] == col ||          // Same column
            stack[i] - i == col - row || // Main diagonal
            stack[i] + i == col + row)   // Secondary diagonal
        {
            return false;
        }
    }
    return true;
}

// Solves the N-Queens problem iteratively
void solveQueen(int N) {
    int count = 0; // Number of solutions found
    int row = 0;   // Current row

    while (row >= 0 && count == 0) {
        stack[row]++;
        while (stack[row] < N && !canPlaceQueen(row, stack[row])) {
            stack[row]++; // Try the next column
        }

        if (stack[row] >= N) { // Cannot place a queen in this row, backtrack
            row--;
        } else if (row == N - 1) { // Found a solution
            count++;
            printf("Solution:\n");
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (stack[i] == j) {
                        printf("Q ");
                    } else {
                        printf(". ");
                    }
                }
                printf("\n");
            }
            printf("\n");
        } else { // Move to the next row
            row++;
            stack[row] = -1;
        }
    }

    if (count == 0) {
        printf("No solution found\n");
    }
}

int main() {
    int N;

    printf("Please enter N: ");
    scanf("%d", &N);

    if (N < 4 || N > MAX_N) {
        printf("N is out of range, cannot solve the problem\n");
        return 0;
    }

    solveQueen(N);

    return 0;
}
/*#include <stdio.h>
#include <stdlib.h>
#define N 5
 
typedef struct //栈
{
    int data[N];
    int top;
}SqStack;
 
void InitSqStack(SqStack *S) //初始化栈
{
    //S = (SqStack*)malloc(sizeof(SqStack));
    S->top=-1;
}
 
int Push(SqStack *S,int m,int n)//进栈
{
 
    if(S->top == N-1)
    {
        return 0;
    }
 
    S->top++;
 
    S->data[S->top] = m*10+n;
 
 
    return 0;
}
int pop(SqStack *S ,int *x,int *y)//出栈
{
    if(S->top == -1)
    {
        return 0;
    }
 
    *x = S->data[S->top]/10;
    *y = S->data[S->top]%10;
    S->top--;
    return 1;
 
}
int StackEmpty(SqStack *S)//判断栈是否为空
{
    if(S->top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
 
void turn_1(int T[N][N],int x,int y) //杀！
{
    for(int i=0;i<N;i++)
    {
        for(int m=0;m<N;m++)
        {
            if(i==x&&m!=y)
            {
                T[i][m]++;
            }
            if(m==y&&i!=x)
            {
                T[i][m]++;
            }
            if(m+i==x+y&&i!=x)
            {
                T[i][m]++;
            }
            if(i-m==x-y&&i!=x)
            {
                T[i][m]++;
            }
        }
    }
    //return T;
}
void turn_0(int T[N][N],int x,int y) //复活
{
 
    for(int i=0;i<N;i++)
    {
        for(int m=0;m<N;m++)
        {
            if(i==x&&m!=y)
            {
                T[i][m]--;
            }
            if(m==y&&i!=x)
            {
                T[i][m]--;
            }
            if(m+i==x+y&&i!=x)
            {
                T[i][m]--;
            }
            if(i-m==x-y&&i!=x)
            {
                T[i][m]--;
            }
        }
    }
    //return T;
 
}
int find_0(int D[N],int D2[N]) //查找是否有可以放置皇后的位置
{
    for(int i=0;i<N;i++)
    {
        if(D[i]==0&&D2[i]==0)
        {
            return 1;
        }
    }
    return 0;
}
void printf_T(int T[N][N]) //格式化、打印棋盘
{
     for(int i=0;i<N;i++)
    {
        for(int m=0;m<N;m++)
        {
            if(T[i][m]==0)
            {
                printf("1");
            }
            else
            {
                printf("0");
            }
            if(m==N-1)
            {
                printf("\n");
            }
        }
    }
    printf("\n");
}
 
int main()
 
{
    int ans=0;
 
 
    for(int w=0;w<N;w++)
    {
    SqStack sq;
    InitSqStack(&sq);
    //int res = find_0(td[0]);
    int m=0;
    int x;
    int y;
    int td[N][N]={0};//棋盘
    int index[N][N]={0}; //辅助棋盘
    turn_1(td,0,w);
    Push(&sq,0,w);
 
    while(sq.top!=-1)
    {
        if(m!=N-2&&find_0(td[m+1],index[m+1]))  //如果下一行存在可以放置皇后的位置
        {
            for(int i=0;i<N;i++)
            {
 
                if(td[m+1][i]==0&&index[m+1][i]==0)
                {
 
                    Push(&sq,m+1,i);
                    //printf("ces\n");
                    turn_1(td,m+1,i);
                    //printf_T(td);
                    m=m+1;
                    break;
                }
            }
        }
        else if(m==N-2&&find_0(td[N-1],index[N-1])) //查找到最后一行，打印输出，继续回到上一行
        {
 
 
                ans++;
                printf("µÚ%d¸ö´ð°¸\n",ans);
                printf_T(td);
                for(int j=0;j<N;j++)
                {
                    index[m+1][j]=0;
                }
                pop(&sq,&x,&y);
                index[x][y]=1;
                turn_0(td,x,y);
 
                //td[x][y]++;
            //printf_T(td);
 
                m--;
 
 
 
        }
        else    //没找到，回到上一行
        {
            for(int j=0;j<N;j++)
            {
                index[m+1][j]=0;
            }
            //td[x][y]--;
            //printf("pop\n");
            pop(&sq,&x,&y);
            index[x][y]=1;
            turn_0(td,x,y);
            //printf_T(td);
            m--;
 
        }
    }}
    return 0;
}
*/