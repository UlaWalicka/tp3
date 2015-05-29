#ifndef __OBIEKT_HPP
#define __OBIEKT_HPP

#include <list>

#include <SDL.h>

namespace dzwig
{
    class Object
    {
        // Precyzja float jest zadowalająca dla skali symulacji
    private:
        Object* parent;
        std::list<Object*> children;

    protected:
        float x,y,w,h;
        float abs_x, abs_y;

    public:
        virtual void setPosition( float x, float y );
        float getX();
        float getY();

        virtual void setSize( float w, float h );
        float getW();
        float getH();
        // logika obiektu
        // delta - czas w milisekundach od ostatniego wywolania
        virtual void update( float delta );
        //
        virtual void draw( SDL_Renderer* renderer );
        virtual bool collides( float tx, float ty );

        void setParent( Object* parent );

        virtual void updateAbsolutePosition();

    };

}
#endif
