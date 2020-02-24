#include "engine.hpp"

double distance(SDL_Point &a, SDL_Point &b) {
    return std::sqrt(std::pow(b.x-a.x,2.0)+std::pow(b.y-a.y,2.0));
}
double calculate_angle(SDL_Point &a, SDL_Point &b) {
    return atan2(b.y-a.y, b.x-a.x);
}
