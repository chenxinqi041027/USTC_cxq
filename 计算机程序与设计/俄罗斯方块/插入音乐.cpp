#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")
int main(void)
{
	mciSendString("open bgm.mp3 alias bkmusic", NULL, 0, NULL);
	//open指令打开需要播放的音乐，alias后面制定了前面文件路径的别名，以后想要操作这个文件直接使用这个别名就可以了.
	//如果音乐文件和我们的debug文件夹在同一目录下，就可以像我这样不用写路径，直接音乐名。
	//如果音乐文件不是上面的情况就得写清楚路径。
	//例: D盘下的demo目录有一个叫1.MP3的文件
	//mciSendString("open D:\\demo\\1.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);     //循环播放音乐
	system("pause");
	return 0;
}
