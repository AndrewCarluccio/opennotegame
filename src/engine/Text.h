#ifndef TEXT_H
#define TEXT_H

#include "DisplayObjectContainer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Game.h"

using namespace std;

class Text: public DisplayObjectContainer {
    public:
        Text(string text);
        Text(string text, int width, int height, string font_path, int font_size, SDL_Color color);
        ~Text();
        void updateText(string text);
        virtual void update(set<SDL_Scancode> pressedKeys);
        virtual void draw(AffineTransform &at);
        static int count;
    private:
        string text;
        int textWidth;
        int textHeight;
        TTF_Font *font;
        SDL_Color color;

        void init(string text, int width, int height, string font_path, int font_size, SDL_Color color);
};
#endif
