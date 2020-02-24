#ifndef ANIMATED_SPRITE_HPP_INCLUDED
#define ANIMATED_SPRITE_HPP_INCLUDED

#include <unordered_map>

#include "animation.hpp"
#include "sprite.hpp"
#include "game.hpp"

class Animated_Sprite :  public Sprite {
  public:
    Animated_Sprite();
    Animated_Sprite(std::string file_path, std::string id, uint8_t row_count, uint8_t column_count, uint8_t frame_rate);
    ~Animated_Sprite();

    void add_animation(std::string file_path, std::string id, uint8_t row_count, uint8_t column_count, uint8_t frame_rate);
    void remove_animation(std::string id);
    void select_animation(std::string id);

    void play_animation();
    void pause_animation();

    virtual void update();
    virtual void render(Transform & transform);
  private:
    std::unordered_map<std::string, Animation*> animations;
    Animation* current_animation;
    double current_frame;
    bool is_animated;
};

#endif /* end of include guard: ANIMATED_SPRITE_HPP_INCLUDED */
