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

	cam = new Camera(305*4,475*4,0,0,0,2730);

	//cam->moveCameraTo(1250, 2000);

	SDL_Point orig;
	orig.x = -150;
	orig.y = -400;

	//cam->moveCameraTo(1200,0);

	car->position = orig;

	//cam->zoom = 4;

	cam->setZoom(1);

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
		cam->moveCameraBy(0, 1);
	}
	else if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		car->position.x -= 1;
		cam->moveCameraBy(1, 0);
	}
	else if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		car->position.y += 1;
		cam->moveCameraBy(0, -1);
	}
	else if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		car->position.x += 1;
		cam->moveCameraBy(-1, 0);
	}

	if (car->position.y > 200 && car->position.x > 150 && car->position.x < 400 && car->position.y < 400) {
		cam->setZoom(4.1);
	}
	else {
		cam->setZoom(4);
	}

	if (car->position.y > 250 && car->position.y < 800) {
		cam->setBounds(10, 0, 0, 0);
	}
	else {
		cam->setBounds(0, 0, 0, 2730);
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