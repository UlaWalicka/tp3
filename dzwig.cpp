#include "dzwig.hpp"

#include <iostream>
#include <list>

#include "object.hpp"
#include "chwytak.hpp"

namespace dzwig
{

    //list<Object*> parents;

    Object dzwig_podstawa;
    Object dzwig_ramie;
    Chwytak dzwig_wysiegnik;

	void init()
	{
        std::cout<<"Dzwig zainicjowany"<<std::endl;

        dzwig_podstawa.setSize( 64, GROUNDLEVEL-100 );
        dzwig_podstawa.setPosition( 48, GROUNDLEVEL-dzwig_podstawa.getH()/2 );

        dzwig_ramie.setSize( 720, 32 );
        dzwig_ramie.setPosition( dzwig_ramie.getW()/2, -dzwig_podstawa.getH()/2+dzwig_ramie.getH()/3);
        dzwig_ramie.setParent( &dzwig_podstawa );

        dzwig_wysiegnik.setSize( 32, 32 );
        dzwig_wysiegnik.setBounds( -dzwig_ramie.getW()/4, dzwig_ramie.getW()/2 - dzwig_wysiegnik.getW()/2,
                                   dzwig_ramie.getH()/2, dzwig_ramie.getH()/2 );
        dzwig_wysiegnik.setPosition( dzwig_ramie.getW()/2, dzwig_ramie.getH()/2 );

        dzwig_wysiegnik.setParent( &dzwig_ramie );

	}



	void draw( SDL_Renderer* renderer )
	{
        SDL_SetRenderDrawColor( renderer, 110, 86, 63, 255 );
        SDL_Rect rect = {0,GROUNDLEVEL,WORLDSIZE_X, WORLDSIZE_Y - GROUNDLEVEL };
        SDL_RenderFillRect( renderer, &rect );
        SDL_SetRenderDrawColor( renderer, 64, 110, 62, 255 );
        rect.h = 16;
        SDL_RenderFillRect( renderer, &rect );

        dzwig_podstawa.draw( renderer );
	}

	void update( float delta )
	{
        dzwig_podstawa.update( delta );

        const Uint8* states = SDL_GetKeyboardState( NULL );

        // Poruszanie wysiegnika w prawo
        if( states[SDL_SCANCODE_RIGHT] ){
            dzwig_wysiegnik.setPosition( dzwig_wysiegnik.getX() + CHWYTAK_HSPEED, dzwig_wysiegnik.getY() );
        }
        // Poruszanie wysiegnika w lewo
        if( states[SDL_SCANCODE_LEFT] ){
            dzwig_wysiegnik.setPosition( dzwig_wysiegnik.getX() - CHWYTAK_HSPEED, dzwig_wysiegnik.getY() );
        }

        // Opuszczanie wysiegnika
        if( states[SDL_SCANCODE_DOWN] ){
            dzwig_wysiegnik.setSize( dzwig_wysiegnik.getW(), dzwig_wysiegnik.getH()+1 );
        }

        if( states[SDL_SCANCODE_UP] ){
            dzwig_wysiegnik.setSize( dzwig_wysiegnik.getW(), dzwig_wysiegnik.getH()-1 );
        }
	}

}
