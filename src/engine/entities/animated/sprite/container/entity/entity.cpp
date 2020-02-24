#include "entity.hpp"
#include "game.hpp"

Entity::Entity() {
    surface = nullptr;
    texture =  nullptr;
}

Entity::Entity(std::string id, std::string file_path) {
    this->id = id;
    this->file_path = file_path;
    this->load_texture(file_path);
}

Entity::Entity(std::string id, uint8_t red, uint8_t green, uint8_t blue) {
    this->is_rgb = true;
    this->id = id;
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->load_rgb_texture(red, green, blue);
}

Entity::~Entity() {
    if(texture != nullptr) SDL_DestroyTexture(texture);
}

void Entity::load_texture(std::string file_path) {
    surface = IMG_Load(file_path.c_str());
    if(surface) {
        texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
        this->image_width = surface->w;
        this->image_height= surface->h;
    } else {
        std::cerr << "ENTITY TEXTURE_LOAD_FAILURE " << this->id << " | ATTEMPTED DIRECTORY: " << this->file_path << '\n';
    }
    SDL_FreeSurface(surface);
    set_texture(texture);
}


void Entity::load_rgb_texture(uint8_t red, uint8_t green, uint8_t blue) {
    /** TO DO **/
    surface = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0x000000ff);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, red, green, blue));
    texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );
    set_texture(texture);
}

void Entity::set_texture(SDL_Texture* texture) {
    this->texture = texture;
}

void Entity::center_pivot(){
  this->pivot.x = image_width/2;
  this->pivot.y = image_height/2;
}

void Entity::update() {

}

void Entity::render(Transform & transform) {
    apply_transform(transform);
    transform.translate(-pivot.x, -pivot.y);
    if(texture != nullptr && is_visible) {
        SDL_Point top_left = transform.apply_transformation(ZERO, ZERO);
        SDL_Point top_right = transform.apply_transformation(image_width, ZERO);
        SDL_Point bottom_left = transform.apply_transformation(ZERO, image_height);
        SDL_Point bottom_right = transform.apply_transformation(image_width, image_height);

        SDL_Point render_origin = {0, 0};
        int render_width = static_cast<int>(distance(top_left, top_right));
        int render_height = static_cast<int>(distance(top_right, bottom_right));

        SDL_Rect render_target = {top_left.x, top_left.y, render_width, render_height};
        SDL_SetTextureAlphaMod(texture, alpha);
        SDL_RenderCopyEx(Game::renderer, texture, nullptr, &render_target, TO_DEGREES*calculate_angle(top_left, top_right), &render_origin, flip);
    }
    transform.translate(pivot.x, pivot.y);
    deapply_transform(transform);
}
void Entity::apply_transform(Transform & transform) {
    transform.translate(position.x, position.y);
    transform.rotate(rotation);
    transform.scale(x_scale, y_scale);
}
void Entity::deapply_transform(Transform & transform) {
    transform.scale(1.0/x_scale, 1.0/y_scale);
    transform.rotate(-rotation);
    transform.translate(-position.x, -position.y);
}
