#ifndef SPRITE_HPP_INCLUDED
#define SPRITE_HPP_INCLUDED

#include "container.hpp"

class Sprite : public Container {

  public:

    Sprite();
    Sprite(std::string id, std::string file_path);
    Sprite(std::string id, uint8_t red, uint8_t green, uint8_t blue);

    virtual void update();
    virtual void render(Transform & transform);

  private:

};
#endif /* end of include guard: SPRITE_HPP_INCLUDED */
