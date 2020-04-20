#ifndef TRANSITIONPOINT_H
#define TRANSITIONPOINT_H

#include "DisplayObjectContainer.h"
#include "Scene.h"

using namespace std;

class TransitionPoint : public DisplayObjectContainer{

public:
	
	TransitionPoint();
	TransitionPoint(string id, string filepath);
	TransitionPoint(string id, int red, int green, int blue);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform& at);

	//Scene* transition_scene = new Scene();
	string transition_scene_name;

	//void bindScene(vector<Scene*> scenes);

private:
	
};

#endif