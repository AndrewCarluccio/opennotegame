#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "DisplayObjectContainer.h"
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
#include "../engine/TransitionPoint.h"


#include <vector>

using namespace std;

class SceneManager{

public:
	SceneManager(TweenJuggler* jug, EventDispatcher* disp);

	SceneManager(TweenJuggler* jug, EventDispatcher* disp, vector<string> scn_names, vector<string> scn_paths);

	//Adds a transition trigger to the manager
	//Params: name of the transition, x,y position to trigger the transition and a margin m, a durration d for the xfade, tree from_tree to transition out of, tree to_tree to transition to
	//Return: success (true) or failure (false)
	bool addTransitionPoint(string name, int x, int y, int m, int durr, Scene* from_tree, Scene* to_tree);
	
	//Returns list of all transition names
	vector<string> getTransitions();

	//Removes a transition trigger from the manager
	//Params: name of transition point to remove
	//Return: success (true) or failure (false)
	bool removeTransitionPoint(string name);

	//Calls a scene transition if the provided position is within margin of any loaded transition
	//Return: true if transition triggered, false otherwise
	bool processPosition(int x, int y);

	bool processPosition();

	Scene* active_scene;
	Scene* transition_scene;

	DisplayObjectContainer* UI;

	vector<string> scene_names;
	vector<string> scene_paths;



private:
	vector<string> transition_names;
	vector<vector<int>> transition_metadata;
	vector<vector<Scene*>> transition_pairs;

	void transitionOut(int durr, Scene* from_tree);
	void transitionIn(int durr, Scene* to_tree);

	TweenJuggler* juggler;
	EventDispatcher* dispatch;

	TweenListener* listen = new TweenListener();
	//TweenListener* listen_end = new TweenListener();

	int d = 0;
	bool primed = false;
	

};

#endif