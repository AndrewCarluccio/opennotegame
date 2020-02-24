#include "animated_sprite.hpp"

Animated_Sprite::Animated_Sprite() : Sprite () {
    this->type = animated;
}

Animated_Sprite::Animated_Sprite(std::string id, std::string file_path, uint8_t row_count, uint8_t column_count, uint8_t frame_rate)  {
    this->type = animated;
    this->file_path = file_path;
    add_animation(id, file_path, row_count, column_count, frame_rate);
    select_animation(id);
}

Animated_Sprite::~Animated_Sprite() {
    for(auto animation : animations) {
        delete animation.second;
    }
    animations.clear();
}

void Animated_Sprite::add_animation(std::string id, std::string file_path, uint8_t row_count, uint8_t column_count, uint8_t frame_rate) {
    Animation* animation = new Animation(id, file_path, row_count, column_count, frame_rate);
    animations.insert(std::pair<std::string,Animation*>(id,animation));
}

void Animated_Sprite::select_animation(std::string id) {
    this->current_animation = animations[id];
    this->image_width = current_animation->image_width;
    this->image_height = current_animation->image_height;
    this->pivot.x = current_animation->frame_width/2;
    this->pivot.y = current_animation->frame_height/2;
}

void Animated_Sprite::update() {
    current_frame+=static_cast<double>(current_animation->frame_rate)/static_cast<double>(TICKS_PER_SECOND);
    Sprite::update();
}

void Animated_Sprite::render(Transform & transform) {
    apply_transform(transform);
    transform.translate(-pivot.x, -pivot.y);
    if(current_animation->texture != nullptr && is_visible) {
        SDL_Point top_left = transform.apply_transformation(ZERO, ZERO);
        SDL_Point top_right = transform.apply_transformation(current_animation->frame_width, ZERO);
        SDL_Point bottom_left = transform.apply_transformation(ZERO, image_height);
        SDL_Point bottom_right = transform.apply_transformation(current_animation->frame_width, current_animation->frame_width);
        SDL_Point render_origin = {0, 0};

        int render_width = static_cast<int>(distance(top_left, top_right));
        int render_height = static_cast<int>(distance(top_right, bottom_right));

        SDL_Rect render_target = {top_left.x, top_left.y, render_width, render_height};

        SDL_Rect render_portion = *(current_animation->animation_frame_at(static_cast<int>(current_frame)));
        SDL_SetTextureAlphaMod(current_animation->texture, alpha);
        SDL_RenderCopyEx(Game::renderer, current_animation->texture, &render_portion, &render_target, TO_DEGREES*calculate_angle(top_left, top_right), &render_origin, flip);
    }
    transform.translate(pivot.x, pivot.y);
    deapply_transform(transform);
    Sprite::render(transform);
}
