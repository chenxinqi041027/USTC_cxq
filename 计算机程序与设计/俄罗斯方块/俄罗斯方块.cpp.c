#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#define UL unsigned int

#define ROW 28 + 1 //游戏区行数
#define COL 18 + 2 //游戏区列数

#define DOWN 80 //方向键：下
#define LEFT 75 //方向键：左
#define RIGHT 77 //方向键：右 
#define TAB 9 //空格键
#define ESC 27 //Esc键


struct PlayArea 
{
	int data[ROW][COL + 10]; //用于标记指定位置是否有方块（1为有，0为无）
	int color[ROW][COL + 10]; //用于记录指定位置的方块颜色编码
}area;

struct Block
{
	int space[4][4];
}block[7][4]; //用于存储7种基本形状方块的各自的4种形态的信息

void HideCursor();        //隐藏光标
void Gotoxy(int x, int y);//光标跳转
void InitPlayArea();      //初始化游戏区 
void InitBlock();         //初始化方块
void color(int num);      //使用十进制编码颜色设置
void DrawBlock(int shape, int form, int x, int y);//画出方块
void SPause();      //暂停界面 
void EraseBlock(int shape, int form, int x, int y);//擦除方块 
int IsLegal(int shape, int form, int x, int y);    //合法性判断
int IsCount();      //判断得分
void IsGameOver();  //判断是否完蛋 
int ShowMenu();     //显示主菜单并选择模式
void ClearArea();   //清除菜单 
void StartGame();   //游戏的主函数 
void ReadRecord();  //从文件读取最高分
void WriteRecord(); //更新最高分到文件
int Max, Record, Speed; 

int main()
{
	system("title Easy_Tetris by PB22111679 and PB22111711"); //设置cmd窗口的名字
	HideCursor(); //隐藏光标
	Max = 0, Record = 0;
	Speed = ShowMenu();
	ReadRecord(); //从文件读取最高分到Max记录	
	InitPlayArea(); 
	InitBlock(); 
	srand((UL)time(NULL)); 
	StartGame(); 
	return 0;
}
//显示主菜单 
int ShowMenu()
{
	Gotoxy(4, 4);
	printf("欢迎进入Tetris小游戏！");
	Gotoxy(4, 6);
	printf("请选择游戏模式：");
	Gotoxy(4, 8);
	printf("按E 简单模式");
	Gotoxy(4, 10);
	printf("按N 一般模式");
	Gotoxy(4, 12);
	printf("按H 困难模式");
	Gotoxy(4, 15);
	printf("请选择...");
	char ch = getch();
	switch(ch)
	{
		case 'e':
		case 'E': 
		{
			ClearArea();
			return 20000;
		}
		case 'n':
		case 'N': 
		{
			ClearArea();
			return 13500;
		}
		case 'H':
		case 'h': 
		{
			ClearArea();
			return 9000;
		}
	} 
}
void ClearArea()
{
	system("cls");
	Sleep(300);
}

//隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO curInfo; //定义光标信息的结构体变量 
	curInfo.dwSize = 1;   //赋值后使隐藏光标有效       
	curInfo.bVisible = FALSE;    //将光标设置为不可见
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取控制台句柄
	SetConsoleCursorInfo(handle, &curInfo);          //设置光标信息
}

//光标跳转
void Gotoxy(int x, int y)//(其实是课本上的SetPos) 
{
	COORD pos;//定义光标位置的结构体变量 
	pos.X = x;//定义横坐标 
	pos.Y = y;//定义纵坐标 
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//控制句柄// 
	SetConsoleCursorPosition(handle, pos);
}

