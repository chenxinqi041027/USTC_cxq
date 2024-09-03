#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define ROW 29 //��Ϸ������
#define COL 20 //��Ϸ������

#define DOWN 80 //���������
#define LEFT 75 //���������
#define RIGHT 77 //���������

#define SPACE 32 //�ո��
#define ESC 27 //Esc��

struct Face
{
	int data[ROW][COL + 10]; //���ڱ��ָ��λ���Ƿ��з��飨1Ϊ�У�0Ϊ�ޣ�
	int color[ROW][COL + 10]; //���ڼ�¼ָ��λ�õķ�����ɫ����
}face;

struct Block
{
	int space[4][4];
}block[7][4]; //���ڴ洢7�ֻ�����״����ĸ��Ե�4����̬����Ϣ����28��

//���ع��
void HideCursor();
//�����ת
void CursorJump(int x, int y);
//��ʼ������
void InitInterface();
//��ʼ��������Ϣ
void InitBlockInfo();
//��ɫ����
void color(int num);
//��������
void DrawBlock(int shape, int form, int x, int y);
//�ո񸲸�
void DrawSpace(int shape, int form, int x, int y);
//�Ϸ����ж�
int IsLegal(int shape, int form, int x, int y);
//�жϵ÷������
int JudeFunc();
//��Ϸ�����߼�����
void StartGame();
//���ļ���ȡ��߷�
void ReadGrade();
//������߷ֵ��ļ�
void WriteGrade();

int max, grade; //ȫ�ֱ���
int main()
{
#pragma warning (disable:4996) //��������
	max = 0, grade = 0; //��ʼ������
	system("title ����˹����"); //����cmd���ڵ�����
	system("mode con lines=29 cols=60"); //����cmd���ڵĴ�С
	HideCursor(); //���ع��
	ReadGrade(); //���ļ���ȡ��߷ֵ�max����	
	InitInterface(); //��ʼ������
	InitBlockInfo(); //��ʼ��������Ϣ
	srand((unsigned int)time(NULL)); //������������ɵ����
	StartGame(); //��ʼ��Ϸ
	return 0;
}

