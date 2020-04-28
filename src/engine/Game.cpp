#include <iostream>
#include "Game.h"
#include <string>
#include <ctime>
#include "DisplayObject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

SDL_Renderer* Game::renderer;
Game* Game::instance;
unsigned int Game::frameCounter = 0;

Game::Game(int windowWidth, int windowHeight) {
	Game::instance = this;

	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	TTF_Init();
	initSDL();
}

Game::~Game() {
	quitSDL();
}

void Game::quitSDL() {
	cout << "Quitting sdl" << endl;
	SDL_DestroyRenderer(Game::renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);

	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

void Game::initSDL() {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	window = SDL_CreateWindow("myGame",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->windowWidth, this->windowHeight, 0);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	font = TTF_OpenFont("./resources/Fonts/Roboto-Regular.ttf", 50);
	const char *error = TTF_GetError();

	Game::renderer = renderer;
}

void Game::start() {

	int ms_per_frame = (1.0 / (double)this->frames_per_sec) * 1000;
	std::clock_t start = std::clock();

	bool quit = false;
	SDL_Event event;

	while (!quit) {
		std::clock_t end = std::clock();
		double duration = ((end - start) / (double)CLOCKS_PER_SEC) * 1000;
		if (duration > ms_per_frame) {
			start = end;
			this->update(pressedKeys);
			AffineTransform at;
			this->draw(at);
		}

		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			pressedKeys.insert(event.key.keysym.scancode);
			break;
		case SDL_KEYUP:
			pressedKeys.erase(event.key.keysym.scancode);
			break;
		case SDL_MOUSEBUTTONDOWN:
			// cout << "Mouse clicked!" << event.motion.x << ", " << event.motion.y << endl;
			if(!mousePressedDown) {
				initialClick = true;
			}
			mousePressedDown = true;
			mouseX = event.motion.x;
			mouseY = event.motion.y;
			prevMouseX = mouseX;
			prevMouseY = mouseY;
			break;
		case SDL_MOUSEBUTTONUP:
			// cout << "Mouse released!" << endl;
			if(mousePressedDown) {
				initialRelease = true;
			}
			mousePressedDown = false;
			break;
		case SDL_MOUSEMOTION:
			// cout << "Mouse position: " << event.motion.x << ", " << event.motion.y << endl;
			prevMouseX = mouseX;
			prevMouseY = mouseY;
			mouseX = event.motion.x;
			mouseY = event.motion.y;
			mouseMotionX = event.motion.xrel;
			mouseMotionY = event.motion.yrel;
			break;
		}
	}
}

void Game::update(set<SDL_Scancode> pressedKeys) {
	frameCounter++;
}
void Game::draw(AffineTransform& at) {
}

/*
void Game::draw(AffineTransform& at, Camera* cam) {

}
*/