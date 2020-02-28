#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include "Camera.h"
#include <vector>
#include <set>

using namespace std;

class Game : public DisplayObjectContainer {

public:

	/* Singleton pattern */
	static Game* instance;

	int frames_per_sec = 60;
	int windowWidth, windowHeight;

	SDL_Window * window;
	static SDL_Renderer* renderer;

	//Global frame counter
	static unsigned int frameCounter;
	bool mousePressedDown = false;
	bool initialClick = false;
	bool initialRelease = false;
	bool keyPressed = false;
	int mouseX;
	int mouseY;

	Game(int windowWidth, int windowHeight);
	virtual ~Game();
	void start();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	//virtual void draw(AffineTransform &at, Camera* cam);

private:

	void initSDL();
	void quitSDL();
	set<SDL_Scancode> pressedKeys;
	
};

#endif