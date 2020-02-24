#include "sprite.hpp"

Sprite::Sprite() : Container () {
    this->type = sprite;
}

Sprite::Sprite(std::string id, std::string file_path) : Container(id, file_path) {
    this->type = sprite;
    this->file_path = file_path;
}

Sprite::Sprite(std::string id, uint8_t red, uint8_t green, uint8_t blue) : Container(id, red, green, blue) {
    this->type = sprite;
}

void Sprite::update() {
    Container::update();
}

void Sprite::render(Transform & transform) {
    Container::render(transform);
}