//���ع��
void HideCursor()
{
	CONSOLE_CURSOR_INFO curInfo; //��������Ϣ�Ľṹ�����
	curInfo.dwSize = 1;  //���û��ֵ�Ļ������ع����Ч
	curInfo.bVisible = FALSE; //���������Ϊ���ɼ�
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ����̨���
	SetConsoleCursorInfo(handle, &curInfo); //���ù����Ϣ
}
//�����ת
void CursorJump(int x, int y)
{
	COORD pos; //������λ�õĽṹ�����
	pos.X = x; //����������
	pos.Y = y; //����������
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ����̨���
	SetConsoleCursorPosition(handle, pos); //���ù��λ��
}
//��ʼ������
void InitInterface()
{
	color(7); //��ɫ����Ϊ��ɫ
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL + 10; j++)
		{
			if (j == 0 || j == COL - 1 || j == COL + 9)
			{
				face.data[i][j] = 1; //��Ǹ�λ���з���
				CursorJump(2 * j, i);
				printf("��");
			}
			else if (i == ROW - 1)
			{
				face.data[i][j] = 1; //��Ǹ�λ���з���
				printf("��");
			}
			else
				face.data[i][j] = 0; //��Ǹ�λ���޷���
		}
	}
	for (int i = COL; i < COL + 10; i++)
	{
		face.data[8][i] = 1; //��Ǹ�λ���з���
		CursorJump(2 * i, 8);
		printf("��");
	}

	CursorJump(2 * COL, 1);
	printf("��һ�����飺");

	CursorJump(2 * COL + 4, ROW - 19);
	printf("���ƣ���");

	CursorJump(2 * COL + 4, ROW - 17);
	printf("���ƣ���");

	CursorJump(2 * COL + 4, ROW - 15);
	printf("���٣���");

	CursorJump(2 * COL + 4, ROW - 13);
	printf("��ת���ո�");

	CursorJump(2 * COL + 4, ROW - 11);
	printf("��ͣ: S");

	CursorJump(2 * COL + 4, ROW - 9);
	printf("�˳�: Esc");

	CursorJump(2 * COL + 4, ROW - 7);
	printf("���¿�ʼ:R");

	CursorJump(2 * COL + 4, ROW - 5);
	printf("��߼�¼:%d", max);

	CursorJump(2 * COL + 4, ROW - 3);
	printf("��ǰ������%d", grade);
}
//��ʼ��������Ϣ
void InitBlockInfo()
{
	//��T����
	for (int i = 0; i <= 2; i++)
		block[0][0].space[1][i] = 1;
	block[0][0].space[2][1] = 1;

	//��L����
	for (int i = 1; i <= 3; i++)
		block[1][0].space[i][1] = 1;
	block[1][0].space[3][2] = 1;

	//��J����
	for (int i = 1; i <= 3; i++)
		block[2][0].space[i][2] = 1;
	block[2][0].space[3][1] = 1;

	for (int i = 0; i <= 1; i++)
	{
		//��Z����
		block[3][0].space[1][i] = 1;
		block[3][0].space[2][i + 1] = 1;
		//��S����
		block[4][0].space[1][i + 1] = 1;
		block[4][0].space[2][i] = 1;
		//��O����
		block[5][0].space[1][i + 1] = 1;
		block[5][0].space[2][i + 1] = 1;
	}

	//��I����
	for (int i = 0; i <= 3; i++)
		block[6][0].space[i][1] = 1;

	int temp[4][4];
	for (int shape = 0; shape < 7; shape++) //7����״
	{
		for (int form = 0; form < 3; form++) //4����̬���Ѿ�����һ�֣�����ÿ����������3�֣�
		{
			//��ȡ��form����̬
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					temp[i][j] = block[shape][form].space[i][j];
				}
			}
			//����form����̬˳ʱ����ת���õ���form+1����̬
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
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
		c = 13; //��T���η�������Ϊ��ɫ
		break;
	case 1:
	case 2:
		c = 12; //��L���κ͡�J���η�������Ϊ��ɫ
		break;
	case 3:
	case 4:
		c = 10; //��Z���κ͡�S���η�������Ϊ��ɫ
		break;
	case 5:
		c = 14; //��O���η�������Ϊ��ɫ
		break;
	case 6:
		c = 11; //��I���η�������Ϊǳ��ɫ
		break;
	default:
		c = 7; //����Ĭ������Ϊ��ɫ
		break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); //��ɫ����
	//ע��SetConsoleTextAttribute��һ��API��Ӧ�ó����̽ӿڣ�
}
//��������
void DrawBlock(int shape, int form, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[shape][form].space[i][j] == 1) //�����λ���з���
			{
				CursorJump(2 * (x + j), y + i); //�����ת��ָ��λ��
				printf("��"); //�������
			}
		}
	}
}
//�ո񸲸�
void DrawSpace(int shape, int form, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[shape][form].space[i][j] == 1) //�����λ���з���
			{
				CursorJump(2 * (x + j), y + i); //�����ת��ָ��λ��
				printf("  "); //��ӡ�ո񸲸ǣ������ո�
			}
		}
	}
}
//�Ϸ����ж�
int IsLegal(int shape, int form, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//����������µ�λ�ñ������Ѿ��з����ˣ��򲻺Ϸ�
			if ((block[shape][form].space[i][j] == 1) && (face.data[y + i][x + j] == 1))
				return 0; //���Ϸ�
		}
	}
	return 1; //�Ϸ�
}
//�жϵ÷������
int JudeFunc()
{
	//�ж��Ƿ�÷�
	for (int i = ROW - 2; i > 4; i--)
	{
		int sum = 0; //��¼��i�еķ������
		for (int j = 1; j < COL - 1; j++)
		{
			sum += face.data[i][j]; //ͳ�Ƶ�i�еķ������
		}
		if (sum == 0) //����û�з��飬�������ж����ϵĲ�Σ������ټ����ж��Ƿ�÷֣�
			break; //����ѭ��
		if (sum == COL - 2) //����ȫ�Ƿ��飬�ɵ÷�
		{
			grade += 10; //��һ�м�10��
			color(7); //��ɫ����Ϊ��ɫ
			CursorJump(2 * COL + 4, ROW - 3); //�����ת����ʾ��ǰ������λ��
			printf("��ǰ������%d", grade); //���µ�ǰ����
			for (int j = 1; j < COL - 1; j++) //����÷��еķ�����Ϣ
			{
				face.data[i][j] = 0; //��λ�õ÷ֺ���������Ϊ�޷���
				CursorJump(2 * j, i); //�����ת����λ��
				printf("  "); //��ӡ�ո񸲸ǣ������ո�
			}
			//�ѱ���������������������Ųһ��
			for (int m = i; m >1; m--)
			{
				sum = 0; //��¼��һ�еķ������
				for (int n = 1; n < COL - 1; n++)
				{
					sum += face.data[m - 1][n]; //ͳ����һ�еķ������
					face.data[m][n] = face.data[m - 1][n]; //����һ�з���ı�ʶ�Ƶ���һ��
					face.color[m][n] = face.color[m - 1][n]; //����һ�з������ɫ����Ƶ���һ��
					if (face.data[m][n] == 1) //��һ�����������Ƿ��飬��ӡ����
					{
						CursorJump(2 * n, m); //�����ת����λ��
						color(face.color[m][n]); //��ɫ����Ϊ���������ɫ
						printf("��"); //��ӡ����
					}
					else //��һ�����������ǿո񣬴�ӡ�ո�
					{
						CursorJump(2 * n, m); //�����ת����λ��
						printf("  "); //��ӡ�ո������ո�
					}
				}
				if (sum == 0) //��һ����������ȫ�ǿո������ٽ��ϲ�ķ��������ƶ����ƶ�������
					return 1; //����1����ʾ������øú��������жϣ��ƶ������Ŀ��ܻ������У�
			}
		}
	}
	//�ж���Ϸ�Ƿ����
	for (int j = 1; j < COL - 1; j++)
	{
		if (face.data[1][j] == 1) //�����з�����ڣ��Ե�1��Ϊ���㣬���ǵ�0�У�
		{
			Sleep(1000); //������ҷ�Ӧʱ��
			system("cls"); //�����Ļ
			color(7); //��ɫ����Ϊ��ɫ
			CursorJump(2 * (COL / 3), ROW / 2 - 3);
			if (grade>max)
			{
				printf("��ϲ�������߼�¼����߼�¼����Ϊ%d", grade);
				WriteGrade();
			}
			else if (grade == max)
			{
				printf("����߼�¼��ƽ�������ٴ��Ѽ�", grade);
			}
			else
			{
				printf("��������ͣ���ǰ����߼�¼���%d", max - grade);
			}
			CursorJump(2 * (COL / 3), ROW / 2);
			printf("GAME OVER");
			while (1)
			{
				char ch;
				CursorJump(2 * (COL / 3), ROW / 2 + 3);
				printf("����һ��?(y/n):");
				scanf("%c", &ch);
				if (ch == 'y' || ch == 'Y')
				{
					system("cls");
					main();
				}
				else if (ch == 'n' || ch == 'N')
				{
					CursorJump(2 * (COL / 3), ROW / 2 + 5);
					exit(0);
				}
				else
				{
					CursorJump(2 * (COL / 3), ROW / 2 + 4);
					printf("ѡ��������ٴ�ѡ��");
				}
			}
		}
	}
	return 0; //�жϽ����������ٵ��øú��������ж�
}
//��Ϸ�����߼�����
void StartGame()
{
	int shape = rand() % 7, form = rand() % 4; //�����ȡ�������״����̬
	while (1)
	{
		int t = 0;
		int nextShape = rand() % 7, nextForm = rand() % 4; //�����ȡ��һ���������״����̬
		int x = COL / 2 - 2, y = 0; //�����ʼ����λ�õĺ�������
		color(nextShape); //��ɫ����Ϊ��һ���������ɫ
		DrawBlock(nextShape, nextForm, COL + 3, 3); //����һ��������ʾ�����Ͻ�
		while (1)
		{
			color(shape); //��ɫ����Ϊ��ǰ��������ķ���
			DrawBlock(shape, form, x, y); //���÷�����ʾ�ڳ�ʼ����λ��
			if (t == 0)
			{
				t = 15000; //����tԽС����������Խ�죨���Ը��ݴ�������Ϸ�Ѷȣ�
			}
			while (--t)
			{
				if (kbhit() != 0) //�����̱��û������˳�ѭ��
					break;
			}
			if (t == 0) //����δ���û�
			{
				if (IsLegal(shape, form, x, y + 1) == 0) //����������Ͳ��Ϸ��ˣ��Ѿ�����ײ���
				{
					//����ǰ�������Ϣ¼��face����
					//face:��¼�����ÿ��λ���Ƿ��з��飬���з��黹���¼��λ�÷������ɫ��
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 4; j++)
						{
							if (block[shape][form].space[i][j] == 1)
							{
								face.data[y + i][x + j] = 1; //����λ�ñ��Ϊ�з���
								face.color[y + i][x + j] = shape; //��¼�÷������ɫ��ֵ
							}
						}
					}
					while (JudeFunc()); //�жϴ˴η��������Ƿ�÷��Լ���Ϸ�Ƿ����
					break; //������ǰ��ѭ����׼��������һ�����������
				}
				else //δ���ײ�
				{
					DrawSpace(shape, form, x, y); //�ÿո񸲸ǵ�ǰ��������λ��
					y++; //��������������һ����ʾ����ʱ���൱��������һ���ˣ�
				}
			}
			else //���̱��û�
			{
				char ch = getch(); //��ȡkeycode
				switch (ch)
				{
				case DOWN: //���������
					if (IsLegal(shape, form, x, y + 1) == 1) //�жϷ��������ƶ�һλ���Ƿ�Ϸ�
					{
						//���������Ϸ��Ž������²���
						DrawSpace(shape, form, x, y); //�ÿո񸲸ǵ�ǰ��������λ��
						y++; //��������������һ����ʾ����ʱ���൱��������һ���ˣ�
					}
					break;
				case LEFT: //���������
					if (IsLegal(shape, form, x - 1, y) == 1) //�жϷ��������ƶ�һλ���Ƿ�Ϸ�
					{
						//�������ƺ�Ϸ��Ž������²���
						DrawSpace(shape, form, x, y); //�ÿո񸲸ǵ�ǰ��������λ��
						x--; //�������Լ�����һ����ʾ����ʱ���൱��������һ���ˣ�
					}
					break;
				case RIGHT: //���������
					if (IsLegal(shape, form, x + 1, y) == 1) //�жϷ��������ƶ�һλ���Ƿ�Ϸ�
					{
						//�������ƺ�Ϸ��Ž������²���
						DrawSpace(shape, form, x, y); //�ÿո񸲸ǵ�ǰ��������λ��
						x++; //��������������һ����ʾ����ʱ���൱��������һ���ˣ�
					}
					break;
				case SPACE: //�ո��
					if (IsLegal(shape, (form + 1) % 4, x, y + 1) == 1) //�жϷ�����ת���Ƿ�Ϸ�
					{
						//������ת��Ϸ��Ž������²���
						DrawSpace(shape, form, x, y); //�ÿո񸲸ǵ�ǰ��������λ��
						y++; //�������������ܲ���ԭ����ת�ɣ�
						form = (form + 1) % 4; //�������̬��������һ����ʾ����ʱ���൱����ת�ˣ�
					}
					break;
				case ESC: //Esc��
					system("cls"); //�����Ļ
					color(7);
					CursorJump(COL, ROW / 2);
					printf("  ��Ϸ����  ");
					CursorJump(COL, ROW / 2 + 2);
					exit(0); //��������
				case 's':
				case 'S':  //��ͣ
					system("pause>nul"); //��ͣ���������������
					break;
				case 'r':
				case 'R': //���¿�ʼ
					system("cls"); //�����Ļ
					main(); //����ִ��������
				}
			}
		}
		shape = nextShape, form = nextForm; //��ȡ��һ���������Ϣ
		DrawSpace(nextShape, nextForm, COL + 3, 3); //�����Ͻǵķ�����Ϣ�ÿո񸲸�
	}
}
//���ļ���ȡ��߷�
void ReadGrade()
{
	FILE* pf = fopen("����˹������ߵ÷ּ�¼.txt", "r"); //��ֻ����ʽ���ļ�
	if (pf == NULL) //���ļ�ʧ��
	{
		pf = fopen("����˹������ߵ÷ּ�¼.txt", "w"); //��ֻд��ʽ���ļ����ļ������ڿ����Զ��������ļ���
		fwrite(&grade, sizeof(int), 1, pf); //��maxд���ļ�����ʱmaxΪ0�������������ʷ�÷ֳ�ʼ��Ϊ0
	}
	fseek(pf, 0, SEEK_SET); //ʹ�ļ�ָ��pfָ���ļ���ͷ
	fread(&max, sizeof(int), 1, pf); //��ȡ�ļ��е������ʷ�÷ֵ�max����
	fclose(pf); //�ر��ļ�
	pf = NULL; //�ļ�ָ�뼰ʱ�ÿ�
}
//������߷ֵ��ļ�
void WriteGrade()
{
	FILE* pf = fopen("����˹������ߵ÷ּ�¼.txt", "w"); //��ֻд��ʽ���ļ�
	if (pf == NULL) //���ļ�ʧ��
	{
		printf("������ߵ÷ּ�¼ʧ��\n");
		exit(0);
	}
	fwrite(&grade, sizeof(int), 1, pf); //��������Ϸ�÷�д���ļ����У����������ʷ�÷֣�
	fclose(pf); //�ر��ļ�
	pf = NULL; //�ļ�ָ�뼰ʱ�ÿ�
}
