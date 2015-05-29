#include "obiekt.hpp"

namespace dzwig
{
    void Obiekt::setPosition( float x, float y )
    {
        this->x = x;
        this->y = y;
    }

    float Obiekt::getX()
    {
        return this->x;
    }

    float Obiekt::getY()
    {
        return this->y;
    }

    void Obiekt::setSize( float w, float h )
    {
        this->w = w;
        this->h = h;
    }

	void Obiekt::update( float delta )
	{

	}

	void Obiekt::draw( SDL_Renderer* renderer )
	{
		SDL_SetRenderDrawColor( renderer, 255, 255, 0, 255 );
		SDL_Rect rect = { x - w/2, y - h/2, w, h };
		SDL_RenderDrawRect( renderer, &rect );
	}

	bool Obiekt::collides( float tx, float ty )
	{
        if( tx >= ( this->x - this->w/2 ) && tx < ( this->x + this->w/2 ) &&
            ty >= ( this->y - this->w/2 ) && ty < ( this->y + this->w/2 ) ){
                return true;
            }
        return false;
	}
}
