#ifndef __FONT_HPP
#define __FONT_HPP

#include <SDL.h>

class Font
{
    SDL_Texture* tex;
    SDL_Renderer* renderer;
    int charw,charh;
    int scale;

    public:
    Font();

    void setRenderer( SDL_Renderer* renderer );
    void setScale( int scale );
    int load( const char* file, int charw, int charh );
    void print( const char* text, int x, int y );
};

#endif
