#include "animation.hpp"
#include "game.hpp"

Animation::Animation(std::string id, std::string file_path, uint8_t row_count, uint8_t column_count, uint8_t frame_rate) {
    this->file_path = file_path;
    this->id = id;
    this->frame_rate = frame_rate;
    this->frame_count = row_count*column_count;
    SDL_Surface* surface = IMG_Load(file_path.c_str());
    if(surface) {
        this->texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
        this->image_width = surface->w;
        this->image_height= surface->h;
        this->frame_height = image_height/row_count;
        this->frame_width = image_width/column_count;
    } else {
        std::cerr << "ANIMATION TEXTURE_LOAD_FAILURE " << this->id << " | ATTEMPTED DIRECTORY: " << this->file_path << '\n';
    }
    SDL_FreeSurface(surface);
    build_render_targets();
}
Animation::~Animation() {
    if(texture != nullptr) SDL_DestroyTexture(texture);
}

SDL_Rect* Animation::animation_frame_at(uint8_t i) {
    return render_targets[i];
}

void Animation::build_render_targets() {
    for(int i = 0; i*frame_width < image_width; i++) {
        int x = (i*frame_width)%image_width;
        int y = 0;
        SDL_Rect frame = {x, y, static_cast<int>(frame_width), static_cast<int>(frame_height)};
        render_targets.push_back(&frame);
    }
}
