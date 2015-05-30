#include "font.hpp"

#include <cctype>
#include <cstdio>
#include <cstring>

Font* current;

Font::Font()
{
    tex = NULL;
    renderer = NULL;
    scale = 1;
}

void Font::setRenderer( SDL_Renderer* renderer )
{
    this->renderer = renderer;
}

void Font::setScale( int scale )
{
    this->scale = scale;
}

int Font::load( const char* file, int charw, int charh )
{
    SDL_Surface* surf = SDL_LoadBMP( file );
    Uint32 key = SDL_MapRGB( surf->format, 255, 255, 255 );
    SDL_SetColorKey( surf, SDL_TRUE, key );

    //SDL_SetColorKey( surf, SDL_TRUE, SDL_MapRGB(
    if( !surf ){
        printf("Couldn't open file %s", file );
        return -1;
    }
    tex = SDL_CreateTextureFromSurface( renderer, surf );
    if( !tex ){
        printf("Couldn't create a texture out of %s", file );
        return -2;
    }
    SDL_FreeSurface( surf );

    this->charw = charw;
    this->charh = charh;

    return 0;
}

void Font::print( const char* text, int x, int y )
{
    while( *text )
    {
        char c = *text++;
        c = toupper( c );
        int frameid;
        if( c == ' ' ){ // SPACJA jest bez grafiki
            x+=charw*scale;
            continue;
        }
        else if( c >= ' ' && c <= 'Z' ) // zamiana litery na indeks obrazka w czcionce
            frameid = c - (' '+1);
        else{
            continue;
        }
        SDL_Rect srcrect = {frameid*charw, 0, charw, charh};
        SDL_Rect destrect = {x,y, charw*scale, charh*scale};
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        if( SDL_RenderCopy( renderer, tex, &srcrect, &destrect ) )
            printf( "SDL_RenderCopy error! '%s'", SDL_GetError() );
        x+=charw*scale;
    }
}
