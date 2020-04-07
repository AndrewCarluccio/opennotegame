#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "MyGame.h"


using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	cs = new CollisionSystem();
	scene = new Scene();

	// Make sure the root is listenting to display object add/remove 
	// events before loading the scene
	root = (DisplayObjectContainer*)scene->root;
	root->addEventListener(cs, DisplayObjectEvent::DISPLAY_OBJECT_ADDED_EVENT);
	root->addEventListener(cs, DisplayObjectEvent::DISPLAY_OBJECT_REMOVED_EVENT);

	scene->loadScene("./resources/Scenes/collision_demo.json");
	parent = scene->getChild("Parent");
	character = scene->getChild("Character");
	car = scene->getChild("Car");

	activeScene = scene;

	cam = new Camera(1200, 1000);
	cam->setBounds(1000, 1000, 1000, 1000);
	cam->setZoom(1);

	cs->watchForCollisions("Car", "Character");
}

MyGame::~MyGame() {
}


void MyGame::update(set<SDL_Scancode> pressedKeys) {
	for(SDL_Scancode s : pressedKeys) {
		switch (s) {
		case SDL_SCANCODE_W: // Movement of Parent
			parent->old_position.y = parent->position.y;
			parent->position.y -= 5;
			break;
		case SDL_SCANCODE_S:
			parent->old_position.y = parent->position.y;
			parent->position.y += 5;
			break;
		case SDL_SCANCODE_A:
			parent->old_position.x = parent->position.x;
			parent->position.x -= 5;
			break;
		case SDL_SCANCODE_D:
			parent->old_position.x = parent->position.x;
			parent->position.x += 5;
			break;
		case SDL_SCANCODE_E:
			parent->rotation -= 0.01;
			break;
		case SDL_SCANCODE_R:
			parent->rotation += 0.01;
			break;
		case SDL_SCANCODE_F:
			parent->scaleX *= 0.99;
			parent->scaleY *= 0.99;
			break;
		case SDL_SCANCODE_G:
			parent->scaleX *= 1.01;
			parent->scaleY *= 1.01;
			break;
		case SDL_SCANCODE_I: // Movement of Character
			character->old_position.y = character->position.y;
			character->position.y -= 5;
			break;
		case SDL_SCANCODE_K:
			character->old_position.y = character->position.y;
			character->position.y += 5;
			break;
		case SDL_SCANCODE_J:
			character->old_position.x = character->position.x;
			character->position.x -= 5;
			break;
		case SDL_SCANCODE_L:
			character->old_position.x = character->position.x;
			character->position.x += 5;
			break;
		case SDL_SCANCODE_O:
			character->rotation -= 0.01;
			break;
		case SDL_SCANCODE_P:
			character->rotation += 0.01;
			break;
		case SDL_SCANCODE_N:
			character->scaleX *= 0.99;
			character->scaleY *= 0.99;
			break;
		case SDL_SCANCODE_M:
			character->scaleX *= 1.01;
			character->scaleY *= 1.01;
			break;
		case SDL_SCANCODE_UP: // Movement of Car
			car->old_position.y = car->position.y;
			car->position.y -= 5;
			break;
		case SDL_SCANCODE_DOWN:
			car->old_position.y = car->position.y;
			car->position.y += 5;
			break;
		case SDL_SCANCODE_LEFT:
			car->old_position.x = car->position.x;
			car->position.x -= 5;
			break;
		case SDL_SCANCODE_RIGHT:
			car->old_position.x = car->position.x;
			car->position.x += 5;
			break;
		case SDL_SCANCODE_X:
			car->rotation -= 0.01;
			break;
		case SDL_SCANCODE_C:
			car->rotation += 0.01;
			break;
		case SDL_SCANCODE_V:
			car->scaleX *= 0.99;
			car->scaleY *= 0.99;
			break;
		case SDL_SCANCODE_B:
			car->scaleX *= 1.01;
			car->scaleY *= 1.01;
			break;
		default:
			break;
		}
	}

	Game::update(pressedKeys);
	activeScene->update(pressedKeys);
	cs->update();
}

void MyGame::draw(AffineTransform& at) {
	Game::draw(at);
	SDL_RenderClear(Game::renderer);
	activeScene->draw(at,cam,true);
	SDL_RenderPresent(Game::renderer);
}