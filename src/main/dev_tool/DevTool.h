#ifndef DEVTOOL_H
#define DEVTOOL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cmath>
#include <thread>
#include <mutex>
#include <algorithm>

#include "../../engine/Game.h"
#include "../../engine/Sprite.h"
#include "../../engine/AnimatedSprite.h"
#include "../../engine/Scene.h"
#include "../../engine/Camera.h"
#include "../../engine/Sound.h"
#include "../../engine/dev_tool/SceneWriter.h"

#include "DevToolBar.h"
#include "CommandLine.h"



using namespace std;

class DevTool : public Game{

public:
	DevTool();
	
	virtual ~DevTool();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	//virtual void draw(AffineTransform& at, Camera* cam);

	Scene* scene;

	Camera* cam;

	Sound* sfx;


private:
	Scene* activeScene;
	bool show1 = true;
	DisplayObjectContainer *bar;
	DisplayObject *clickedSprite;
	DisplayObjectContainer *selectedLayer;
	int spriteCount = 0;
	double zoom = 1;
	Player *player;
	// lock for scene since it is shared between threads
	mutex scene_lock;
	// allow command class to access private members
	friend class CommandLine;
};

#endif