#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	//instance = this;

	scene = new Scene();
	scene->loadScene("./resources/Scenes/camera_demo.json");

	car = scene->getChild("Girl");

	activeScene = scene;

	cam = new Camera(1200,1000);

	//cam->moveCameraTo(1250, 2000);

	SDL_Point orig;
	orig.x = -150;
	orig.y = -400;

	//cam->moveCameraTo(1200, 500+1300);

	car->position = orig;

	cam->zoom = 1;

}

MyGame::~MyGame() {
}


void MyGame::update(set<SDL_Scancode> pressedKeys) {
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		/*
		if (car->position.y > 5) {
			car->position.y -= 5;
			cam->moveCameraBy(0, 5);
		}
		*/
		car->position.y -= 1;
		cam->moveCameraBy(0, 4);
	}
	else if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		car->position.x -= 1;
		cam->moveCameraBy(4, 0);
	}
	else if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		car->position.y += 1;
		cam->moveCameraBy(0, -4);
	}
	else if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		car->position.x += 1;
		cam->moveCameraBy(-4, 0);
	}

	if (car->position.y < 200) {
		//cam->zoom = 1;
	}
	else {
		//cam->zoom = 2;
	}
	
	Game::update(pressedKeys);
	activeScene->update(pressedKeys);
}

void MyGame::draw(AffineTransform& at) {
	Game::draw(at);
	SDL_RenderClear(Game::renderer);
	activeScene->draw(at,cam);
	SDL_RenderPresent(Game::renderer);
}