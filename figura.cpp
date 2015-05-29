#include "figura.hpp"

#include "dzwig.hpp"

namespace dzwig
{

    void Figura::setPosition( float x, float y )
    {
        Object::setPosition( x, y );

    }

    void Figura::update( float delta )
    {
        if( true ) // mozna spasc
            setPosition( x, y+1 );
    }
}
