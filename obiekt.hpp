#ifndef __OBIEKT_HPP
#define __OBIEKT_HPP
namespace dzwig
{
    class Obiekt
    {
        // Precyzja float jest zadowalająca dla skali symulacji
        float x,y,w,h;
        // logika obiektu
        // delta - czas w milisekundach od ostatniego wywolania
        virtual update( float delta );
        //
        virtual draw( SDL_Renderer* renderer );
    }

}
#endif
