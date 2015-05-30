#include "figura.hpp"

#include "dzwig.hpp"

#include <SDL.h>

namespace dzwig
{
    extern std::list<Figura*> figury;

    Figura::Figura()
    {
        gravity = true;
        shape = FIGURA_KWADRAT;
        w = Figura::W;
        h = Figura::H;
    }

    Figura::Figura( int shape )
    {
        gravity = true;
        this->shape = shape;
        w = Figura::W;
        h = Figura::H;
    }

    void Figura::setGravity( bool gravity )
    {
        this->gravity = gravity;
    }

    bool Figura::getGravity()
    {
        return this->gravity;
    }

    void Figura::setPosition( float x, float y )
    {
        Object::setPosition( x, y );
        if( abs_y + h/2 > GROUNDLEVEL ){
            Object::setPosition( x, GROUNDLEVEL - h/2 );
        }
    }

    void Figura::draw( SDL_Renderer* renderer )
    {

        SDL_SetRenderDrawColor( renderer, 100, 255, 0, 255 );
        switch( shape )
        {
            case FIGURA_KWADRAT:
            {
                SDL_Rect rect = {abs_x - w/2, abs_y - h/2, w, h };
                SDL_RenderFillRect( renderer, &rect );
            }
            break;

            case FIGURA_TROJKAT:
            SDL_Point points[6] = { abs_x, abs_y - h/2, abs_x+w/2, abs_y+h/2,
                                    abs_x+w/2, abs_y+h/2, abs_x-w/2, abs_y+h/2,
                                    abs_x-w/2, abs_y+h/2, abs_x, abs_y-h/2};
            SDL_RenderDrawLines( renderer, points, 6 );
            break;
        }
    }

    void Figura::update( float delta )
    {
        if( gravity ){ // mozna spasc
            Figura* collider = dzwig::collides( x, y+1+h/2 );
            if( !collider || collider == this )
                setPosition( x, y+300*delta );
        }
    }

    void Figura::setShape( int shape )
    {
        this->shape = shape;
    }

    bool Figura::collides( float tx, float ty )
    {

        //if(
        if( tx >= this->abs_x - this->w/2 && tx < this->abs_x + this->w/2 &&
            ty >= this->abs_y - this->h/2 && ty < this->abs_y + this->h/2 )
            return true;
        return false;
    }
}
