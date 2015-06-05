#include "objectbmp.hpp"
#include "object.hpp"

namespace dzwig{
Objectbmp::Objectbmp()
{
		obraz = this->obraz;
		surface = SDL_LoadBMP(obraz);     
       pdst = SDL_CreateTextureFromSurface(renderer, surface);
       SDL_RenderCopy(renderer, pdst, &rect, &rect);
        SDL_RenderPresent(renderer);


}
Objectbmp* base;
base = new Objectbmp;
base -> obraz="resources/dzwig.bmp";



void Objectbmp::setRenderer( SDL_Renderer* renderer )
{
    this->renderer = renderer;
}

int Objectbmp::load( const char* obraz, int charw, int charh )
{
    SDL_Surface* surface = SDL_LoadBMP( obraz );
    Uint32 key = SDL_MapRGB( surface->format, 255, 255, 255 );
    SDL_SetColorKey( surface, SDL_TRUE, key );

    if( !surface ){
        printf("Couldn't open file %s", obraz );
        return -1;
    }
    texture = SDL_CreateTextureFromSurface( renderer, surface );
    if( !texture ){
        printf("Couldn't create a texture out of %s", obraz );
        return -2;
    }
    SDL_FreeSurface( surface );

    this->charw = charw;
    this->charh = charh;

    return 0;
}

void Objectbmp::print( const char* pdst, int x, int y )
{
    while( *pdst )
    {
       
        SDL_Rect srcrect = {charw, 0, charw, charh};
        SDL_Rect destrect = {x,y, charw, charh};
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        if( SDL_RenderCopy( renderer, texture, &srcrect, &destrect ) )
            printf( "SDL_RenderCopy error! '%s'", SDL_GetError() );
 
    }

}}