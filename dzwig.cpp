#include "dzwig.hpp"

#include <iostream>
#include <list>

#include "chwytak.hpp"
#include "figura.hpp"
#include "font.hpp"
#include "object.hpp"

namespace dzwig
{

    //list<Object*> parents;

    Object dzwig_podstawa;
    Object dzwig_ramie;
    Chwytak dzwig_wysiegnik;

    std::list<Figura*> figury;

    Figura* figura;

    Font* czcionka;

	void init( SDL_Renderer* renderer )
	{
        std::cout<<"Dzwig zainicjowany"<<std::endl;

        czcionka = new Font();
        czcionka->setRenderer( renderer );
        czcionka->setScale( 2 );
        czcionka->load( "resources/marcinfonto.bmp", 6, 8 );

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

        figura = new Figura;
        figura->setPosition( 400, 0 );
        figury.push_back( figura );

        figura = new Figura( FIGURA_TROJKAT );
        figura->setPosition( 400, -100 );
        figury.push_back( figura );

        figura = new Figura;
        figura->setPosition( 400, -300 );
        figury.push_back( figura );

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

        for( std::list<Figura*>::iterator it = figury.begin(); it != figury.end(); it++ ){
            (*it)->draw( renderer );
        }

        czcionka->print( "ULKA OBCZAJ TEN TEKST ;) ( a jak jest dla Ciebie za duzy to nacisnij M )", 100, 100 );
	}

	void update( float delta )
	{
        dzwig_podstawa.update( delta );

        const Uint8* states = SDL_GetKeyboardState( NULL );

        // Poruszanie wysiegnika w prawo
        if( states[SDL_SCANCODE_RIGHT] ){
            dzwig_wysiegnik.setPosition( dzwig_wysiegnik.getX() + CHWYTAK_HSPEED*delta, dzwig_wysiegnik.getY() );
        }
        // Poruszanie wysiegnika w lewo
        if( states[SDL_SCANCODE_LEFT] ){
            dzwig_wysiegnik.setPosition( dzwig_wysiegnik.getX() - CHWYTAK_HSPEED*delta, dzwig_wysiegnik.getY() );
        }

        // Opuszczanie wysiegnika
        if( states[SDL_SCANCODE_DOWN] ){
            dzwig_wysiegnik.setSize( dzwig_wysiegnik.getW(), dzwig_wysiegnik.getH()+CHWYTAK_VSPEED*delta );
        }

        if( states[SDL_SCANCODE_UP] ){
            dzwig_wysiegnik.setSize( dzwig_wysiegnik.getW(), dzwig_wysiegnik.getH()-CHWYTAK_VSPEED*delta );
        }

        for( std::list<Figura*>::iterator it = figury.begin(); it != figury.end(); it++ ){
            (*it)->update( delta );
        }

	}

	void keyEvent( SDL_KeyboardEvent event )
	{
        keyDown( event.keysym.scancode );
	}

	void keyDown( int code )
	{
        if ( code == SDL_SCANCODE_SPACE ){
            dzwig_wysiegnik.tryGrab();
        }
        if( code == SDL_SCANCODE_M ){
            czcionka->setScale( 1 );
        }
	}

	Figura* collides( float tx, float ty )
	{
        for( std::list<Figura*>::iterator it = figury.begin(); it != figury.end(); it++ ){
            if( (*it)->collides( tx, ty ) ){
                return *it;
            }
        }
        return NULL;
	}

}
