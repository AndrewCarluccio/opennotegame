#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "DevTool.h"
#include <thread>
#include <mutex>

using namespace std;

int GRID_SIZE = 25;

// lock for scene since it is shared between threads
mutex scene_lock;

void DevTool::commandLine() {
		while(true) {
			cout << ">>";
			string command;
			cin >> command;
			if (command == "load") {
				cout << "Type the name of a scene file inside ./resources/Scenes, ex. camera_demo.json" << endl;
				string filename;
				cin >> filename;
				scene_lock.lock();
				delete activeScene;
				activeScene = new Scene();
				activeScene->loadScene("./resources/Scenes/" + filename);
				activeScene->root->position.y = 100;
				scene_lock.unlock();
			} else if (command == "save") {
				cout << "Type the name of the file you want to save the scene as, ex. scene.json" << endl;
				string filename;
				cin >> filename;
				SceneWriter sw(activeScene);
				sw.saveScene("./resources/Scenes/" + filename);
			}
		}
}

DevTool::DevTool() : Game(1200, 1000) {

	bar = new DisplayObjectContainer();
	vector<string> filenames = {"Jump_5.png", "Idle_2.png","Idle_15.png","Jump_3.png","Idle_5.png", "Jump_23.png", "Idle_2.png","Run_10.png","Jump_3.png","Walk_15.png", "Run_5.png", "Jump_2.png"};
	for (int i = 0; i < filenames.size(); i++) {
		Sprite *sprite = new Sprite("test" + to_string(i), "./resources/character/" + filenames[i]);
		sprite->scaleX = 100.0 / sprite->width;
		sprite->scaleY = 100.0 / sprite->height;
		sprite->position.x = 100 * i;
		bar->addChild(sprite);
		
	}
	cam = new Camera(1200, 1000);
	cam->setBounds(1000, 1000, 1000, 1000);
	cam->setZoom(zoom);

	scene = new Scene();

	scene->loadScene("./resources/Scenes/camera_demo.json");
	thread cmdThread(&DevTool::commandLine, this);
	cmdThread.detach();

	scene_lock.lock();
	activeScene = scene;
	activeScene->root->position.y = 100;
	scene_lock.unlock();
}

DevTool::~DevTool() {
}

bool mouseWithinBounds(DisplayObject *sprite, int mouseX, int mouseY) {
	return mouseY > sprite->globalPos.y &&
		mouseY < sprite->globalPos.y + sprite->globalH &&
		mouseX > sprite->globalPos.x &&
		mouseX < sprite->globalPos.x + sprite->globalW;


}

void DevTool::update(set<SDL_Scancode> pressedKeys) {
	
	Game::update(pressedKeys);
	if(mousePressedDown && initialClick) {
		if(mouseY < 100) {
			int copyIndex = mouseX / 100;
			DisplayObject *toCopy = bar->getChild(copyIndex);
			Sprite* newSprite = new Sprite("sprite" + to_string(spriteCount), toCopy->imgPath);
			spriteCount++;
			// newSprite->scaleX = 100.0 / newSprite->width;
			// newSprite->scaleY = 100.0 / newSprite->height;
			newSprite->position.x = (mouseY);
			newSprite->position.y = (mouseY);
			clickedSprite = newSprite;
			activeScene->foreground->addChild(clickedSprite);

		} else {
			for (const auto& sprite: activeScene->foreground->children) {
				// check if mouse is within the bounding box of the sprite
				if (mouseWithinBounds(sprite, mouseX, mouseY)) {
					clickedSprite = sprite;
					break;
				}
			}
		}

		initialClick = false;
	} else if(mousePressedDown) {
		if (clickedSprite != NULL) {
			clickedSprite->position.x += 2* (mouseX - prevMouseX);
			clickedSprite->position.y += 2 * (mouseY - prevMouseY);
		}
	}

	if(!mousePressedDown && initialRelease) {
		if (clickedSprite != NULL) {
			clickedSprite->position.x = (int)(round(clickedSprite->position.x / (double)GRID_SIZE) * GRID_SIZE);
			clickedSprite->position.y = (int)(round(clickedSprite->position.y / (double)GRID_SIZE) * GRID_SIZE);
		}
		initialRelease = false;
	}

	if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
			// car->position.x -= 6;
		if (clickedSprite != NULL) {
			clickedSprite->scaleX += 0.01;
		}
	}

	else if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		if (clickedSprite != NULL) {
			clickedSprite->scaleX -= 0.01;
		}
	}

	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		if (clickedSprite != NULL) {
			clickedSprite->scaleY += 0.01;
		}
	}
	else if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		if (clickedSprite != NULL) {
			clickedSprite->scaleY -= 0.01;
		}
	}

	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		cam->moveCameraBy(5, 0);
	}
	else if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		cam->moveCameraBy(-5, 0);
	}
	else if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		cam->moveCameraBy(0, 5);
	}
	else if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		cam->moveCameraBy(0, -5);
	}

	if (pressedKeys.find(SDL_SCANCODE_V) != pressedKeys.end()) {
		zoom += 0.01;
		zoom = min(zoom, 4.0);
		cam->setZoom(zoom);
	}
	else if (pressedKeys.find(SDL_SCANCODE_B) != pressedKeys.end()) {
		zoom -= 0.01;
		zoom = max(zoom, 0.1);
		cam->setZoom(zoom);
	}


	bar->update(pressedKeys);
	scene_lock.lock();
	activeScene->update(pressedKeys);
	scene_lock.unlock();
}


void DevTool::draw(AffineTransform& at) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::renderer);
	
	Game::draw(at);
	scene_lock.lock();
	activeScene->draw(at, cam, false);
	scene_lock.unlock();

	SDL_Rect rect = {0, 0, windowWidth, 100};
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &rect);
	
	
	bar->draw(at);

	
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	for(int i = 100; i <= windowHeight; i+=GRID_SIZE) {
		SDL_RenderDrawLine(renderer, 0, i, windowWidth, i);
	}
	for(int j = 0; j <= windowWidth; j+=GRID_SIZE) {
		SDL_RenderDrawLine(renderer, j, 100, j, windowHeight);
	}
	SDL_RenderPresent(Game::renderer);
}