#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <set>
#include "AffineTransform.h"
#include "Camera.h"
#include "Types.h"
#include <string>
#include <fstream>

using namespace std;

class DisplayObjectContainer;

class DisplayObject{

public:
	string id = "DEFAULT_ID";
	string imgPath = "";
	int red, green, blue;
	string type = "DisplayObject";
	types::Type object_type = types::Type::Default;

	DisplayObjectContainer* parent = NULL;

	bool isRGB = false;

	DisplayObject();
	DisplayObject(string id, string path);
	DisplayObject(string id, int red, int green, int blue);
	virtual ~DisplayObject();
	
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	void loadTexture(string filepath);
	void loadRGBTexture(int red, int green, int blue);
	void setTexture(SDL_Texture* t);

	void applyTransformations(AffineTransform &at);
	void reverseTransformations(AffineTransform &at);

	int getWidth();
	int getHeight();

	bool visible = true;
	SDL_Point position = {0, 0};
	int width = 100;
	int height = 100;
	SDL_Point pivot = {0, 0};
	double scaleX = 1.0;
	double scaleY = 1.0;
	double rotation = 0.0; // in radians
	int alpha = 255;
	int alpha_abs = 255;
	bool facingRight = true;
	bool facingDown = true;
	SDL_Point old_position = {0, 0};
	double oldScaleX = 1.0;
	double oldScaleY = 1.0;
	double oldRotation = 0.0;
	bool collidable = false;
	bool isDynamic = false;
	double hitboxScaleX = 1.0;
	double hitboxScaleY = 1.0;

	// global coordinates that dictate where the sprite actually is on the screen
	SDL_Point globalPos = {0, 0};
	int globalW = width;
	int globalH = height;
	int globalRotation = rotation;
	AffineTransform* globalTransform();
	SDL_Rect getHitbox();
	void drawHitbox(AffineTransform &at);
	virtual void onCollision(DisplayObject* other);
	DisplayObject* getRoot();
	static bool compareByPosition(const DisplayObject* a, const DisplayObject* b);

private:
	double distance(SDL_Point &p1, SDL_Point &p2);
	double calculateRotation(SDL_Point &origin, SDL_Point &p);
	
	SDL_Texture* texture = NULL;
	SDL_Surface* image = NULL;

	/* Texture currently being drawn. Equal to texture for normal DO */
	SDL_Texture* curTexture;

};

#endif