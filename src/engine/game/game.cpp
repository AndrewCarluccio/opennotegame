#include "game.hpp"

SDL_Renderer* Game::renderer;
Game* Game::instance;

Game::Game(unsigned int width, unsigned int height) {
    Game::instance = this;
    keyboard_state = SDL_GetKeyboardState(&keyboard_state_size);
    this->_width = width;
    this->_height = height;
    this->_running = true;
    init_SDL();
    TTF_Init();
    /* General Game Configuration */
}

Game::~Game() {
    quit_SDL();
}

void Game::quit_SDL() {
    std::cout << "Game quitting..." << '\n';
    SDL_DestroyRenderer(Game::renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
}

void Game::init_SDL() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow(GAME_NAME,
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              this->_width, this->_height, SDL_WINDOW_OPENGL);

    Game::renderer = SDL_CreateRenderer(window, -ONE, SDL_RENDERER_ACCELERATED);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
}

void Game::run() {
    /* TO DO FRAMERATE LIMITING */

    unsigned int next_game_tick = SDL_GetTicks();
    unsigned int ticks;
    double interpolation;
    SDL_Event event; // Event handling | input | interactions
    while( _running ) {
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                _running = false;
                break;
            default:
                break;
            }
        }
        ticks = 0;
        while( SDL_GetTicks() > next_game_tick && MAX_FRAMESKIP > ticks++) { // Game calulations
            update();
            next_game_tick += SKIP_TICKS;
        }
        // interpolation = (static_cast<double>( SDL_GetTicks() + SKIP_TICKS - next_game_tick ))/(static_cast<double>( SKIP_TICKS ));
        Transform transform;
        render(transform);

    }
}

void Game::update() {
    Container::update();
}

void Game::render(Transform & transform) {
    SDL_RenderClear(Game::renderer);
    Container::render(transform);
    SDL_RenderPresent(Game::renderer);
}


bool key_pressed(SDL_Scancode key_code) {
    return Game::instance->keyboard_state[key_code];
}
