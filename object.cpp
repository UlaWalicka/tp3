#include "object.hpp"

namespace dzwig
{
    void Object::setPosition( float x, float y )
    {
        this->x = x;
        this->y = y;

        updateAbsolutePosition();

    }

    void Object::updateAbsolutePosition()
    {
        if( !this->parent ){
            this->abs_x = this->x;
            this->abs_y = this->y;
        }else{
            this->abs_x = this->parent->abs_x + this->x;
            this->abs_y = this->parent->abs_y + this->y;
        }
    }

    float Object::getX()
    {
        return this->x;
    }

    float Object::getY()
    {
        return this->y;
    }

    void Object::setSize( float w, float h )
    {
        this->w = w;
        this->h = h;
    }

    float Object::getW()
    {
        return this->w = w;
    }

    float Object::getH()
    {
        return this->h = h;
    }

	void Object::update( float delta )
	{
        updateAbsolutePosition();
        for( std::list<Object*>::iterator it = children.begin(); it != children.end(); it++ ){
            (*it)->update( delta );
        }

	}

	void Object::draw( SDL_Renderer* renderer )
	{
		SDL_SetRenderDrawColor( renderer, 255, 255, 0, 255 );
		SDL_Rect rect = { abs_x - w/2, abs_y - h/2, w, h };
		SDL_RenderDrawRect( renderer, &rect );
        for( std::list<Object*>::iterator it = children.begin(); it != children.end(); it++ ){
            (*it)->draw( renderer );
        }
	}

	bool Object::collides( float tx, float ty )
	{
        if( tx >= ( this->x - this->w/2 ) && tx < ( this->x + this->w/2 ) &&
            ty >= ( this->y - this->w/2 ) && ty < ( this->y + this->w/2 ) ){
                return true;
            }
        return false;
	}

	void Object::setParent( Object* obj )
	{
        this->parent = obj;
        obj->children.push_back( this );
        updateAbsolutePosition();
	}
}
