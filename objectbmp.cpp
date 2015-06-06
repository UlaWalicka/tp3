#include "objectbmp.hpp"
#include "object.hpp"

namespace dzwig{

    Objectbmp::Objectbmp()
    {
        texture = NULL;
    }

    int Objectbmp::loadImage( SDL_Renderer* renderer, const char* path )
    {
        // Zaladuj obrazek do surface
        SDL_Surface* surface = SDL_LoadBMP( path );
        Uint32 key = SDL_MapRGB( surface->format, 255, 255, 255 ); // kolor bialy jest dla nas przezroczysty
        SDL_SetColorKey( surface, SDL_TRUE, key );

        if( !surface ){
            printf("Couldn't open file %s", path );
            return -1;
        }
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        if( !texture ){
            printf("Couldn't create a texture out of %s", path );
            return -2;
        }
        SDL_FreeSurface( surface );

        return 0;
    }

    void Objectbmp::draw( SDL_Renderer* renderer )
    {
        if( !texture )
            Object::draw( renderer );
        else{
		SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        SDL_Rect dest{x-w/2,y-h/2,w,h};
        SDL_RenderCopy( renderer, texture, NULL, &dest );
        drawChildren( renderer ); // przekaz rysowanie do dzieci tego obiektu
        }
    }
}
