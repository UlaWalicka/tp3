#include "figura.hpp"

#include <cmath>

#include <SDL.h>

#include "dzwig.hpp"

#define PI 3.141592654

/*
    Jak ja widzę maksymalną wielkość wieży

    Po pierwsze:
        figury potrzebują wewnętrznego licznika który zachowuje się tak:
            - jeżeli figura spadnie prosto na ziemię, to ustawiam 1
            - jeżeli figura spadnie na inną figurę, to zwiększam go o 1
            - jeżeli figura zostanie podniesiona ( gravity = false ) to go zeruję
        czyli potrzebuję funkcji w stylu setCount( int ), addCount(), getCount()

    Po drugie:
        chwytak zamiast puszczać obiekt, to powinien po naciśnieciu spacji zjeżdzać cały czas w dół,
        aż to, co trzyma nie skoliduje.
        Po kolizji należy odczytać licznik obiektu z którym skolidował ( chyba, że to ziemia, wtedy 0 ) i zwiększony o 1 zapisać do aktualnego obiektu.
        Jeżeli rezultat jest większy od 3, to nie może pozwolić puścić

    PS. opuszczanie może być zrobione poprzez ustawienie zmiennej typu boolowskiego na true i wracanie z nią na false przy natrafieniu czegokolwiek przez obiekt trzymany
    PS2. jak by co to krzycz
    PS3. bonusowe punkty od Marcinka: zrób, że nie można chwytać figur, które są "w środku" wieży ( patrz ich licznik wysokości ).
*/

namespace dzwig
{

    void drawCircle( SDL_Renderer* renderer, float x, float y, float r, size_t segments )
    {
        SDL_Point* points = new SDL_Point[segments+1]; // +1 bo punkt początkowy powinien pojawić się 2 razy
        double step = PI*2/segments;
        double ang = 0;
        for( int i=0; i<=segments; i++ ){
            points[i].x = x + cos( ang )*r;
            points[i].y = y + sin( ang )*r;
            ang+=step;
        }

        SDL_RenderDrawLines( renderer, points, segments+1 );
        delete[] points;
    }

    extern std::list<Figura*> figury;

    Figura::Figura()
    {
        gravity = true;
        shape = FIGURA_KWADRAT;
        w = Figura::W;
        h = Figura::H;
    }

    Figura::Figura( int shape )
    {
        gravity = true;
        this->shape = shape;
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

    void Figura::draw( SDL_Renderer* renderer )
    {

        SDL_SetRenderDrawColor( renderer, 100, 255, 0, 255 );
        switch( shape )
        {
            case FIGURA_KWADRAT:
            {
                SDL_Rect rect = {abs_x - w/2, abs_y - h/2, w, h };
                SDL_RenderFillRect( renderer, &rect );
            }
            break;

            case FIGURA_TROJKAT:
            {
            SDL_Point points[6] = { abs_x, abs_y - h/2, abs_x+w/2, abs_y+h/2,
                                    abs_x+w/2, abs_y+h/2, abs_x-w/2, abs_y+h/2,
                                    abs_x-w/2, abs_y+h/2, abs_x, abs_y-h/2};
            SDL_RenderDrawLines( renderer, points, 6 );
            }
            break;

            case FIGURA_KOLO:
            drawCircle( renderer, abs_x, abs_y, Figura::W/2, 40 );
            break;
        }
    }

    void Figura::update( float delta )
    {
        if( gravity ){ // mozna spasc
            Figura* collider = dzwig::collides( x, y+1+h/2 );
            if( !collider || collider == this )
                setPosition( x, y+300*delta );
        }
    }

    void Figura::setShape( int shape )
    {
        this->shape = shape;
    }

    int Figura::getShape()
    {
        return this->shape;
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
