#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>//��������ͷ�ļ�
#pragma comment(lib,"Winmm.lib")

int main(void)
{
    //printf("Hello world!\n");
    //��������
    PlaySound("BGM.mp3",NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
    system("pause");
    return 0;
}
