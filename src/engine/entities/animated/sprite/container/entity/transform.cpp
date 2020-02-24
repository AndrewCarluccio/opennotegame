#include "transform.hpp"
#include <iostream>

Transform::Transform() {
    _transform = new Matrix();
}
Transform::~Transform() {
    delete _transform;
}
SDL_Point Transform::apply_transformation(int x, int y) {
    SDL_Point point;
    point.x = static_cast<int>((_transform->at(0,0))*x + (_transform->at(0,1))*y + (_transform->at(0,2))*1);
    point.y = static_cast<int>((_transform->at(1,0))*x + (_transform->at(1,1))*y + (_transform->at(1,2))*1);
    return point;
}
void Transform::translate(int x, int y) {
    Matrix translation;
    translation.at(0,2) = x;
    translation.at(1,2) = y;
    *_transform*=translation;
}
void Transform::rotate(double r) {
    r*=TO_RADIANS;
    Matrix rotation;
    double cos = std::cos(r);
    double sin = std::sin(r);
    rotation.at(0,0) = cos;
    rotation.at(0,1) = -sin;
    rotation.at(1,0) = sin;
    rotation.at(1,1) = cos;
    *_transform*=rotation;
}
void Transform::scale(double x, double y) {
    Matrix scale;
    scale.at(0,0) = x;
    scale.at(1,1) = y;
    *_transform*=scale;
}
std::string Transform::print() {
    return _transform->to_string();
}
