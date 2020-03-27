#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "MyGame.h"


using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	scene = new Scene();
	scene->loadScene("./resources/Scenes/collision_demo.json");

	parent = scene->getChild("Parent");
	character = scene->getChild("Character");
	car = scene->getChild("Car");

	activeScene = scene;

	cam = new Camera(1200, 1000);
	cam->setBounds(1000, 1000, 1000, 1000);
	cam->setZoom(1);

	cs = new CollisionSystem();
}

MyGame::~MyGame() {
}


void MyGame::update(set<SDL_Scancode> pressedKeys) {
	// Movement of parent display object
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end())
		parent->speedX = -6;
	else if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end())
		parent->speedX = 6;
	else
		parent->speedX = 0;
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end())
		parent->speedY = -6;
	else if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end())
		parent->speedY = 6;
	else
		parent->speedY = 0;
	if (pressedKeys.find(SDL_SCANCODE_E) != pressedKeys.end())
		parent->rotation -= 0.01;
	else if (pressedKeys.find(SDL_SCANCODE_R) != pressedKeys.end())
		parent->rotation += 0.01;
	if (pressedKeys.find(SDL_SCANCODE_F) != pressedKeys.end()){
		parent->scaleX *= 0.99;
		parent->scaleY *= 0.99;
	}
	else if (pressedKeys.find(SDL_SCANCODE_G) != pressedKeys.end()){
		parent->scaleX *= 1.01;
		parent->scaleY *= 1.01;
	}

	// Movement of character
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end())
		character->speedX = -6;
	else if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end())
		character->speedX = 6;
	else
		character->speedX = 0;
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end())
		character->speedY = -6;
	else if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end())
		character->speedY = 6;
	else
		character->speedY = 0;
	if (pressedKeys.find(SDL_SCANCODE_O) != pressedKeys.end())
		character->rotation -= 0.01;
	else if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end())
		character->rotation += 0.01;
	if (pressedKeys.find(SDL_SCANCODE_N) != pressedKeys.end()){
		character->scaleX *= 0.99;
		character->scaleY *= 0.99;
	}
	else if (pressedKeys.find(SDL_SCANCODE_M) != pressedKeys.end()){
		character->scaleX *= 1.01;
		character->scaleY *= 1.01;
	}

	// Movement of car
	if (pressedKeys.find(SDL_SCANCODE_J) != pressedKeys.end())
		car->speedX = -6;
	else if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end())
		car->speedX = 6;
	else
		car->speedX = 0;
	if (pressedKeys.find(SDL_SCANCODE_I) != pressedKeys.end())
		car->speedY = -6;
	else if (pressedKeys.find(SDL_SCANCODE_K) != pressedKeys.end())
		car->speedY = 6;
	else
		car->speedY = 0;
	if (pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end())
		car->rotation -= 0.01;
	else if (pressedKeys.find(SDL_SCANCODE_C) != pressedKeys.end())
		car->rotation += 0.01;
	if (pressedKeys.find(SDL_SCANCODE_V) != pressedKeys.end()){
		car->scaleX *= 0.99;
		car->scaleY *= 0.99;
	}
	else if (pressedKeys.find(SDL_SCANCODE_B) != pressedKeys.end()){
		car->scaleX *= 1.01;
		car->scaleY *= 1.01;
	}

	parent->position.x += parent->speedX;
	parent->position.y += parent->speedY;

	character->position.x += character->speedX;
	character->position.y += character->speedY;

	car->position.x += car->speedX;
	car->position.y += car->speedY;
	
	Game::update(pressedKeys);
	activeScene->update(pressedKeys);
	if(cs->collidesWith(character, car))
		cs->resolveCollision(character, car, character->speedX, character->speedY, car->speedX, car->speedY);
}

void MyGame::draw(AffineTransform& at) {
	Game::draw(at);
	SDL_RenderClear(Game::renderer);
	activeScene->draw(at,cam,true);
	SDL_RenderPresent(Game::renderer);
}