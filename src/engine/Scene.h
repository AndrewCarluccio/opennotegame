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

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	DisplayObjectContainer* foreground;
	DisplayObjectContainer* midground;
	DisplayObjectContainer* background;

	DisplayObjectContainer* root;

private:
	//TODO --> change this from vector type string to vector type JSON args list, however you want to do that
	vector<string> the_list;

	vector<string> parent_ids;
};

#endif