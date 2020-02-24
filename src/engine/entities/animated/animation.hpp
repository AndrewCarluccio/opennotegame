#ifndef ANIMATION_HPP_INCLUDED
#define ANIMATION_HPP_INCLUDED

#include <vector>

#include "sprite.hpp"

class Animation {
  public:
    Animation(std::string id, std::string file_path, uint8_t row_count, uint8_t column_count, uint8_t frame_rate);
    ~Animation();
    SDL_Texture* texture = nullptr;

    SDL_Rect* animation_frame_at(uint8_t i);
    std::string file_path;
    uint8_t frame_rate;
    uint8_t frame_count;
    unsigned int image_width;
    unsigned int image_height;
    unsigned int frame_width;
    unsigned int frame_height;
    std::string id;
  private:
    void build_render_targets();
    std::vector<SDL_Rect*> render_targets;
};


#endif /* end of include guard: ANIMATION_HPP_INCLUDED */
