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
#include "../engine/Player.h"
#include "../engine/controls.h"
#include "../engine/SceneManager.h"
#include "../engine/Player.h"
#include "../engine/TransitionPoint.h"
#include "../engine/UI.h"

using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	
	Scene* scene;

	DisplayObjectContainer* root;

	DisplayObject* flag;

	Scene* default_area;

	string a1_1_name;
	string a1_2_name;
	string a1_3_name;
	string a1_4_name;
	string a1_5_name;
	string a1_6_name;
	string a1_7_name;
	string a1_8_name;

	string a2_1_name;
	string a2_2_name;
	string a2_3_name;
	string a2_4_name;
	string a2_5_name;
	string a2_6_name;
	string a2_7_name;
	string a2_8_name;

	string a3_1_name;
	string a3_2_name;
	string a3_3_name;
	string a3_4_name;
	string a3_5_name;
	string a3_6_name;
	string a3_7_name;
	string a3_8_name;

	string a4_1_name;
	string a4_2_name;
	string a4_3_name;
	string a4_4_name;
	string a4_5_name;
	string a4_6_name;
	string a4_7_name;
	string a4_8_name;

	string a1_1_path;
	string a1_2_path;
	string a1_3_path;
	string a1_4_path;
	string a1_5_path;
	string a1_6_path;
	string a1_7_path;
	string a1_8_path;

	string a2_1_path;
	string a2_2_path;
	string a2_3_path;
	string a2_4_path;
	string a2_5_path;
	string a2_6_path;
	string a2_7_path;
	string a2_8_path;

	string a3_1_path;
	string a3_2_path;
	string a3_3_path;
	string a3_4_path;
	string a3_5_path;
	string a3_6_path;
	string a3_7_path;
	string a3_8_path;

	string a4_1_path;
	string a4_2_path;
	string a4_3_path;
	string a4_4_path;
	string a4_5_path;
	string a4_6_path;
	string a4_7_path;
	string a4_8_path;

	TweenJuggler* tweenJuggler;
	SceneManager* scene_manager;
	Camera* cam;

	int i = 0;
	vector<string> all_paths;
	vector<string> all_names;

	CollisionSystem* cs;

	Player* player;

	EventDispatcher* dispatch;
	TweenListener* flagTweenListen; 
	Tween* flagExpandTween;
	UI* UserInterface;
	

private:

};

#endif
