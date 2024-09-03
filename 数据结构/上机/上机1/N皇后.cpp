#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<math.h>

#define MAXSIZE 20
#define ERROR 0
#define OK 1

typedef int Status;

//用来记录皇后位置的点
typedef struct
{
	int col;//列坐标值
	int row;//行坐标值
}Point;

//顺序栈
typedef struct SqStack
{
	Point *base;//栈底指针
	Point *top;//栈顶指针，指向真实栈顶元素的下一位置
	int stacksize; 
}SqStack;

Status InitStack(SqStack &S)//顺序栈初始化
{
    S.base=new Point[MAXSIZE];
	if(!S.base) return ERROR;
	S.top = S.base;
	S.stacksize = MAXSIZE;
	return OK;
}

bool StackEmpty(SqStack S)//顺序栈判空
{
	if (S.top==S.base) return true;
	return false;
}

int StackLength(SqStack S)//求顺序栈长度
{
	return S.top-S.base;
}

Status Push(SqStack &S, Point e)    //顺序栈进栈
{
	if(StackLength(S)==S.stacksize) return ERROR;
    *S.top++=e;
	return OK;
}

Status Pop(SqStack &S, Point &e)    //顺序栈出栈
{
	if(S.top==S.base) return ERROR;
    e=*--S.top;
	return OK;
}

//判断新皇后位置和已有皇后是否有冲突，没有冲突返回OK，有冲突返回ERROR
Status CanPlaceQueen(Point newQueen, SqStack QueenStack)
{
	Point *preQueen;
    preQueen=QueenStack.base;
	int x1=newQueen.col;
	int y1=newQueen.row;
	int flag = OK;
	while (preQueen<QueenStack.top)
	{
		int x2=preQueen->col;
		int y2=preQueen->row;
		if(x1==x2)    //如果新的皇后和前面的皇后在同一列
		{
			flag=ERROR;
			break;
		}
		if(abs(x2-x1)==abs(y2-y1))    //新皇后和前面的皇后在同一正斜线或逆斜线
		{
			flag = ERROR;
			break;
		}
		preQueen++;
	}
	return flag;
}

Status OutputResult(SqStack QueenStack, int N,FILE* fpWrite)//输出
{
	int Q[MAXSIZE][MAXSIZE]={0};
	Point *p = QueenStack.base;//从底开始遍历
	while(p<QueenStack.top){
		Q[p->row-1][p->col-1]=1;
		p++;
	}
	for(int i=0;i<N;i++){
        for (int j=0;j<N;j++){
			fprintf(fpWrite,"%d  ",Q[i][j]);
		}
		fprintf(fpWrite,"\n");
	}
	return OK;
}

Status PlaceQueen(int N,FILE* fpWrite)//非递归算法
{
	SqStack QueenStack;
	Point QueenPoint;

	InitStack(QueenStack);//初始化链表
	int resultCount = 0;    //记录满足要求的解数量
	QueenPoint.col = 1;//列
	QueenPoint.row = 1;//行
	Push(QueenStack,QueenPoint);
    int flag;

	QueenPoint.col = 2;
	QueenPoint.row = 1;
	while (QueenPoint.row<=N && QueenPoint.col<=N)
	{
		while (QueenPoint.col<=N)
		{
            flag=CanPlaceQueen(QueenPoint,QueenStack);
            if(flag==OK) break;//这一行的该位置为合适位置
			QueenPoint.col++;    //存在冲突，则列往后移动一个位置
		}
		if(flag==OK)    //如果在该行上存在合适的位置
		{
			Push(QueenStack, QueenPoint);//压栈
			QueenPoint.row++;
			QueenPoint.col=1;//从第一列开始
			if (QueenPoint.row>N){
                OutputResult(QueenStack,N,fpWrite);
                break;
            }
		}
		else    //在本行上没有找到合适的位置，执行回退
		{
			Pop(QueenStack,QueenPoint);
			QueenPoint.col++;//列数加一
			while(QueenPoint.col>N && !StackEmpty(QueenStack))    //如果回退不成功，则继续回退
			{
				Pop(QueenStack,QueenPoint);
				QueenPoint.col++;
			}
		}
	}
	return OK;
}

int main(int argc,char *argv[])
{
    int N;
	//输入
	FILE* fpRead;
    fpRead=fopen(argv[1],"r");
    if(fpRead==NULL) return 0;
    fscanf(fpRead,"%d",&N);
	if(N<4||N>MAXSIZE){//判断是否合法
        printf("ERROR");
        return 0;
    }

	//输出
    FILE* fpWrite;
    fpWrite=fopen(argv[2],"w");
	fprintf(fpWrite,"Output:\n");
	PlaceQueen(N,fpWrite);

	fclose(fpRead);
    fclose(fpWrite);
	return 0;
}
