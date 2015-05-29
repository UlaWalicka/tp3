#ifndef __OBIEKT_HPP
#define __OBIEKT_HPP

#include <list>

#include <SDL.h>

namespace dzwig
{
    class Obiekt
    {
        // Precyzja float jest zadowalająca dla skali symulacji
    private:
        float x,y,w,h;

    public:
        void setPosition( float x, float y );
        float getX();
        float getY();

        void setSize( float w, float h );

        // logika obiektu
        // delta - czas w milisekundach od ostatniego wywolania
        virtual void update( float delta );
        //
        virtual void draw( SDL_Renderer* renderer );
        virtual bool collides( float tx, float ty );
    };

}
#endif
