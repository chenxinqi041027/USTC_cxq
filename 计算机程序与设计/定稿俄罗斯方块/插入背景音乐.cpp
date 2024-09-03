#include<stdio.h> 
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment (lib,"winmm.lib")

int main()
{
    mciSendString("open C:\\bgm.mp3 alias bkmusic", NULL, 0, NULL);
    mciSendString("play bkmusic repeat", NULL, 0, NULL);
    printf("hello");
    return 0;
}
