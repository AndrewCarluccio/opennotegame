#include "open_note.hpp"

Open_Note::Open_Note() : Game(1280, 720) {
    instance = this;
    Container* scene = new Container();
    this->add_child(scene);
    /** Game Configuration? **/
}

Open_Note::~Open_Note() {

}

void Open_Note::update() {
    if(key_pressed(SDL_SCANCODE_RIGHT)) {

    }
    if(key_pressed(SDL_SCANCODE_LEFT)) {

    }
    if(key_pressed(SDL_SCANCODE_UP)) {

    }
    if(key_pressed(SDL_SCANCODE_DOWN)) {

    }
    if(key_pressed(SDL_SCANCODE_Q)) {

    }
    if(key_pressed(SDL_SCANCODE_W)) {

    }
    if(key_pressed(SDL_SCANCODE_E)) {

    }
    if(key_pressed(SDL_SCANCODE_R)) {

    }
    if(key_pressed(SDL_SCANCODE_I)) {

    }
    if(key_pressed(SDL_SCANCODE_K)) {

    }
    if(key_pressed(SDL_SCANCODE_J)) {

    }
    if(key_pressed(SDL_SCANCODE_L)) {

    }
    if(key_pressed(SDL_SCANCODE_A)) {

    }
    if(key_pressed(SDL_SCANCODE_S)) {

    }
    if(key_pressed(SDL_SCANCODE_Z)) {

    }
    if(key_pressed(SDL_SCANCODE_X)) {

    }
    if(key_pressed(SDL_SCANCODE_SPACE)) {

    }
    if(key_pressed(SDL_SCANCODE_ESCAPE)) {
        //toggle pause
    }
    /** TO DO **/
    // Event handlers for mouse events and other state machine inputs
    Game::update();
}

void Open_Note::render(Transform & transform) {
    Game::render(transform);
}
