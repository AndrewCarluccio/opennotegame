#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include <set>
#include <string>
#include <cstdint>

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "types.hpp"
#include "engine.hpp"
#include "transform.hpp"

#define DEFAULT_TYPE entity
#define DEFAULT_ID "entity"
#define DEFAULT_TRANSPARENCY 255
#define DEFAULT_RENDER_LENGTH 100
#define DEFAULT_SCALE 1.00

class Entity {

  public:
    /** Meta information **/
    entity_type type = DEFAULT_TYPE;
    std::string id = DEFAULT_ID;
    std::string file_path;

    /** Texture Information **/
    bool is_rgb = false;
    uint8_t red, green, blue;// 8 bit unsigned integers.

    //DisplayObject* parent = NULL;

    Entity();
    Entity(std::string id, std::string file_path);
    Entity(std::string id, uint8_t red, uint8_t green, uint8_t blue);
    virtual ~Entity();

    void load_texture(std::string filepath);
    void load_rgb_texture(uint8_t red, uint8_t green, uint8_t blue);
    void set_texture(SDL_Texture* texture);

    void center_pivot();
    virtual void update();
    virtual void render(Transform & transform);

    void apply_transform(Transform & transform);
    void deapply_transform(Transform & transform);

    /** Rendering information **/
    bool is_visible = true;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    unsigned int image_width = DEFAULT_RENDER_LENGTH;
    unsigned int image_height = DEFAULT_RENDER_LENGTH*GOLDEN_RATIO;
    unsigned int alpha = DEFAULT_TRANSPARENCY;
    /** Local Coordinate Information **/
    SDL_Point position = {0, 0};
    SDL_Point pivot = {0, 0};
    double rotation = 0.0;
    double x_scale = DEFAULT_SCALE;
    double y_scale = DEFAULT_SCALE;

  private:
    SDL_Surface* surface = nullptr;
    SDL_Texture* texture = nullptr;
};


#endif /* end of include guard: ENTITY_HPP_INCLUDED */
