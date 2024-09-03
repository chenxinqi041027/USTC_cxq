#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>//导入声音头文件
#pragma comment(lib,"Winmm.lib")

int main(void)
{
    //printf("Hello world!\n");
    //播放音乐
    PlaySound("BGM.mp3",NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
    system("pause");
    return 0;
}
