#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SDL2/SDL_ttf.h>

#include "container.hpp"

#define GAME_NAME "Open_Note!"

const int TICKS_PER_SECOND = 64;
const int SKIP_TICKS = 1024 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 8;

class Game : public Container {
  public:
    static Game* instance;
    SDL_Window * window;
    static SDL_Renderer * renderer;

    Game(unsigned int _width, unsigned int _height);
    virtual ~Game();

    void run();

    virtual void update();
    virtual void render(Transform & transform);

    const uint8_t* keyboard_state;
    int keyboard_state_size;
  private:
    void init_SDL();
    void quit_SDL();
    unsigned int _width, _height;
    double _aspect_ratio;
    bool _running = false;
};

bool key_pressed(SDL_Scancode key_code);

#endif /* end of include guard: GAME_HPP_INCLUDED */
