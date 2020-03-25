#ifndef DISPLAYOBJECTCONTAINER_H
#define DISPLAYOBJECTCONTAINER_H

#include <vector>
#include "DisplayObject.h"
#include "AffineTransform.h"
// #include "Event.h"
#include <string>
#include <fstream>

using namespace std;

class DisplayObjectContainer : public DisplayObject{

public:
	
	DisplayObjectContainer();
	DisplayObjectContainer(string id, string filepath);
	DisplayObjectContainer(string id, int red, int green, int blue);
	virtual ~DisplayObjectContainer();

	void addChild(DisplayObject* child);
	void removeImmediateChild(DisplayObject* child);
	void removeImmediateChild(string id);
	void removeChild(int index);
	void removeChild(string id);
	void removeThis();
	void moveChildToFront(string id);
	
	virtual int numChildren();
	virtual DisplayObject* getChild(int index);
	virtual DisplayObject* getChild(string id);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	float scrollRate = 1.0;

	vector<DisplayObject*> children;
private:
	
	
};

#endif