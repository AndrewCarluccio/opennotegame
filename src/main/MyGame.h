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
#include "../engine/TweenJuggler.h"
#include "../engine/EventDispatcher.h"
#include "../engine/TweenEvent.h"
#include "../engine/TweenListener.h"
#include "../engine/Tween.h"
#include "../engine/SceneManager.h"
#include "../engine/Player.h"
#include "../engine/UI.h"

using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	//virtual void draw(AffineTransform& at, Camera* cam);

	Scene* area1_1;
	Scene* area1_2;
	Scene* area1_3;
	Scene* area1_4;
	Scene* area1_5;
	Scene* area1_6;
	Scene* area1_7;
	Scene* area1_8;
	Scene* area2_1;
	Scene* area2_2;
	Scene* area2_3;
	Scene* area2_4;
	Scene* area2_5;
	Scene* area2_6;
	Scene* area2_7;
	Scene* area2_8;


	TweenJuggler* tweenJuggler;
	EventDispatcher* dispatch;
	SceneManager* scene_manager;
	Camera* cam;

	DisplayObject* player;

	UI* UserInterface;
	

private:

};

#endif