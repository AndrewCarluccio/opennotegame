#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED
#include <cmath>

#include <SDL2/SDL.h>

#include "constants.hpp"

double distance(SDL_Point& a, SDL_Point& b);
double calculate_angle(SDL_Point& a, SDL_Point& b);

#endif /* end of include guard: ENGINE_HPP_INCLUDED */
