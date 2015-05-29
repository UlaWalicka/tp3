#include "figura.hpp"

#include "dzwig.hpp"

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

    void Figura::update( float delta )
    {
        if( gravity ){ // mozna spasc
            Figura* collider = dzwig::collides( x, y+1+h/2 );
            if( !collider || collider == this )
                setPosition( x, y+1 );
        }
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
