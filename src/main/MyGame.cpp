#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	//instance = this;

	scene1 = new Scene();
	scene1->loadScene("./resources/Scenes/room_one.json");

	scene2 = new Scene();
	scene2->loadScene("./resources/Scenes/room_two.json");

	//this->addChild(scene1);
	activeScene = scene1;
}

MyGame::~MyGame() {
}


void MyGame::update(set<SDL_Scancode> pressedKeys) {
	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
		show1 = !show1;
	}

	if (show1) {
		activeScene = scene1;
	}
	else {
		//do the stuff to load scene 2
		activeScene = scene2;
	}
	
	Game::update(pressedKeys);
	activeScene->update(pressedKeys);
}

void MyGame::draw(AffineTransform& at) {
	Game::draw(at);
	SDL_RenderClear(Game::renderer);
	activeScene->draw(at);
	SDL_RenderPresent(Game::renderer);
}