#ifndef TRANSFORM_HPP_INCLUDED
#define TRANSFORM_HPP_INCLUDED

#include <cmath>

#include <SDL2/SDL.h>

#include "matrix.hpp"
#include "constants.hpp"

class Transform {
  public:
    Transform();
    ~Transform();
    SDL_Point apply_transformation(int x, int y);
    void translate(int x, int y);
    void rotate(double r);
    void scale(double x, double y);
    std::string print();
  private:
    Matrix* _transform;
};

#endif /* end of include guard: TRANSFORM_HPP_INCLUDED */
