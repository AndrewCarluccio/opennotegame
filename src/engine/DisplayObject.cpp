#include "DisplayObject.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
#include <iostream>
#include <algorithm>
#include <cmath>

#define PI 3.14159265

DisplayObject::DisplayObject(){
	image = NULL;
	texture = NULL;
	curTexture = NULL;
}

DisplayObject::DisplayObject(string id, string filepath){
	this->id = id;
	this->imgPath = filepath;

	loadTexture(filepath);
}

DisplayObject::DisplayObject(string id, int red, int green, int blue){
	isRGB = true;
	this->id = id;

	this->red = red;
	this->blue = blue;
	this->green = green;

	this->loadRGBTexture(red, green, blue);
}

DisplayObject::~DisplayObject(){
	//TODO: Get this freeing working
	if(image != NULL) SDL_FreeSurface(image);
	if(texture != NULL) SDL_DestroyTexture(texture);	
}

void DisplayObject::loadTexture(string filepath){
	image = IMG_Load(filepath.c_str());
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	setTexture(texture);
}

void DisplayObject::loadRGBTexture(int red, int green, int blue){
	image = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0x000000ff);
	SDL_FillRect(image, NULL, SDL_MapRGB(image->format, red, green, blue));
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );
	setTexture(texture);
}

void DisplayObject::setTexture(SDL_Texture* t){
	
	this->curTexture = t;	
	if (curTexture != NULL) {
		SDL_QueryTexture(this->curTexture, NULL, NULL, &width, &height);
	}
	
}

void DisplayObject::update(set<SDL_Scancode> pressedKeys){
	if (this->parent != NULL) {
		//this->alpha = 255 * ((this->parent->alpha / 255) * (this->alpha / 255));
		//this->alpha = this->parent->alpha;
	}
}

void DisplayObject::draw(AffineTransform &at){
	applyTransformations(at);
	
	if(curTexture != NULL && visible) {
		SDL_Point origin = at.transformPoint(0, 0);
		SDL_Point upperRight = at.transformPoint(width, 0);
		SDL_Point lowerRight = at.transformPoint(width, height);
		SDL_Point corner = {0, 0};

		int w = (int)distance(origin, upperRight);
		int h = (int)distance(upperRight, lowerRight);

		SDL_Rect dstrect = { origin.x, origin.y, w, h };

		SDL_RendererFlip flip;
		if (facingRight) {
			flip = SDL_FLIP_NONE;
		}
		else {
			flip = SDL_FLIP_HORIZONTAL;
		}
		
		globalPos = origin;
		globalW = w;
		globalH = h;
		globalRotation = calculateRotation(origin, upperRight);
		
//collision_system
		//SDL_SetTextureAlphaMod(curTexture, alpha);
		//SDL_RenderCopyEx(Game::renderer, curTexture, NULL, &dstrect, calculateRotation(origin, upperRight), &corner, flip);
		//drawHitbox();	
		//int alpha_tmp;
		if (this->parent != NULL) {
			//this->alpha = 255 * ((this->parent->alpha / 255) * (this->alpha / 255));
			//this->alpha = this->parent->alpha;
			SDL_SetTextureAlphaMod(curTexture, 255.0 * double(double(this->parent->alpha / 255.0) * double(this->alpha / 255.0)));
			//cout << 255.0 * double(double(this->parent->alpha / 255.0) * double(this->alpha / 255.0)) << endl;
		}
		else {
			SDL_SetTextureAlphaMod(curTexture, alpha);
		}

		//SDL_SetTextureAlphaMod(curTexture, alpha);
		SDL_RenderCopyEx(Game::renderer, curTexture, NULL, &dstrect, calculateRotation(origin, upperRight), &corner, flip);	
		drawHitbox();
	}

	reverseTransformations(at);
}

void DisplayObject::applyTransformations(AffineTransform &at) {
	at.translate(position.x, position.y);
	at.rotate(rotation);
	at.scale(scaleX, scaleY);
	at.translate(-pivot.x, -pivot.y);
}

void DisplayObject::reverseTransformations(AffineTransform &at) {
	at.translate(pivot.x, pivot.y);
	at.scale(1.0/scaleX, 1.0/scaleY);
	at.rotate(-rotation);
	at.translate(-position.x, -position.y);
}

int DisplayObject::getWidth() {
	return this->image->w;
}

int DisplayObject::getHeight() {
	return this->image->h;
}

double DisplayObject::distance(SDL_Point &p1, SDL_Point &p2) {
	return sqrt(((p2.y - p1.y)*(p2.y - p1.y)) + ((p2.x - p1.x)*(p2.x - p1.x)));
}

double DisplayObject::calculateRotation(SDL_Point &origin, SDL_Point &p) {
	double y = p.y - origin.y;
	double x = p.x - origin.x;
	return (atan2(y, x) * 180 / PI);
}

AffineTransform* DisplayObject::globalTransform() {
	AffineTransform* at;
	if(parent != NULL) {
		at = parent->globalTransform();
		at->translate(-parent->pivot.x, -parent->pivot.y);
	}
	else {
		at = new AffineTransform();
	}
	applyTransformations(*at);
	at->translate(-pivot.x, -pivot.y);
	return at;
}

SDL_Rect DisplayObject::getHitbox() {
	AffineTransform* at = globalTransform();

	SDL_Point upperLeft = at->transformPoint(0, 0);
	SDL_Point upperRight = at->transformPoint(width, 0);
	SDL_Point lowerRight = at->transformPoint(width, height);
	SDL_Point lowerLeft = at->transformPoint(0, height);

	int x[] = {upperLeft.x, upperRight.x, lowerRight.x, lowerLeft.x};
	int y[] = {upperLeft.y, upperRight.y, lowerRight.y, lowerLeft.y};

	int min_x = *min_element(x, x+4);
	int min_y = *min_element(y, y+4);

	int max_x = *max_element(x, x+4);
	int max_y = *max_element(y, y+4);

	int w = max_x - min_x;
	int h = max_y - min_y;

	int scaled_w = w * hitboxScaleX;
	int scaled_h = h * hitboxScaleY;

	min_x += (w - scaled_w) / 2;
	min_y += (h - scaled_h) / 2;

	SDL_Rect hitbox = { min_x, min_y, scaled_w, scaled_h };
	
	return hitbox;
}

void DisplayObject::drawHitbox() {
	SDL_Rect hitbox = getHitbox();
	SDL_SetRenderDrawColor(Game::renderer, 0xFF, 0, 0, 0xFF);
	SDL_RenderDrawRect(Game::renderer, &hitbox);
	SDL_SetRenderDrawColor(Game::renderer, 0x00, 0, 0, 0xFF);
}

void DisplayObject::onCollision(DisplayObject* other) {
	Game::instance->collisionSystem.resolveCollision(this, other, 
	  this->position.x - this->old_position.x, this->position.y - this->old_position.y,
	  other->position.x - other->old_position.x, other->position.y - other->old_position.y);
}

DisplayObject* DisplayObject::getRoot() {
	if(parent != NULL)
		return parent->getRoot();
	else
		return this;
}

bool DisplayObject::compareByPosition(const DisplayObject* a, const DisplayObject* b) {
	return (a->position.x < b->position.x);
}