//初始化界面
void InitPlayArea()
{
	color(7); //颜色设置为白色
	int i, j;
	for(i = 0; i < ROW; i++)
	{
		for(j = 0; j < COL + 10; j++)
		{
			if(j == 0 || j == COL - 1 || j == COL + 9)//绘制竖直边框 
			{
				area.data[i][j] = 1; 
				area.color[i][j] = 7;
				Gotoxy(2 * j, i);
				printf("■");
			}
			else if(i == ROW - 1)//绘制底边 
			{
				area.data[i][j] = 1; 
				area.color[i][j] = 7;
				printf(" ■");
			}
			else
				area.data[i][j] = 0; 
		}
	}
	for(i = COL; i < COL + 10; i++)//绘制旁栏 
	{
		area.data[8][i] = 1; 
		area.color[8][i] = 7;
		Gotoxy(2 * i, 8);
		printf("■");
	}
    //打印旁栏提示 
	Gotoxy(2 * COL + 4, 1);
	printf("下一个方块：");
	Gotoxy(2 * COL + 4, ROW - 19);
	printf("左移：←");
	Gotoxy(2 * COL + 4, ROW - 17);
	printf("右移：→");
	Gotoxy(2 * COL + 4, ROW - 15);
	printf("加速：↓");
	Gotoxy(2 * COL + 4, ROW - 13);
	printf("旋转：Tab");
	Gotoxy(2 * COL + 4, ROW - 11);
	printf("暂停: S");
	Gotoxy(2 * COL + 4, ROW - 9);
	printf("退出: Esc");
	Gotoxy(2 * COL + 4, ROW - 7);
	printf("重新开始:R");
	Gotoxy(2 * COL + 4, ROW - 5);
	printf("最高纪录:%d", Max);
	Gotoxy(2 * COL + 4, ROW - 3);
	printf("当前分数：%d", Record);
}
//初始化方块
void InitBlock()
{
	int i; 
	//“T”形
	for(i = 0; i <= 2; i++)
		block[0][0].space[1][i] = 1;
	block[0][0].space[2][1] = 1;
	//“L”形
	for(i = 1; i <= 3; i++)
		block[1][0].space[i][1] = 1;
	block[1][0].space[3][2] = 1;
	//“J”形
	for(i = 1; i <= 3; i++)
		block[2][0].space[i][2] = 1;
	block[2][0].space[3][1] = 1;
	for(i = 0; i <= 1; i++)
	{
		//“Z”形
		block[3][0].space[1][i] = 1;
		block[3][0].space[2][i + 1] = 1;
		//“S”形
		block[4][0].space[1][i + 1] = 1;
		block[4][0].space[2][i] = 1;
		//“田”形
		block[5][0].space[1][i + 1] = 1;
		block[5][0].space[2][i + 1] = 1;
	}
	//“I”形
	for(i = 0; i <= 3; i++)
		block[6][0].space[i][1] = 1;
	int temp[4][4], j, shape, form;
	for(shape = 0; shape < 7; shape++) //7种形状
	{
		for(form = 0; form < 3; form++) 
		{
			//获取第form种形态
			for(i = 0; i < 4; i++)
			{
				for(j = 0; j < 4; j++)
				{
					temp[i][j] = block[shape][form].space[i][j];
				}
			}
			//将第form种形态顺时针旋转，得到第form+1种形态
			for(i = 0; i < 4; i++)
			{
				for(j = 0; j < 4; j++)
				{
					block[shape][form + 1].space[i][j] = temp[3 - j][i];
				}
			}
		}
	}
}
//颜色设置
void color(int c)
{
	switch (c)
	{
	case 0:
		c = 5; //“T”形
		break;
	case 1:
	case 2:
		c = 12; //“L”形和“J”形
		break;
	case 3:
	case 4:
		c = 3; //“Z”形和“S”形
		break;
	case 5:
		c = 14; //“O”形
		break;
	case 6:
		c = 11; //“I”形
		break;
	default:
		c = 7; //其他默认设置为白色
		break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); 
}
//画出方块
void DrawBlock(int shape, int form, int x, int y)
{
	int i, j;
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			if(block[shape][form].space[i][j] == 1) //如果该位置有方块
			{
				Gotoxy(2 * (x + j), y + i); //光标跳转到指定位置
				printf("■"); //输出方块
			}
		}
	}
}
//擦除方块 
void EraseBlock(int shape, int form, int x, int y)
{
	int i, j; 
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			if(block[shape][form].space[i][j] == 1) //如果该位置有方块
			{
				Gotoxy(2 * (x + j), y + i); //光标跳转到指定位置
				printf("  "); //打印空格覆盖（两个空格）
			}
		}
	}
}
//合法性判断
int IsLegal(int shape, int form, int x, int y)
{
	int i, j;
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			//如果方块落下or旋转的位置本来就已经有方块了，则不合法
			if((block[shape][form].space[i][j] == 1) && (area.data[y + i][x + j] == 1))
				return 0; //不合法
		}
	}
	return 1; //合法
}
//判断是否得分 
int IsCount()
{
	int i, j;
	for(i = ROW - 2; i > 4; i--)
	{
		int sum = 0; //记录第i行的方块个数
		for(j = 1; j < COL - 1; j++)
		{
			sum += area.data[i][j]; //统计第i行的方块个数
		}
		if(sum == 0) //该行没有方块，无需再判断其上的层次（无需再继续判断是否得分）
			break; //跳出循环
		if(sum == COL - 2) //该行全是方块，可得分
		{
			Record += 10; //满一行加10分
			color(7); //颜色设置为白色
			Gotoxy(2 * COL + 4, ROW - 3); //光标跳转到显示当前分数的位置
			printf("当前分数：%d", Record); //更新当前分数
			for(j = 1; j < COL - 1; j++) //清除得分行的方块信息
			{
				area.data[i][j] = 0; //该位置得分后被清除，标记为无方块
				Gotoxy(2 * j, i); //光标跳转到该位置
				printf("  "); //打印空格覆盖（两个空格）
			}
			//把被清除行上面的行整体向下挪一格
			for(j = i; j > 1; j--)
			{
				sum = 0; //记录上一行的方块个数
				int k; 
				for(k = 1; k < COL - 1; k++)
				{
					sum += area.data[j - 1][k]; //统计上一行的方块个数
					area.data[j][k] = area.data[j - 1][k]; //将上一行方块的标识移到下一行
					area.color[j][k] = area.color[j - 1][k]; //将上一行方块的颜色编号移到下一行
					if(area.data[j][k] == 1) //上一行移下来的是方块，打印方块
					{
						Gotoxy(2 * k, j); //光标跳转到该位置
						color(area.color[j][k]); //颜色设置为还方块的颜色
						printf("■"); //打印方块
					}
					else //上一行移下来的是空格，打印空格
					{
						Gotoxy(2 * k, j); //光标跳转到该位置
						printf("  "); //打印空格（两个空格）
					}
				}
				if (sum == 0) //上一行移下来的全是空格，无需再将上层的方块向下移动（移动结束）
					return 1; //返回1，表示还需调用该函数进行判断（移动下来的可能还有满行）
			}
		}
	}
	IsGameOver();
	return 0; //判断结束，无需再调用该函数进行判断
}
//判断是否结束 
void IsGameOver()
{
	int i; 
	for(i = 1; i < COL - 1; i++)
	{
		if(area.data[1][i] == 1) //以第1行为顶层，不是第0行
		{
			system("cls"); 
			color(7); 
			Gotoxy(2 * (COL / 3), ROW / 2 - 3);
			if(Record > Max)
			{
				printf("恭喜你打破最高记录，最高记录更新为%d", Record);
				WriteRecord();
			}
			else if(Record == Max)
			{
				printf("与最高记录持平，加油再创佳绩", Record);
			}
			else
			{
				printf("请继续加油，当前与最高记录相差%d", Max - Record);
			}
			Gotoxy(2 * (COL / 3), ROW / 2);
			printf("GAME OVER");
			while(1)
			{
				char ch;
				Gotoxy(2 * (COL / 3), ROW / 2 + 3);
				printf("再来一局?(y/n):");
				scanf("%c", &ch);
				if(ch == 'y' || ch == 'Y')
				{
					system("cls");
					main();
				}
				else if(ch == 'n' || ch == 'N')
				{
					Gotoxy(2 * (COL / 3), ROW / 2 + 5);
					exit(0);
				}
				else
				{
					Gotoxy(2 * (COL / 3), ROW / 2 + 4);
					printf("选择错误，请再次选择");
				}
			}
		}
	}
}
//暂停界面 
void SPause()
{
	int d[COL + 2], c[COL + 2], i, y = (ROW) / 2;
	for(i = 0; i < COL; i++)
	{
		d[i] = area.data[y][i], c[i] = area.color[y][i];
		Gotoxy(2 * i, y);
		printf("  ");
	} 
	Gotoxy(2, y);
	printf("暂停中，请按任意键继续...");
	system("pause>nul"); //暂停（按任意键继续）
	Gotoxy(2, y);
	printf("                         ");
	for(i = 0; i < COL; i++)//重新绘制被消掉的地方 
	{
		if(d[i] == 1)
		{
			color(c[i]);
			Gotoxy(2 * i, y);
			printf("■");
		}
	}
} 
//游戏主函数
void StartGame()
{
	int shape = rand() % 7, form = rand() % 4; //随机获取方块的形状和形态
	while(1)
	{
		int t = 0;                                         //此处需要先更新下一个块，再下落 
		int nextShape = rand() % 7, nextForm = rand() % 4; //随机获取下一个方块的形状和形态
		int x = (COL - 8) / 2 , y = 0;                     //方块初始下落位置的横纵坐标
		color(nextShape);                                  //颜色设置为下一个方块的颜色
		DrawBlock(nextShape, nextForm, COL + 3, 3);        //将下一个方块显示在右上角
		while (1)
		{
			color(shape);                 //颜色设置为当前正在下落的方块
			DrawBlock(shape, form, x, y); //将该方块显示在初始下落位置
			if(t == 0)
			{
				t = Speed;       //规定下落一格的速度 
			}
			while(--t)           //这里必须是--t，不然之后t一直是负的 
			{
				if(kbhit() != 0) //下落一格的时间之内进行了其他操作（余下的时间足以忽略） 
					break;
			}
			if(t == 0)           //玩家未进行操作，或者方块已经到底了 
			{
				if(IsLegal(shape, form, x, y + 1) == 0)//到底部：更新游戏区地图的状态 
				{
					int i, j;
					for(i = 0; i < 4; i++)
					{
						for(j = 0; j < 4; j++)
						{
							if(block[shape][form].space[i][j] == 1)
							{
								area.data[y + i][x + j] = 1;
								area.color[y + i][x + j] = shape; 
							}
						}
					}
					while(IsCount()); 
					break; 
				}
				else //未到底部
				{
					EraseBlock(shape, form, x, y); y++; //准备移动  
				}
			}
			else //进行了其他操作 
			{
				char ch = getch();
				switch(ch)
				{
				case DOWN: //方向键：下
					if(IsLegal(shape, form, x, y + 1) == 1) //判断方块向下移动一位后是否合法
					{
						EraseBlock(shape, form, x, y); y += 2;
					}
					break;
				case LEFT: //方向键：左
					if(IsLegal(shape, form, x - 1, y) == 1) //判断方块向左移动一位后是否合法
					{
						EraseBlock(shape, form, x, y); x--; 
					}
					break;
				case RIGHT: //方向键：右
					if(IsLegal(shape, form, x + 1, y) == 1) //判断方块向右移动一位后是否合法
					{
						EraseBlock(shape, form, x, y); x++; 
					}
					break;
				case TAB: //空格键
					if(IsLegal(shape, (form + 1) % 4, x, y + 1) == 1) //判断方块旋转后是否合法
					{
						EraseBlock(shape, form, x, y); 
						form = (form + 1) % 4; 
						y++;
					}
					break;
				case ESC: //Esc键
					system("cls"); 
					color(7);
					Gotoxy(COL, ROW / 2);
					printf("  游戏结束  ");
					Gotoxy(COL, ROW / 2 + 2);
					exit(0); 
				case 's':
				case 'S':  
					SPause();
					break;
				case 'r':
				case 'R': 
					system("cls"); 
					main(); //重新游戏 
				}
			}
		}
		shape = nextShape, form = nextForm; 
		EraseBlock(nextShape, nextForm, COL + 3, 3); //将右上角的方块信息用空格覆盖
	}
}
//从文件读取最高分
void ReadRecord()
{
	FILE* pf = fopen("俄罗斯方块最高得分记录.txt", "r"); 
	if (pf == NULL) //还没有创建文件 
	{
		pf = fopen("俄罗斯方块最高得分记录.txt", "w"); 
		fwrite(&Record, sizeof(int), 1, pf); //将max写入文件（此时max为0），即将最高历史得分初始化为0
	}
	fread(&Max, sizeof(int), 1, pf); //读取文件中的最高历史得分到max当中
	fclose(pf); 
	pf = NULL;
}
//更新最高分到文件
void WriteRecord()
{
	FILE* pf = fopen("俄罗斯方块最高得分记录.txt", "w"); 
	if (pf == NULL) 
	{
		printf("保存最高得分记录失败\n");
		exit(0);
	}
	fwrite(&Record, sizeof(int), 1, pf); //更新最高历史得分
	fclose(pf); 
	pf = NULL; 
}
