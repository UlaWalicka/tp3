#include "chwytak.hpp"
#include "dzwig.hpp"

#include <cstdio>

namespace dzwig
{

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
}
