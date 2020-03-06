#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "MyGame.h"


using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	//instance = this;

	scene = new Scene();
	scene->loadScene("./resources/Scenes/parallax_demo.json");

	car = scene->getChild("Car");
	coin = scene->getChild("Coin");

	coin->pivot.x = coin->getWidth() / 2;
	coin->pivot.y = coin->getHeight() / 2;

	activeScene = scene;

	cam = new Camera(1200, 1000);
	cam->setBounds(1000, 1000, 1000, 1000);
	cam->setZoom(1);

	dispatch = new EventDispatcher();
	//TweenListener* carTweenListen = new TweenListener();
	coinExpandTween = new Tween(coin);

	coinTweenListen = new TweenListener();

	coinTweenListen->myTween = coinExpandTween;

	dispatch->addEventListener(coinTweenListen,TweenEvent::TWEEN_END_EVENT);
	tweenJuggler = new TweenJuggler(dispatch);

	Tween* carEntryTween = new Tween(car);
	carEntryTween->animate(TweenableParams::ALPHA, 0, 255, 2);

	tweenJuggler->add(carEntryTween);

	//sfx = new Sound();
	//sfx->playMusic();
}

MyGame::~MyGame() {
}


void MyGame::update(set<SDL_Scancode> pressedKeys) {
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		car->position.x -= 6;
		cam->moveCameraBy(5, 0);
	}
	else if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		car->position.x += 6;
		cam->moveCameraBy(-5, 0);
	}

	if (car->position.x > 1400) {
		if (!collision) {
			
			coinExpandTween->animate(TweenableParams::SCALE_X, 0.1, 0.4, 2);
			coinExpandTween->animate(TweenableParams::SCALE_Y, 0.1, 0.4, 2);

			tweenJuggler->add(coinExpandTween);

			collision = true;
		}		
	}

	//Event handler gets Tween Finished event
	if (coinTweenListen->occured) {
		Tween* coinFadeTween = new Tween(coin);
		coinFadeTween->animate(TweenableParams::ALPHA, 255, 0, 2);

		tweenJuggler->add(coinFadeTween);
		coinTweenListen->occured = false;
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