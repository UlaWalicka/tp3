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
        Object();

        virtual void setPosition( float x, float y );
        float getX();
        float getAbsX();
        float getY();
        float getAbsY();

        virtual void setSize( float w, float h );
        float getW();
        float getH();

        // logika obiektu
        // delta - czas w milisekundach od ostatniego wywolania
        virtual void update( float delta );
        void updateChildren( float delta );
        // rysowanie
        virtual void draw( SDL_Renderer* renderer );
        void drawChildren( SDL_Renderer* renderer );

        void setParent( Object* parent );

        virtual void updateAbsolutePosition();

    };

}
#endif
