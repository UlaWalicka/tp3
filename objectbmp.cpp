#include "objectbmp.hpp"
#include "object.hpp"

namespace dzwig{

    
    int Objectbmp::loadImage( SDL_Renderer* renderer, const char* path )
    {
        image.loadFromFile( renderer, path );
        return 0;
    }

    void Objectbmp::draw( SDL_Renderer* renderer )
    {
        if( !image.texture )
            Object::draw( renderer );
        else{
        image.draw( renderer, abs_x - w/2, abs_y - h/2, w, h );
        drawChildren( renderer ); // przekaz rysowanie do dzieci tego obiektu
        }
    }
}
