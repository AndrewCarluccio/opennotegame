#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../engine/DisplayObject.h"
#include <iostream>
#include "MyGame.h"
#include "dev_tool/DevTool.h"

#ifdef _WIN32
#include <windows.h>
#undef main

#ifdef __GNUC__
#define _stdcall  __attribute__((stdcall))
#endif


int main(int argc, char** argv)
{
	// comment out one of the following to choose between normal run and dev tool
	MyGame* myGame = new MyGame();
	// DevTool* myGame = new DevTool();
	myGame->start();
	

	delete myGame;
	return 0;
}

int _stdcall
WinMain(struct HINSTANCE__* hInstance,
	struct HINSTANCE__* hPrevInstance,
	char* lpszCmdLine,
	int                 nCmdShow)
{
	return main(__argc, __argv);
}

#else
int main(int argc, char** argv)
{
	// comment out one of the following to choose between normal run and dev tool
	
	MyGame* myGame = new MyGame();
	// DevTool* myGame = new DevTool();
	
	myGame->start();

	delete myGame;
	return 0;
}
#endif