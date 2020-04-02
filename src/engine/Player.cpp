#include "Player.h"

using namespace std;

Player::Player(DisplayObject* object){
    myPlayer = object;
}
void Player::draw(AffineTransform& at){
    myPlayer->draw(at);
}

void Player::update(set<SDL_Scancode> pressedKeys){
    if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
            myPlayer->position.x -= 6;
        }
    else if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
        myPlayer->position.x += 6;
    }
    else if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
            myPlayer->position.y -= 6;
        }
    else if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
        myPlayer->position.y += 6;
    }
}