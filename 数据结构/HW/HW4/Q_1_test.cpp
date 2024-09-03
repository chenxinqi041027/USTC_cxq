#include <stdio.h>
#include <stdlib.h>
 
#define MAXSIZE 10
 
//定义迷宫 
int arr[MAXSIZE][MAXSIZE] = {
        1,1,1,1,1,1,1,1,1,1,
        1,0,0,1,0,0,0,1,0,1,
        1,0,0,1,0,0,0,1,0,1,
        1,0,0,0,0,1,1,0,0,1,
        1,0,1,1,1,0,0,0,0,1,
        1,0,0,0,1,0,0,0,0,1,
        1,0,1,0,0,0,1,0,0,1,
        1,0,1,1,1,0,1,1,0,1,
        1,1,0,0,0,1,0,0,2,1,
        1,1,1,1,1,1,1,1,1,1
};

 
//行走过的标志
int arr_tar[MAXSIZE][MAXSIZE] = {0};
 
//栈的数据域 
typedef struct Stack
{
	int x;
	int y;
	int direction;
}Stack;
 
//顺序栈 
typedef struct SqStack
{
	Stack* base;
	int top;
}SqStack;
 
//初始化
void InitStack(SqStack* stack)
{
	stack->base = (Stack*)malloc(MAXSIZE * MAXSIZE * sizeof(Stack));
	stack->top = 0;
}
 
//入栈
void InsertStack(SqStack* stack, Stack data)
{
	stack->base[stack->top] = data;
	stack->top++;
	
	printf("arr[%d][%d]\n", data.x, data.y);
} 
 
//出栈 
Stack PopStack(SqStack* stack)
{
	stack->top--;
	
	printf("arr[%d][%d]\n", stack->base[stack->top].x, stack->base[stack->top].y);
	return stack->base[stack->top];
}
 
//判栈空
int StackEmpty(SqStack* stack)
{
	if (stack->top == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
 
//取栈顶元素
Stack GetTop(SqStack* stack)
{
	int q = stack->top - 1;
	
	return stack->base[q];
}
 
//判断该位置是否为墙和之前是否经过 
int CanPass(Stack data)
{
	if (arr[data.x][data.y] == 1 || arr_tar[data.x][data.y] == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
 
//判断该位置是否为出口 
int IsEnd(Stack data)
{
	if (arr[data.x][data.y] == 2) 
	{
		//printf("发现出口！！！\n"); 
		return 1;
	}
	else
	{
		return 0;
	}
}
 
//移动
void move(SqStack* stack)
{
	Stack data = GetTop(stack);
	Stack new_data;
	
	if (data.direction == 1)//东 
	{
		//printf("向东走了一格\n");
		new_data.direction = 1;
		new_data.x = data.x;
		new_data.y = data.y + 1;
	}
	else if (data.direction == 2)//南 
	{
		//printf("向南走了一格\n");
		new_data.direction = 1;
		new_data.x = data.x + 1;
		new_data.y = data.y;
	}
	else if (data.direction == 3)//西 
	{
		//printf("向西走了一格\n");
		new_data.direction = 1;
		new_data.x = data.x;
		new_data.y = data.y - 1;
	}
	else if (data.direction == 4)//北 
	{
		//printf("向北走了一格\n");
		new_data.direction = 1;
		new_data.x = data.x - 1;
		new_data.y = data.y;
	}
 
	InsertStack(stack, new_data);
} 
 
//更新走过的路径
void AddPath(Stack data)
{
	arr_tar[data.x][data.y] = 1;
}
void PopPath(Stack data)
{
	arr_tar[data.x][data.y] = 0;
}
 
int main()
{
	SqStack* stack = (SqStack*)malloc(sizeof(SqStack));
	//遍历迷宫 
	int i, j;
	for (i = 0;i < MAXSIZE; i++)
	{
		for (j = 0;j < MAXSIZE; j++)
		{
			printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}
	
		
	//printf("--------------------破译中--------------------\n");
	
	//初始化
	InitStack(stack);
	//设置初始点 
	int x = 1, y = 1;
	Stack data = {x, y, 1};
	InsertStack(stack, data);
 
	do
	{
		if(!CanPass(GetTop(stack)))//不是墙并且从未走过 
		{
			if (IsEnd(GetTop(stack)))//检测出口 
			{
				break;
			}
			else
			{
				AddPath(GetTop(stack));
				move(stack);//添加下一个块到栈中	
			} 
		}
		else//是墙 
		{
 			PopStack(stack);
 			PopPath(GetTop(stack));//栈顶元素的路径不算入经过地点 
 			
 			if (!StackEmpty(stack))
 			{
 				if (GetTop(stack).direction == 4 && !StackEmpty(stack))
 				{
 					AddPath(GetTop(stack));
 					PopStack(stack);
 					PopPath(GetTop(stack));
				}
				if (GetTop(stack).direction < 4)
				{
					//更新栈顶坐标的方向
					stack->base[stack->top - 1].direction++;		
				}
			}
		} 
		//getchar();
	}while(!StackEmpty(stack));
	
	//printf("--------------------破译完毕--------------------\n");
	//输出结果
	while (!StackEmpty(stack))
	{
		data = PopStack(stack);
		arr[data.x][data.y] = 3;
	} 
	//遍历迷宫 
	for (i = 0;i < MAXSIZE; i++)
	{
		for (j = 0;j < MAXSIZE; j++)
		{
			printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}
	 
	return 0;
} 
