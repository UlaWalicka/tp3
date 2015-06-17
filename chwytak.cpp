#include "chwytak.hpp"
#include "dzwig.hpp"

#include <cstdio>
#include <list>

namespace dzwig
{
    extern std::list<Figura*> figury;

    void Chwytak::setBounds( float min_x, float max_x, float min_y, float max_y )
    {
        this->min_x = min_x;
        this->max_x = max_x;
        this->min_y = min_y;
        this->max_y = max_y;
    }

	void Chwytak::stretch(float amount)
	{
		this->h += amount;
		if (this->abs_y + this->h >= GROUNDLEVEL){
			this->h = GROUNDLEVEL - abs_y;
		}
		else if (this->h <= 40 ){
			this->h = 40;
		}
	}

    void Chwytak::updateAbsolutePosition()
    {
        Object::updateAbsolutePosition();
    }

    void Chwytak::setPosition( float x, float y )
    {
        if( x < min_x )
            this->x = min_x;
        else if( x > max_x )
            this->x = max_x;
        else
            this->x = x;

        if( y < min_y )
            this->y = min_y;
        else if( y > max_y )
            this->y = max_y;
        else
            this->y = y;
    }

    void Chwytak::update( float delta )
    {
        Object::update( delta );

        // spód chwytaka
        float hx, hy;
        hx = abs_x;
        hy = abs_y + h;

        hover = NULL;
        for( std::list<Figura*>::iterator it = figury.begin(); it != figury.end(); it++ ){
            if( (*it)->collides( hx, hy ) ){
                hover = *it;
                break;
            }
        }

		if (lowering){
			if (!grab && !hover && abs_y + h >= GROUNDLEVEL)
				lowering = false;
			else if (!grab && hover){ // && hover->getShape() == FIGURA_KOLO
				lowering = false;
				if (hover->getShape() == FIGURA_KOLO && !hover->getUp()){
					grab = hover;
					grab_x = grab->getAbsX() - abs_x;
					grab_y = grab->getAbsY() - (abs_y+h);
					grab->setGravity(false);
					grab->setLevel(0);
					if (grab->getDown())
						grab->getDown()->setUp(NULL);
					grab->setUp(NULL);
					grab->setDown(NULL);
				}
			}
			else if (grab){
				if (Figura* col = collides(grab->getX(), grab->getY() + grab->getH() / 2)){
					lowering = false;
					if (col->getShape() == FIGURA_KOLO && !col->getUp() && col->getLevel() < 3 ){
						grab->setGravity(true);
						grab = NULL;
					}
				}
				else if (grab->getY() + grab->getH()/2 >= GROUNDLEVEL){
					lowering = false;

					grab->setLevel(1);
					grab = NULL;
				}
			}
		}
		if (lowering)
			stretch( CHWYTAK_VSPEED*delta);
		else
			stretch(- CHWYTAK_VSPEED*delta);
        if( grab ){
            grab->setPosition( abs_x + grab_x, abs_y + h + grab_y );
        }
    }

    void Chwytak::draw( SDL_Renderer* renderer )
    {
        if( hover != NULL )
            SDL_SetRenderDrawColor( renderer, 255, 255, 0, 255 );
		else
            SDL_SetRenderDrawColor( renderer, 109, 62, 110, 255 );

		SDL_Rect rect = { abs_x - w/2, abs_y, w, h };
		SDL_RenderDrawRect( renderer, &rect );
        drawChildren( renderer );
    }

    void Chwytak::tryGrab()
    {
		lowering = true;
    }
}
