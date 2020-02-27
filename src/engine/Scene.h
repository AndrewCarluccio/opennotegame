#ifndef SCENE_H
#define SCENE_H

#include "DisplayObjectContainer.h"
#include "DisplayObject.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Scene : public DisplayObjectContainer{

public:
	Scene();

	/* Load scene from a file */
	void loadScene(string sceneFilePath);

	virtual DisplayObject* getChild(string id);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	virtual void draw(AffineTransform& at, Camera* cam);

	DisplayObjectContainer* root;

	float backgroundScrollRate;
	float midgroundScrollRate;
	float foregroundScrollRate;
	
private:
	//TODO --> change this from vector type string to vector type JSON args list, however you want to do that
	vector<string> the_list;
};

#endif