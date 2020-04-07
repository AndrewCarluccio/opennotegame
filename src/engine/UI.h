#ifndef UI_H
#define UI_H

#include "DisplayObjectContainer.h"
#include "Scene.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class UI : public Scene {

public:
	UI();

	/* Load scene from a file */
	void loadInterface(string sceneFilePath);

	virtual DisplayObject* getChild(string id);

	//DisplayObjectContainer* createLayer(const Value& layerInfo);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform& at);
	virtual void draw(AffineTransform& at, Camera* cam, bool paralax);

	void setHealth(int h);
	int getHealth();

private:
	//TODO --> change this from vector type string to vector type JSON args list, however you want to do that
	vector<string> the_list;
	int health = 100;
	DisplayObject* health_meter;
};

#endif

