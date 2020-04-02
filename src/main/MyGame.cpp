#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "MyGame.h"
#include "../engine/character_programming/Player.h"
#include "../engine/character_programming/controls.h"


using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	//instance = this;

	scene = new Scene();
	scene->loadScene("./resources/Scenes/area1/level1-1.json");

	player = scene->getChild("player");
	flag = scene->getChild("sprite64");

	flag->pivot.x = flag->getWidth() / 2;
	flag->pivot.y = flag->getHeight() / 2;

	activeScene = scene;

	cam = new Camera(1200, 1000);
	cam->setBounds(1000, 1000, 1000, 1000);
	cam->setZoom(0.5);

	dispatch = new EventDispatcher();
	//TweenListener* carTweenListen = new TweenListener();
	flagExpandTween = new Tween(flag);

	flagTweenListen = new TweenListener();

	flagTweenListen->myTween = flagExpandTween;

	dispatch->addEventListener(flagTweenListen,TweenEvent::TWEEN_END_EVENT);
	tweenJuggler = new TweenJuggler(dispatch);

	Tween* playerEntryTween = new Tween(player);
  playerEntryTween->animate(TweenableParams::ALPHA, 0, 255, 2);

	tweenJuggler->add(playerEntryTween);

	//sfx = new Sound();
	//sfx->playMusic();
}

MyGame::~MyGame() {
}


void MyGame::update(set<SDL_Scancode> pressedKeys) {
  /*
  if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		player->position.x -= 6;
		//cam->moveCameraBy(5, 0);
	}
	else if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		player->position.x += 6;
		//cam->moveCameraBy(-5, 0);
	}

  */

  	Player::update(pressedKeys);

	
	if (player->position.x > 1400) {
		if (!collision) {
			
			flagExpandTween->animate(TweenableParams::SCALE_X, 0.1, 0.4, 2);
			flagExpandTween->animate(TweenableParams::SCALE_Y, 0.1, 0.4, 2);

			tweenJuggler->add(flagExpandTween);

			collision = true;
		}		
	}

	//Event handler gets Tween Finished event
	if (flagTweenListen->occured) {
		Tween* flagFadeTween = new Tween(flag);
		flagFadeTween->animate(TweenableParams::ALPHA, 255, 0, 2);

		tweenJuggler->add(flagFadeTween);
		flagTweenListen->occured = false;
	}

	tweenJuggler->nextFrame();
	
	Game::update(pressedKeys);
	activeScene->update(pressedKeys);
}

void MyGame::draw(AffineTransform& at) {
	Game::draw(at);
	SDL_RenderClear(Game::renderer);
	activeScene->draw(at,cam,true);
	//activeScene->draw(at);
	SDL_RenderPresent(Game::renderer);
}
  




