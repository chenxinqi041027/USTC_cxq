#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")
int main(void)
{
	mciSendString("open bgm.mp3 alias bkmusic", NULL, 0, NULL);
	//openָ�����Ҫ���ŵ����֣�alias�����ƶ���ǰ���ļ�·���ı������Ժ���Ҫ��������ļ�ֱ��ʹ����������Ϳ�����.
	//��������ļ������ǵ�debug�ļ�����ͬһĿ¼�£��Ϳ���������������д·����ֱ����������
	//��������ļ��������������͵�д���·����
	//��: D���µ�demoĿ¼��һ����1.MP3���ļ�
	//mciSendString("open D:\\demo\\1.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);     //ѭ����������
	system("pause");
	return 0;
}
