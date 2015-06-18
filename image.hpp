#ifndef __IMAGE_HPP
#define __IMAGE_HPP

#include <SDL.h>

struct Image
{
    SDL_Texture* texture;
    float width;
    float height;

    Image();
    int loadFromFile( SDL_Renderer* renderer, const char* path );
    void draw( SDL_Renderer* renderer, float x, float y, float w, float h );

};

#endif // __IMAGE_HPP

