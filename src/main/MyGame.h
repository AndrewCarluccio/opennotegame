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
#include "../engine/CollisionSystem.h"


using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	Scene *scene;

	DisplayObject* parent;
	DisplayObject* character;
	DisplayObject* car;

	Camera* cam;

	CollisionSystem* cs;

private:
	Scene* activeScene;
};

#endif