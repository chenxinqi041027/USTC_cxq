#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#define UL unsigned int

#define ROW 28 + 1 //��Ϸ������
#define COL 18 + 2 //��Ϸ������

#define DOWN 80 //���������
#define LEFT 75 //���������
#define RIGHT 77 //��������� 
#define TAB 9 //�ո��
#define ESC 27 //Esc��


struct PlayArea 
{
	int data[ROW][COL + 10]; //���ڱ��ָ��λ���Ƿ��з��飨1Ϊ�У�0Ϊ�ޣ�
	int color[ROW][COL + 10]; //���ڼ�¼ָ��λ�õķ�����ɫ����
}area;

struct Block
{
	int space[4][4];
}block[7][4]; //���ڴ洢7�ֻ�����״����ĸ��Ե�4����̬����Ϣ

void HideCursor();        //���ع��
void Gotoxy(int x, int y);//�����ת
void InitPlayArea();      //��ʼ����Ϸ�� 
void InitBlock();         //��ʼ������
void color(int num);      //ʹ��ʮ���Ʊ�����ɫ����
void DrawBlock(int shape, int form, int x, int y);//��������
void SPause();      //��ͣ���� 
void EraseBlock(int shape, int form, int x, int y);//�������� 
int IsLegal(int shape, int form, int x, int y);    //�Ϸ����ж�
int IsCount();      //�жϵ÷�
void IsGameOver();  //�ж��Ƿ��군 
int ShowMenu();     //��ʾ���˵���ѡ��ģʽ
void ClearArea();   //����˵� 
void StartGame();   //��Ϸ�������� 
void ReadRecord();  //���ļ���ȡ��߷�
void WriteRecord(); //������߷ֵ��ļ�
int Max, Record, Speed; 

