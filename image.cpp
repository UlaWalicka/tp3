#include "image.hpp"

Image::Image()
{
    this->texture = NULL;
}

int Image::loadFromFile( SDL_Renderer* renderer, const char* path )
{
        // Zaladuj obrazek do surface
        SDL_Surface* surface = SDL_LoadBMP( path );
        if( !surface ){
            printf("Couldn't open file %s", path );
            return -1;
        }
        Uint32 key = SDL_MapRGB( surface->format, 255, 255, 255 ); // kolor bialy jest dla nas przezroczysty
        SDL_SetColorKey( surface, SDL_TRUE, key );

        texture = SDL_CreateTextureFromSurface( renderer, surface );
        if( !texture ){
            printf("Couldn't create a texture out of %s", path );
            return -2;
        }
        SDL_FreeSurface( surface );

        return 0;
}

void Image::draw( SDL_Renderer* renderer, float x, float y, float w, float h )
{
        if( !texture ) return;

        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        SDL_Rect dest{x,y,w,h};
        SDL_RenderCopy( renderer, texture, NULL, &dest );
}
