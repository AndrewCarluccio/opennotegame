#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include "Camera.h"
#include "CollisionSystem.h"
#include "GameState.h"
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

	TTF_Font *font;

	//Global frame counter
	static unsigned int frameCounter;
	bool mousePressedDown = false;
	bool initialClick = false;
	bool initialRelease = false;
	bool keyPressed = false;
	int prevMouseX;
	int prevMouseY;
	int mouseX;
	int mouseY;
	int mouseMotionX;
	int mouseMotionY;

	Game(int windowWidth, int windowHeight);
	virtual ~Game();
	void start();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	//virtual void draw(AffineTransform &at, Camera* cam);

	CollisionSystem collisionSystem;
	GameState gameState;

private:

	void initSDL();
	void quitSDL();
	set<SDL_Scancode> pressedKeys;
	
};

#endif