int main()
{
	system("title Easy_Tetris by PB22111679 and PB22111711"); //����cmd���ڵ�����
	HideCursor(); //���ع��
	Max = 0, Record = 0;
	Speed = ShowMenu();
	ReadRecord(); //���ļ���ȡ��߷ֵ�Max��¼	
	InitPlayArea(); 
	InitBlock(); 
	srand((UL)time(NULL)); 
	StartGame(); 
	return 0;
}
//��ʾ���˵� 
int ShowMenu()
{
	Gotoxy(4, 4);
	printf("��ӭ����TetrisС��Ϸ��");
	Gotoxy(4, 6);
	printf("��ѡ����Ϸģʽ��");
	Gotoxy(4, 8);
	printf("��E ��ģʽ");
	Gotoxy(4, 10);
	printf("��N һ��ģʽ");
	Gotoxy(4, 12);
	printf("��H ����ģʽ");
	Gotoxy(4, 15);
	printf("��ѡ��...");
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

//���ع��
void HideCursor()
{
	CONSOLE_CURSOR_INFO curInfo; //��������Ϣ�Ľṹ����� 
	curInfo.dwSize = 1;   //��ֵ��ʹ���ع����Ч       
	curInfo.bVisible = FALSE;    //���������Ϊ���ɼ�
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ����̨���
	SetConsoleCursorInfo(handle, &curInfo);          //���ù����Ϣ
}

//�����ת
void Gotoxy(int x, int y)//(��ʵ�ǿα��ϵ�SetPos) 
{
	COORD pos;//������λ�õĽṹ����� 
	pos.X = x;//��������� 
	pos.Y = y;//���������� 
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//���ƾ��// 
	SetConsoleCursorPosition(handle, pos);
}

//��ʼ������
void InitPlayArea()
{
	color(7); //��ɫ����Ϊ��ɫ
	int i, j;
	for(i = 0; i < ROW; i++)
	{
		for(j = 0; j < COL + 10; j++)
		{
			if(j == 0 || j == COL - 1 || j == COL + 9)//������ֱ�߿� 
			{
				area.data[i][j] = 1; 
				area.color[i][j] = 7;
				Gotoxy(2 * j, i);
				printf("��");
			}
			else if(i == ROW - 1)//���Ƶױ� 
			{
				area.data[i][j] = 1; 
				area.color[i][j] = 7;
				printf(" ��");
			}
			else
				area.data[i][j] = 0; 
		}
	}
	for(i = COL; i < COL + 10; i++)//�������� 
	{
		area.data[8][i] = 1; 
		area.color[8][i] = 7;
		Gotoxy(2 * i, 8);
		printf("��");
	}
    //��ӡ������ʾ 
	Gotoxy(2 * COL + 4, 1);
	printf("��һ�����飺");
	Gotoxy(2 * COL + 4, ROW - 19);
	printf("���ƣ���");
	Gotoxy(2 * COL + 4, ROW - 17);
	printf("���ƣ���");
	Gotoxy(2 * COL + 4, ROW - 15);
	printf("���٣���");
	Gotoxy(2 * COL + 4, ROW - 13);
	printf("��ת��Tab");
	Gotoxy(2 * COL + 4, ROW - 11);
	printf("��ͣ: S");
	Gotoxy(2 * COL + 4, ROW - 9);
	printf("�˳�: Esc");
	Gotoxy(2 * COL + 4, ROW - 7);
	printf("���¿�ʼ:R");
	Gotoxy(2 * COL + 4, ROW - 5);
	printf("��߼�¼:%d", Max);
	Gotoxy(2 * COL + 4, ROW - 3);
	printf("��ǰ������%d", Record);
}
//��ʼ������
void InitBlock()
{
	int i; 
	//��T����
	for(i = 0; i <= 2; i++)
		block[0][0].space[1][i] = 1;
	block[0][0].space[2][1] = 1;
	//��L����
	for(i = 1; i <= 3; i++)
		block[1][0].space[i][1] = 1;
	block[1][0].space[3][2] = 1;
	//��J����
	for(i = 1; i <= 3; i++)
		block[2][0].space[i][2] = 1;
	block[2][0].space[3][1] = 1;
	for(i = 0; i <= 1; i++)
	{
		//��Z����
		block[3][0].space[1][i] = 1;
		block[3][0].space[2][i + 1] = 1;
		//��S����
		block[4][0].space[1][i + 1] = 1;
		block[4][0].space[2][i] = 1;
		//�����
		block[5][0].space[1][i + 1] = 1;
		block[5][0].space[2][i + 1] = 1;
	}
	//��I����
	for(i = 0; i <= 3; i++)
		block[6][0].space[i][1] = 1;
	int temp[4][4], j, shape, form;
	for(shape = 0; shape < 7; shape++) //7����״
	{
		for(form = 0; form < 3; form++) 
		{
			//��ȡ��form����̬
			for(i = 0; i < 4; i++)
			{
				for(j = 0; j < 4; j++)
				{
					temp[i][j] = block[shape][form].space[i][j];
				}
			}
			//����form����̬˳ʱ����ת���õ���form+1����̬
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
//��ɫ����
void color(int c)
{
	switch (c)
	{
	case 0:
		c = 5; //��T����
		break;
	case 1:
	case 2:
		c = 12; //��L���κ͡�J����
		break;
	case 3:
	case 4:
		c = 3; //��Z���κ͡�S����
		break;
	case 5:
		c = 14; //��O����
		break;
	case 6:
		c = 11; //��I����
		break;
	default:
		c = 7; //����Ĭ������Ϊ��ɫ
		break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); 
}
//��������
void DrawBlock(int shape, int form, int x, int y)
{
	int i, j;
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			if(block[shape][form].space[i][j] == 1) //�����λ���з���
			{
				Gotoxy(2 * (x + j), y + i); //�����ת��ָ��λ��
				printf("��"); //�������
			}
		}
	}
}
//�������� 
void EraseBlock(int shape, int form, int x, int y)
{
	int i, j; 
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			if(block[shape][form].space[i][j] == 1) //�����λ���з���
			{
				Gotoxy(2 * (x + j), y + i); //�����ת��ָ��λ��
				printf("  "); //��ӡ�ո񸲸ǣ������ո�
			}
		}
	}
}
//�Ϸ����ж�
int IsLegal(int shape, int form, int x, int y)
{
	int i, j;
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			//�����������or��ת��λ�ñ������Ѿ��з����ˣ��򲻺Ϸ�
			if((block[shape][form].space[i][j] == 1) && (area.data[y + i][x + j] == 1))
				return 0; //���Ϸ�
		}
	}
	return 1; //�Ϸ�
}
//�ж��Ƿ�÷� 
int IsCount()
{
	int i, j;
	for(i = ROW - 2; i > 4; i--)
	{
		int sum = 0; //��¼��i�еķ������
		for(j = 1; j < COL - 1; j++)
		{
			sum += area.data[i][j]; //ͳ�Ƶ�i�еķ������
		}
		if(sum == 0) //����û�з��飬�������ж����ϵĲ�Σ������ټ����ж��Ƿ�÷֣�
			break; //����ѭ��
		if(sum == COL - 2) //����ȫ�Ƿ��飬�ɵ÷�
		{
			Record += 10; //��һ�м�10��
			color(7); //��ɫ����Ϊ��ɫ
			Gotoxy(2 * COL + 4, ROW - 3); //�����ת����ʾ��ǰ������λ��
			printf("��ǰ������%d", Record); //���µ�ǰ����
			for(j = 1; j < COL - 1; j++) //����÷��еķ�����Ϣ
			{
				area.data[i][j] = 0; //��λ�õ÷ֺ���������Ϊ�޷���
				Gotoxy(2 * j, i); //�����ת����λ��
				printf("  "); //��ӡ�ո񸲸ǣ������ո�
			}
			//�ѱ���������������������Ųһ��
			for(j = i; j > 1; j--)
			{
				sum = 0; //��¼��һ�еķ������
				int k; 
				for(k = 1; k < COL - 1; k++)
				{
					sum += area.data[j - 1][k]; //ͳ����һ�еķ������
					area.data[j][k] = area.data[j - 1][k]; //����һ�з���ı�ʶ�Ƶ���һ��
					area.color[j][k] = area.color[j - 1][k]; //����һ�з������ɫ����Ƶ���һ��
					if(area.data[j][k] == 1) //��һ�����������Ƿ��飬��ӡ����
					{
						Gotoxy(2 * k, j); //�����ת����λ��
						color(area.color[j][k]); //��ɫ����Ϊ���������ɫ
						printf("��"); //��ӡ����
					}
					else //��һ�����������ǿո񣬴�ӡ�ո�
					{
						Gotoxy(2 * k, j); //�����ת����λ��
						printf("  "); //��ӡ�ո������ո�
					}
				}
				if (sum == 0) //��һ����������ȫ�ǿո������ٽ��ϲ�ķ��������ƶ����ƶ�������
					return 1; //����1����ʾ������øú��������жϣ��ƶ������Ŀ��ܻ������У�
			}
		}
	}
	IsGameOver();
	return 0; //�жϽ����������ٵ��øú��������ж�
}
//�ж��Ƿ���� 
void IsGameOver()
{
	int i; 
	for(i = 1; i < COL - 1; i++)
	{
		if(area.data[1][i] == 1) //�Ե�1��Ϊ���㣬���ǵ�0��
		{
			system("cls"); 
			color(7); 
			Gotoxy(2 * (COL / 3), ROW / 2 - 3);
			if(Record > Max)
			{
				printf("��ϲ�������߼�¼����߼�¼����Ϊ%d", Record);
				WriteRecord();
			}
			else if(Record == Max)
			{
				printf("����߼�¼��ƽ�������ٴ��Ѽ�", Record);
			}
			else
			{
				printf("��������ͣ���ǰ����߼�¼���%d", Max - Record);
			}
			Gotoxy(2 * (COL / 3), ROW / 2);
			printf("GAME OVER");
			while(1)
			{
				char ch;
				Gotoxy(2 * (COL / 3), ROW / 2 + 3);
				printf("����һ��?(y/n):");
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
					printf("ѡ��������ٴ�ѡ��");
				}
			}
		}
	}
}
//��ͣ���� 
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
	printf("��ͣ�У��밴���������...");
	system("pause>nul"); //��ͣ���������������
	Gotoxy(2, y);
	printf("                         ");
	for(i = 0; i < COL; i++)//���»��Ʊ������ĵط� 
	{
		if(d[i] == 1)
		{
			color(c[i]);
			Gotoxy(2 * i, y);
			printf("��");
		}
	}
} 
//��Ϸ������
void StartGame()
{
	int shape = rand() % 7, form = rand() % 4; //�����ȡ�������״����̬
	while(1)
	{
		int t = 0;                                         //�˴���Ҫ�ȸ�����һ���飬������ 
		int nextShape = rand() % 7, nextForm = rand() % 4; //�����ȡ��һ���������״����̬
		int x = (COL - 8) / 2 , y = 0;                     //�����ʼ����λ�õĺ�������
		color(nextShape);                                  //��ɫ����Ϊ��һ���������ɫ
		DrawBlock(nextShape, nextForm, COL + 3, 3);        //����һ��������ʾ�����Ͻ�
		while (1)
		{
			color(shape);                 //��ɫ����Ϊ��ǰ��������ķ���
			DrawBlock(shape, form, x, y); //���÷�����ʾ�ڳ�ʼ����λ��
			if(t == 0)
			{
				t = Speed;       //�涨����һ����ٶ� 
			}
			while(--t)           //���������--t����Ȼ֮��tһֱ�Ǹ��� 
			{
				if(kbhit() != 0) //����һ���ʱ��֮�ڽ������������������µ�ʱ�����Ժ��ԣ� 
					break;
			}
			if(t == 0)           //���δ���в��������߷����Ѿ������� 
			{
				if(IsLegal(shape, form, x, y + 1) == 0)//���ײ���������Ϸ����ͼ��״̬ 
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
				else //δ���ײ�
				{
					EraseBlock(shape, form, x, y); y++; //׼���ƶ�  
				}
			}
			else //�������������� 
			{
				char ch = getch();
				switch(ch)
				{
				case DOWN: //���������
					if(IsLegal(shape, form, x, y + 1) == 1) //�жϷ��������ƶ�һλ���Ƿ�Ϸ�
					{
						EraseBlock(shape, form, x, y); y += 2;
					}
					break;
				case LEFT: //���������
					if(IsLegal(shape, form, x - 1, y) == 1) //�жϷ��������ƶ�һλ���Ƿ�Ϸ�
					{
						EraseBlock(shape, form, x, y); x--; 
					}
					break;
				case RIGHT: //���������
					if(IsLegal(shape, form, x + 1, y) == 1) //�жϷ��������ƶ�һλ���Ƿ�Ϸ�
					{
						EraseBlock(shape, form, x, y); x++; 
					}
					break;
				case TAB: //�ո��
					if(IsLegal(shape, (form + 1) % 4, x, y + 1) == 1) //�жϷ�����ת���Ƿ�Ϸ�
					{
						EraseBlock(shape, form, x, y); 
						form = (form + 1) % 4; 
						y++;
					}
					break;
				case ESC: //Esc��
					system("cls"); 
					color(7);
					Gotoxy(COL, ROW / 2);
					printf("  ��Ϸ����  ");
					Gotoxy(COL, ROW / 2 + 2);
					exit(0); 
				case 's':
				case 'S':  
					SPause();
					break;
				case 'r':
				case 'R': 
					system("cls"); 
					main(); //������Ϸ 
				}
			}
		}
		shape = nextShape, form = nextForm; 
		EraseBlock(nextShape, nextForm, COL + 3, 3); //�����Ͻǵķ�����Ϣ�ÿո񸲸�
	}
}
//���ļ���ȡ��߷�
void ReadRecord()
{
	FILE* pf = fopen("����˹������ߵ÷ּ�¼.txt", "r"); 
	if (pf == NULL) //��û�д����ļ� 
	{
		pf = fopen("����˹������ߵ÷ּ�¼.txt", "w"); 
		fwrite(&Record, sizeof(int), 1, pf); //��maxд���ļ�����ʱmaxΪ0�������������ʷ�÷ֳ�ʼ��Ϊ0
	}
	fread(&Max, sizeof(int), 1, pf); //��ȡ�ļ��е������ʷ�÷ֵ�max����
	fclose(pf); 
	pf = NULL;
}
//������߷ֵ��ļ�
void WriteRecord()
{
	FILE* pf = fopen("����˹������ߵ÷ּ�¼.txt", "w"); 
	if (pf == NULL) 
	{
		printf("������ߵ÷ּ�¼ʧ��\n");
		exit(0);
	}
	fwrite(&Record, sizeof(int), 1, pf); //���������ʷ�÷�
	fclose(pf); 
	pf = NULL; 
}
