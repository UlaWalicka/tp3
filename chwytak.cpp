#include "chwytak.hpp"
#include "dzwig.hpp"

#include <cstdio>
#include <list>

namespace dzwig
{
    extern std::list<Figura*> figury;

    void Chwytak::setBounds( float min_x, float max_x, float min_y, float max_y )
    {
        this->min_x = min_x;
        this->max_x = max_x;
        this->min_y = min_y;
        this->max_y = max_y;
    }

    void Chwytak::updateAbsolutePosition()
    {
        Object::updateAbsolutePosition();
        this->abs_y+= this->h/2;
    }

    void Chwytak::setPosition( float x, float y )
    {
        if( x < min_x )
            this->x = min_x;
        else if( x > max_x )
            this->x = max_x;
        else
            this->x = x;

        if( y < min_y )
            this->y = min_y;
        else if( y > max_y )
            this->y = max_y;
        else
            this->y = y;
    }

    void Chwytak::setSize( float w, float h )
    {
        this->w = w;
        if( this->abs_y+h/2 > GROUNDLEVEL )
            this->h = (GROUNDLEVEL - this->abs_y)*2;
        else
            this->h = h;
    }

    void Chwytak::update( float delta )
    {
        Object::update( delta );

        // spód chwytaka
        float hx, hy;
        hx = abs_x;
        hy = abs_y + h/2;

        hover = NULL;
        for( std::list<Figura*>::iterator it = figury.begin(); it != figury.end(); it++ ){
            if( (*it)->collides( hx, hy ) ){
                hover = *it;
                break;
            }
        }

        if( grab ){
            grab->setPosition( abs_x + grab_x, abs_y + h/2 + grab_y );
        }
    }

    void Chwytak::draw( SDL_Renderer* renderer )
    {
        if( hover != NULL )
            SDL_SetRenderDrawColor( renderer, 255, 255, 0, 255 );
		else
            SDL_SetRenderDrawColor( renderer, 109, 62, 110, 255 );

		SDL_Rect rect = { abs_x - w/2, abs_y - h/2, w, h };
		SDL_RenderDrawRect( renderer, &rect );

        drawChildren( renderer );
    }

    void Chwytak::tryGrab()
    {
        if( grab ){
            grab->setGravity( true );
            grab = NULL;
        }else if( hover ){
            grab = hover;
            grab_x = grab->getAbsX() - abs_x;
            grab_y = grab->getAbsY() - ( abs_y + h/2 );
            grab->setGravity( false );
        }
    }
}
