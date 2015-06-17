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
            - jeżeli figura spadnie na inną figurę, to ustawiam go na figure niżej + 1
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
		level = 0;
		up = down = NULL;
    }

    Figura::Figura( int shape )
    {
        gravity = true;
        this->shape = shape;
        w = Figura::W;
        h = Figura::H;
		level = 0;
		up = down = NULL;
    }

	void Figura::setUp(Figura* fig)
	{
		this->up = fig;
	}

	void Figura::setDown(Figura* fig)
	{
		this->down = fig;
	}

	Figura* Figura::getUp()
	{
		return this->up;
	}

	Figura* Figura::getDown()
	{
		return this->down;
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
				for (int i = 0; i < 4; i++){
					SDL_Point points[6] = { abs_x, abs_y - h / 2 + i, abs_x + w / 2 - i, abs_y + h / 2 - i,
						abs_x + w / 2 - i, abs_y + h / 2 - i, abs_x - w / 2 + i, abs_y + h / 2 - i,
						abs_x - w / 2 + i, abs_y + h / 2 - i, abs_x, abs_y - h / 2 + i };
					SDL_RenderDrawLines(renderer, points, 6);
				}
			}
            break;

            case FIGURA_KOLO:
				for (int i = 0; i < 4; i++){
					drawCircle(renderer, abs_x, abs_y, Figura::W / 2 - i, 40);
				}
			break;
        }
    }

    void Figura::update( float delta )
    {
        if( gravity ){ // mozna spasc
            Figura* collider = dzwig::collides( x, y+1+h/2, this );
			if (collider){
				this->setLevel(collider->getLevel() + 1);
				this->setDown(collider);
				collider->setUp(this);
			}
			else if (!collider){
				setPosition(x, y + FIGURA_GRAVITY*delta);
				this->setLevel(1);
			}
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
        if( tx >= this->abs_x - this->w/2 && tx < this->abs_x + this->w/2 &&
            ty >= this->abs_y - this->h/2 && ty < this->abs_y + this->h/2 )
            return true;
        return false;
    }

	void Figura::setLevel(int level){
		if (getShape() == FIGURA_KOLO)
			this->level = level;
		else {
			this->level = 999;
		}
	}

	int Figura::getLevel(){
		return this->level;
	}

}
