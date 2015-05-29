#ifndef __OBIEKT_HPP
#define __OBIEKT_HPP

#include <SDL.h>

namespace dzwig
{
    class Obiekt
    {
        // Precyzja float jest zadowalająca dla skali symulacji
	public:
        float x,y,w,h;
        // logika obiektu
        // delta - czas w milisekundach od ostatniego wywolania
        virtual void update( float delta );
        //
        virtual void draw( SDL_Renderer* renderer );
    };

}
#endif
