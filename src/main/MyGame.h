#ifndef MYGAME_H
#define MYGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../engine/Game.h"
#include "../engine/Sprite.h"
#include "../engine/AnimatedSprite.h"
#include "../engine/Scene.h"
#include "../engine/Camera.h"
#include "../engine/Sound.h"
#include "../engine/dev_tool/SceneWriter.h"
#include <cmath>


using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	//virtual void draw(AffineTransform& at, Camera* cam);

	Scene* scene;

	Camera* cam;

	Sound* sfx;

	bool goUp = true;

private:
	Scene* activeScene;
	bool show1 = true;
	DisplayObjectContainer *bar;
	Sprite *clickedSprite;
	int spriteCount = 0;
};

#endif