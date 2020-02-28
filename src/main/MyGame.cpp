#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	//instance = this;

	bar = new DisplayObjectContainer();
	vector<string> filenames = {"Jump_5.png", "Idle_2.png","Idle_15.png","Jump_3.png","Idle_5.png", "Jump_23.png", "Idle_2.png","Run_10.png","Jump_3.png","Walk_15.png", "Run_5.png", "Jump_2.png"};
	for (int i = 0; i < filenames.size(); i++) {
		Sprite *sprite = new Sprite("test" + to_string(i), "./resources/character/" + filenames[i]);
		sprite->scaleX = 100.0 / sprite->width;
		sprite->scaleY = 100.0 / sprite->height;
		sprite->position.x = 100 * i;
		bar->addChild(sprite);
		
	}

	scene = new Scene();
	scene->loadScene("./resources/Scenes/camera_demo.json");


	activeScene = scene;

	activeScene->root->position.y = 100;

	cam = new Camera(305*4,475*4,0,0,0,2730);

	//cam->moveCameraTo(1250, 2000);

	SDL_Point orig;
	orig.x = -150;
	orig.y = -400;

	//cam->moveCameraTo(1200,0);

	// car->position = orig;

	//cam->zoom = 4;

	cam->setZoom(1);

	sfx = new Sound();
	sfx->playMusic();


}

MyGame::~MyGame() {
}


void MyGame::update(set<SDL_Scancode> pressedKeys) {
	
	Game::update(pressedKeys);

	if(mousePressedDown && initialClick) {
		if(mouseY < 100) {
			int copyIndex = mouseX / 100;
			DisplayObject *toCopy = bar->getChild(copyIndex);
			Sprite* newSprite = new Sprite("sprite" + to_string(spriteCount), toCopy->imgPath);
			spriteCount++;
			newSprite->scaleX = 100.0 / newSprite->width;
			newSprite->scaleY = 100.0 / newSprite->height;
			newSprite->position.x = (mouseX - 50);
			newSprite->position.y = (mouseY - 50) - 100;
			clickedSprite = newSprite;
			activeScene->foreground->addChild(clickedSprite);

		}

		initialClick = false;
	} else if(mousePressedDown) {
		if (clickedSprite != NULL) {
			clickedSprite->position.x = (mouseX - 50);
			clickedSprite->position.y = (mouseY - 50) - 100;
		}
	}

	if(!mousePressedDown && initialRelease) {
		if (clickedSprite != NULL) {
			clickedSprite->position.x = (int)(round(clickedSprite->position.x / 100.0) * 100);
			clickedSprite->position.y = (int)(round(clickedSprite->position.y / 100.0) * 100);
			clickedSprite = NULL;
		}
		initialRelease = false;
	}

	if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) {
		cout << "Type the name of a scene file inside ./resources/Scenes, ex. camera_demo.json" << endl;
		string filename;
		cin >> filename;
		delete activeScene;
		activeScene = new Scene();
		activeScene->loadScene("./resources/Scenes/" + filename);
		activeScene->root->position.y = 100;

	} 
	
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		cout << "Type the name of the file you want to save the scene as, ex. scene.json" << endl;
		string filename;
		cin >> filename;
		SceneWriter sw(activeScene);
		sw.saveScene("./resources/Scenes/" + filename);
	}
	bar->update(pressedKeys);
	activeScene->update(pressedKeys);
}


void MyGame::draw(AffineTransform& at) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::renderer);
	
	Game::draw(at);
	SDL_Rect rect = {0, 0, windowWidth, 100};
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &rect);
	bar->draw(at);
	activeScene->draw(at);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	for(int i = 100; i <= windowHeight; i+=100) {
		SDL_RenderDrawLine(renderer, 0, i, windowWidth, i);
	}
	for(int j = 0; j <= windowWidth; j+=100) {
		SDL_RenderDrawLine(renderer, j, 100, j, windowHeight);
	}
	SDL_RenderPresent(Game::renderer);
}