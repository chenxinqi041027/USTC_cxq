#include<graphics.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>	//kbhit()
 
int score = 0;	//�ܷ�
int rank = 0;	//�ȼ�
 
#define BLOCK_COUNT 5
#define BLOCK_WIDTH 5
#define BLOCK_HEIGHT 5
 
#define UNIT_SIZE 20	//С������
 
#define START_X 130		//���齵��򣬷��齵����ʼλ��
#define START_Y 30
 
#define KEY_UP 87		//�û�����
#define KEY_LEFT 65
#define KEY_RIGHT 68
#define KEY_DOWN 83
#define KEY_SPACE 32
 
#define MinX 30		//��Ϸ���Ͻ�λ��
#define MinY 30
int speed = 500;	//���齵���ٶ�
 
 
int NextIndex = -1;		//��һ������
int BlockIndex = -1;		//��ǰ����
 
typedef enum {		//���鳯��
	BLOCK_UP,
	BLOCK_RIGHT,
	BLOCK_LEFT,
	BLOCK_DOWN
}block_dir_t;
 
typedef enum {		//�����ƶ�����
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT
}move_dir_t;
 
//������ɫ
int color[BLOCK_COUNT] = {
	GREEN,
	CYAN,
	MAGENTA,
	YELLOW,
	BROWN
};
int visit[30][15];	//��������visit[i][j] = 1��ʾ��λ���з���
int markColor[30][15];	//��Ӧλ����ɫ
int block[BLOCK_COUNT * 4][BLOCK_WIDTH][BLOCK_HEIGHT] = {
	// | �η���
	{ 0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0 },
	 // L �η���
	{ 0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0 },
	// �� �η���
	{ 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	// T �η���
	{ 0,0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0 },
	// Z �η���
	{ 0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0 },
};
 
/***************************
 * ���ܣ���ӭҳ��
 * ���룺
 *		��
 * ���أ�
 *		��
 **************************/
void welcome() {
	//1.��ʼ������
	initgraph(550, 660);
	//2.���ô��ڱ���
	HWND window = GetHWnd();//��ô��ڣ���õ�ǰ����
	SetWindowText(window, _T("����˹����  С�����"));	//���ñ���
 
	//3.������Ϸ��ʼҳ��
	setfont(40, 0, _T("΢���ź�"));		//�����ı���������ʽ(�ߣ���0��ʾ����Ӧ�������壩
	setcolor(WHITE);	// ������ɫ
	outtextxy(205, 200, _T("����˹����"));
 
	setfont(20, 0, _T("����"));
	setcolor(WHITE);	// ������ɫ
	outtextxy(175, 300, _T("��̣��Ӷ���˹���鿪ʼ"));
 
	Sleep(3000);
}
 
/***************************
 * ���ܣ���ʼ����Ϸ����
 * ���룺
 *		��
 * ���أ�
 *		��
 **************************/
void initGameSceen() {
	char str[16];	//��ŷ���
	//1.����
	cleardevice();
	//2.������
	rectangle(27, 27, 336, 635);	//���齵������
	rectangle(29, 29, 334, 633);	//���齵����ڿ�
	rectangle(370, 50, 515, 195);	//������ʾ��
 
	setfont(24, 0, _T("����"));		//д����һ����
	setcolor(LIGHTGRAY);	//��ɫ
	outtextxy(405, 215, _T("��һ����"));
 
	setcolor(RED);					//д����
	outtextxy(405, 280, _T("������"));
 
	//��ָ����ʽ����scoreд��str
	sprintf_s(str, 16, "%d", score);
	//���������ַ���Ϊ���ַ�����֤outtextxy����д������str
	outtextxy(415, 310, str);
 
	outtextxy(405, 375, _T("�ȼ���"));	//�ȼ�
 
	//��ָ����ʽ����rankд��str
	sprintf_s(str, 16, "%d", rank);
	//���������ַ���Ϊ���ַ�����֤outtextxy����д������str
	outtextxy(415, 405, str);
 
	setcolor(LIGHTBLUE);	//����˵��
	outtextxy(390, 475, "����˵��:");
	outtextxy(390, 500, "��: ��ת");
	outtextxy(390, 525, "��: �½�");
	outtextxy(390, 550, "��: ����");
	outtextxy(390, 575, "��: ����");
	outtextxy(390, 600, "�ո�: ��ͣ");
}
 
/*****************************************
 * ���ܣ���շ�����ʾ����ķ���
 * ���룺
 *		��
 * ���أ�
 *		��
 ****************************************/
void clearBlock() {
	setcolor(BLACK);
	setfont(23, 0, "����");
	for (int i = 0; i < BLOCK_HEIGHT; ++i) {
		for (int j = 0; j < BLOCK_WIDTH; ++j) {
			int x = 391 + j * UNIT_SIZE;
			int y = 71 + i * UNIT_SIZE;
			outtextxy(x, y, "��");
		}
	}
}
 
/*****************************************
 * ���ܣ������������еķ���
 * ���룺
 *		x,y - ��������꣨��ά�������Ͻ�λ�ã�
 *		block_dir_t - ���鷽��
 * ���أ�
 *		��
 ****************************************/
void clearBlock(int x, int y, block_dir_t blockDir) {
	setcolor(BLACK);
	//	setfont(23, 0, "����");
	int id = BlockIndex * 4 + blockDir;
	for (int i = 0; i < BLOCK_HEIGHT; ++i) {
		for (int j = 0; j < BLOCK_WIDTH; ++j) {
			if (block[id][i][j] == 1) {
				int x2 = x + j * UNIT_SIZE;
				int y2 = y + i * UNIT_SIZE;
				outtextxy(x2, y2, "��");
			}
		}
	}
}
 
/*****************************************
 * ���ܣ�����ʾ�� �� ��������ʼλ�û�����
 * ���룺
 *		x,y - ��������꣨��ά�������Ͻ�λ�ã�
 * ���أ�
 *		��
 ****************************************/
void drawBlock(int x, int y) {
	setcolor(color[NextIndex]);
	setfont(23, 0, "����");
	for (int i = 0; i < BLOCK_HEIGHT; ++i) {
		for (int j = 0; j < BLOCK_WIDTH; ++j) {
			if (block[NextIndex * 4][i][j] == 1) {
				int x2 = x + j * UNIT_SIZE;
				int y2 = y + i * UNIT_SIZE;
				outtextxy(x2, y2, "��");
			}
		}
	}
}
 
/*****************************************
 *���ܣ������½������еķ���
 *���룺
 *		x,y - ��������꣨��ά�������Ͻ�λ�ã�
 *		block_dir_t - ���鷽��
 * ���أ�
 *		��
 ****************************************/
void drawBlock(int x, int y, block_dir_t dir) {
	setcolor(color[BlockIndex]);
	setfont(23, 0, "����");
	int id = BlockIndex * 4 + dir;
	for (int i = 0; i < BLOCK_HEIGHT; ++i) {
		for (int j = 0; j < BLOCK_WIDTH; ++j) {
			if (block[id][i][j] == 1) {
				//�����÷���ĵ�i�е�j��
				outtextxy(x + j * UNIT_SIZE, y + i * UNIT_SIZE, "��");
			}
		}
	}
}
 
/*****************************************
 *���ܣ�������ʾ���в����·���
 *���룺
 *		��
 *���أ�
 *		��
 ****************************************/
void nextblock() {
	clearBlock();
	//��������������ѡ�񷽿�
	srand((unsigned)time(NULL));	//ʹ��ʱ�亯���ķ���ֵ������Ϊ�������
	NextIndex = rand() % BLOCK_COUNT;	//����0~5�������
	drawBlock(391, 71);
}
 
 /*****************************************
  *���ܣ��ж���ָ��λ����ָ�������Ƿ�����ƶ�
  *���룺
  *		x��y - ����λ��
  *		moveDir - ��һ����Ҫ�ƶ��ķ���
  *		blockDir - ��ǰ����ķ���
  * ���أ�
  *		true - �����ƶ�
  *		false - �������ƶ�
  ****************************************/
bool moveable(int x0, int y0, move_dir_t moveDir, block_dir_t blockDir) {
	//���㷽�����Ͻ���30��15����Ϸ��λ�ã��ڶ����У� �ڶ����У�
	int x = (y0 - MinY) / UNIT_SIZE;
	int y = (x0 - MinX) / UNIT_SIZE;
	int ret = 1;
	int id = BlockIndex * 4 + blockDir;
	if (moveDir == MOVE_DOWN) {
		for (int i = 0; i < BLOCK_HEIGHT; ++i) {
			for (int j = 0; j < BLOCK_WIDTH; ++j) {
				//���²����˶���������ʵ�ķ����Ѿ��ﵽ�ײ���x+i+1==30�������ߵײ����з���	
				if (block[id][i][j] == 1 &&
					(x + i + 1 == 30 || visit[x + i + 1][y + j] == 1)) {
					ret = 0;
				}
			}
		}
	}
	else if (moveDir == MOVE_LEFT) {
		for (int i = 0; i < BLOCK_HEIGHT; ++i) {
			for (int j = 0; j < BLOCK_WIDTH; ++j) {
				//�������˶���������ʵ�ķ����Ѿ��ﵽ��߽�(y+j==0),����������з���
				if (block[id][i][j] == 1 &&
					(y + j <= 0 || visit[x + i][y + j - 1] == 1)) {
					ret = 0;
				}
			}
		}
	}
	else if (moveDir == MOVE_RIGHT) {
		for (int i = 0; i < BLOCK_HEIGHT; ++i) {
			for (int j = 0; j < BLOCK_WIDTH; ++j) {
				//���²����˶���������ʵ�ķ����Ѿ��ﵽ�ұ߽磨y+j+1>=15)�������ұ����з���
				if (block[id][i][j] == 1 &&
					(y + j + 1 >= 15 || visit[x + i][y + j + 1] == 1)) {
					ret = 0;
				}
			}
		}
	}
	return ret;
}
 
/*****************************
 *���ܣ������Ϸ�Ƿ����
 *���룺
 *		��
 * ���أ�
 *		��
 *****************************/
void failCheck() {
	//��Ϸ���������Ƕ����±����Ƴ��ķ����Ҫ���̻����������»��Ƶķ��鷽���ϣ��˶�������
	if (!moveable(START_X, START_Y, MOVE_DOWN, (block_dir_t)BLOCK_UP)) {
		setcolor(WHITE);
		setfont(45, 0, "����");
		outtextxy(75, 300, "Game Over��");
		Sleep(1000);
		system("pause");
		closegraph();
		exit(0);
	}
}
 
/**************************
 * ���ܣ���ʱ�ȴ�
 * ���룺
 *
 * ���أ�
 *		��
 *************************/
void wait(int interval) {
	int count = interval / 10;
	for (int i = 0; i < count; ++i) {
		Sleep(10);
		//��������ڼ��û��а��������������
		if (_kbhit()) {
			return;
		}
	}
}
 
/*****************************************
 * ���ܣ��жϵ�ǰ�����Ƿ������ָ��������ת
 * ���룺
 *		x��y - ����λ�ã���ά�������꣩
 *		dir - ������ת����
 * ���أ�
 *		true - ������ת
 *		false - ��������ת
 ****************************************/
bool rotatable(int x, int y, block_dir_t dir) {
	//�����ж��Ƿ���Լ��������ƶ�
	if (!moveable(x, y, MOVE_DOWN, dir)) {
		return false;
	}
	int x2 = (y - MinY) / UNIT_SIZE;
	int y2 = (x - MinX) / UNIT_SIZE;
	int id = BlockIndex * 4 + dir;
	for (int i = 0; i < BLOCK_HEIGHT; ++i) {
		for (int j = 0; j < BLOCK_WIDTH; ++j) {
			//������ת���������ұ߽�Խ��������з��顰�赲��
			if (block[id][i][j] == 1 && (y2 + j < 0 || y2 + j >= 15 || visit[x2 + i][y2 + j] == 1)) {
				return false;
			}
		}
	}
	return true;
}
 
/*****************************************
 * ���ܣ�
 * ���룺
 *
 * ���أ�
 *		��
 ****************************************/
void mark(int x, int y, block_dir_t dir) {
	int id = BlockIndex * 4 + dir;
	int x2 = (y - MinY) / UNIT_SIZE;
	int y2 = (x - MinX) / UNIT_SIZE;
	for (int i = 0; i < BLOCK_HEIGHT; ++i) {
		for (int j = 0; j < BLOCK_WIDTH; ++j) {
			if (block[id][i][j] == 1) {
				visit[x2 + i][y2 + j] = 1;
				markColor[x2 + i][y2 + j] = color[BlockIndex];
			}
		}
	}
}
 
/*****************************************
 * ���ܣ���ȡ�û�������ʱʱ���½���ķ���
 * ���룺
 *		��
 * ���أ�
 *		��
 ****************************************/
void move() {
	int x = START_X;	//������ʼλ��
	int y = START_Y;
	int k = 0;
	block_dir_t blockDir = (block_dir_t)BLOCK_UP;
	int curSpeed = speed;	//���嵱ǰ���齵���ٶ�
	//��ȡ�û�����ǰ�ж���Ϸ�Ƿ����
	failCheck();
	//�������½���
	while (1) {
		int curSpeed = speed;	//���嵱ǰ���齵���ٶ�
		//�������
		clearBlock(x, k + y, blockDir);
		//�ж�ѡ��ķ���
		if (_kbhit()) {
			int key = _getch();
			if (key == KEY_SPACE) {
				system("pause");
			}
			else if (key == KEY_UP) {
				block_dir_t nextDir = (block_dir_t)((blockDir + 1) % 4);
				if (rotatable(x, y + k, nextDir)) {
					blockDir = nextDir;
				}
			}
			else if (key == KEY_LEFT) {
				if (moveable(x, y + k + 20, MOVE_LEFT, blockDir)) {
					x -= UNIT_SIZE;
				}
			}
			else if (key == KEY_RIGHT) {
				if (moveable(x, y + k + 20, MOVE_RIGHT, blockDir)) {
					x += UNIT_SIZE;
				}
			}
			else if (key == KEY_DOWN) {
				curSpeed = 50;
			}
		}
		k += 20;
		//���Ʒ���
		drawBlock(x, y + k, blockDir);
		//����
		wait(curSpeed);
		//����Ĺ̻���������̶������ѭ������ǰһ�������moveִ�����
		if (!moveable(x, y + k, MOVE_DOWN, blockDir)) {
			mark(x, y + k, blockDir);
			break;
		}
	}
}
 
/*****************************************
 *���ܣ����ƸմӶ�������ķ��飬������ʾ���ڵķ��飬���÷��齵�亯��move()
 *���룺
 *		��
 * ���أ�
 *		��
 ****************************************/
void newblock() {
	BlockIndex = NextIndex;
	//���ƸմӶ����½��ķ���
	drawBlock(START_X, START_Y);
	//���³��ַ�����ͣһ��
	Sleep(200);
	//���Ͻ����������һ������
	nextblock();
	//���齵��
	move();
}
 
/*****************************************
 * ���ܣ�������i�У�����������ж�������
 * ���룺
 *		��
 * ���أ�
 *		��
 ****************************************/
void down(int x) {
	for (int i = x; i > 0; --i) {
		for (int j = 0; j < 15; ++j) {
			if (visit[i - 1][j] == 1) {
				visit[i][j] = 1;
				markColor[i][j] = markColor[i - 1][j];
				setcolor(markColor[i][j]);
				outtextxy(20 * j + MinX, 20 * i + MinY, "��");
			}
			else {
				visit[i][j] = 0;
				setcolor(BLACK);
				outtextxy(20 * j + MinX, 20 * i + MinY, "��");
			}
		}
	}
	//�����㷽��
	setcolor(BLACK);
	for (int j = 0; j < 15; ++j) {
		visit[0][j] = 0;
		outtextxy(20 * j + MinX, MinY, "��");
	}
}
 
/*****************************************
 * ���ܣ����·���
 * ���룺
 *		��
 * ���أ�
 *		��
 ****************************************/
void addScore(int lines) {
	char str[32];
	score += lines * 10;
	sprintf_s(str, 32, "%d", score);
	setcolor(RED);
	outtextxy(415, 310, str);
 
}
 
/*************************
 * ���ܣ����µȼ�
 * ���룺
 *		��
 * ���أ�
 *		��
 *************************/
void updateGrade() {
	//���µȼ�
	//����50��һ��
	rank = score / 50;
	char str[32];
	sprintf_s(str, 32, "%d", rank);
	setcolor(RED);
	outtextxy(415, 405, str);
	//�����ٶ�
	if (speed <= 100) {
		speed = 100;
	}
	else {
		speed = 500 - rank * 20;
	}
}
 
/*************************
 * ���ܣ�����Ƿ������з���
 * ���룺
 *		��
 * ���أ�
 *		��
 *************************/
void check() {
	int i, j;
	int clearLines = 0;
	for (i = 29; i >= 0; i--) {
		// ����i����û����
		for (j = 0; j < 15 && visit[i][j]; j++);
		//ִ�е��˴�ʱ�������������
		// 1. ��i��û����������ʾ�п�λ ��ʱ j<15
		// 2. ��i�������ˣ���ʱ j>=15
		if (j >= 15) {
			// ��ʱ����i���Ѿ����ˣ�����Ҫ������i��
			down(i);  //������i�У�����������ж�����
			i++;  // ��Ϊ������ѭ������ i--, ����������i++, ʹ���´�ѭ��ʱ���ٰ���һ�м��һ��
			clearLines++;
		}
	}
	// ���·���
	addScore(clearLines);
 
	// ���µȼ�(���µȼ���ʾ�������ٶȣ�
	updateGrade();
}
 
int main() {
	welcome();
	initGameSceen();
	//�����·���
	nextblock();
	//	system("pause");
	Sleep(800);
 
	//��ʼ����������
	memset(visit, 0, sizeof(visit));
 
	while (1) {
		newblock();
		//�������У������·������ٶ�
		check();
	}
	system("pause");
	closegraph();
	return 0;
}
