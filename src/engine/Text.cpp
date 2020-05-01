#include "Text.h"

int Text::count = 0;

Text::Text(string text) : DisplayObjectContainer() {
    int width = 700;
    int height = 300;
    string font_path = "./resources/Fonts/Roboto-Regular.ttf";
    int font_size = 50;
    // black    
    SDL_Color color = {0, 0, 0};
    init(text, width, height, font_path, font_size, color);
}

Text::Text(string text, int width, int height, string font_path, int font_size, SDL_Color color) : DisplayObjectContainer() {
    init(text, width, height, font_path, font_size, color);
}
Text::~Text() {
    TTF_CloseFont(font);

}

void Text::init(string text, int width, int height, string font_path, int font_size, SDL_Color color) {
    this->id = "text" + to_string(++count);
    this->text = text;
    this->textWidth = width;
    this->textHeight = height;
	this->font = TTF_OpenFont(font_path.c_str(), font_size);
    this->color = color;

    image = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, textWidth);
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
    position.y = -1 * textHeight;
    setTexture(texture);

    bg = new DisplayObjectContainer(id + "-bg", 255, 255, 255);
    bg->position = this->position;
    bg->height = this->height;
    bg->width = this->width;
}

void Text::updateText(string text) {
	if(image != NULL) SDL_FreeSurface(image);
	if(texture != NULL) SDL_DestroyTexture(texture);	

    image = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, textWidth);
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
    position.y = -1 * textHeight;
    setTexture(texture);
    bg->position = this->position;
    bg->height = this->height;
    bg->width = this->width;
}

void Text::update(set<SDL_Scancode> pressedKeys) {
    DisplayObjectContainer::update(pressedKeys);
    bg->visible = this->visible;
}

void Text::draw(AffineTransform &at) {
    bg->draw(at);
    DisplayObjectContainer::draw(at);
}