#include<iostream>
#include"gluttonous_snake.h"
#include <Windows.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

using namespace std;
int main()
{
	if (!PlaySound(L"music/backmusic.wav", NULL, SND_FILENAME | SND_ASYNC))
	{
		cout << "ÒôÀÖ´ò¿ªÊ§°Ü" << endl;
		return -1;
	}
	Game snake_game;
	snake_game.Top_control();
	return 0;
}