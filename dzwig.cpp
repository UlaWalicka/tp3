// plik naglowkowy
#include "dzwig.hpp"
// naglowki biblioteki standardowej
#include <iostream>
#include <list>
// naglowki wlasne
#include "chwytak.hpp"
#include "figura.hpp"
#include "font.hpp"
#include "object.hpp"
#include "objectbmp.hpp"


namespace dzwig
{

    //list<Object*> parents;

    Objectbmp dzwig_podstawa;
    Object dzwig_ramie;
    Chwytak dzwig_wysiegnik;

    std::list<Figura*> figury;

    Figura* figura;

    Font* czcionka;
    Font* czcionkad;

	void init( SDL_Renderer* renderer )
	{
        std::cout<<"Dzwig zainicjowany"<<std::endl;

        czcionka = new Font();
        czcionka->setRenderer( renderer );
        czcionka->setScale( 1 );
        czcionka->load( "resources/marcinfonto.bmp", 6, 8 );

        czcionkad = new Font();
        czcionkad->setRenderer( renderer );
        czcionkad->setScale( 1 );
        czcionkad->load( "resources/marcinfonto14.bmp", 9, 14 );

        dzwig_podstawa.setSize( 128, 500 );
        dzwig_podstawa.setPosition( 128, GROUNDLEVEL-dzwig_podstawa.getH()/2 );
        dzwig_podstawa.loadImage( renderer, "resources/dzwig.bmp" );

        dzwig_ramie.setSize( 720, 128 );
        dzwig_ramie.setPosition( dzwig_ramie.getW()/2 - 128, -dzwig_podstawa.getH()/2+dzwig_ramie.getH()/2);
        dzwig_ramie.setParent( &dzwig_podstawa );

        dzwig_wysiegnik.setSize( 16, 32 );
        dzwig_wysiegnik.setBounds( -dzwig_ramie.getW()/5, dzwig_ramie.getW()/2 - dzwig_wysiegnik.getW()/2,
                                   dzwig_ramie.getH()/2, dzwig_ramie.getH()/2 );
        dzwig_wysiegnik.setPosition( dzwig_ramie.getW()/2, dzwig_ramie.getH()/2 );

        dzwig_wysiegnik.setParent( &dzwig_ramie );

        figura = new Figura( FIGURA_KWADRAT );
        figura->setPosition( 220, 0 );
        figury.push_back( figura );

        figura = new Figura( FIGURA_KWADRAT );
        figura->setPosition( 400, 0 );
        figury.push_back( figura );

        figura = new Figura( FIGURA_TROJKAT );
        figura->setPosition( 300, -100 );
        figury.push_back( figura );

        figura = new Figura( FIGURA_TROJKAT );
        figura->setPosition( 500, -100 );
        figury.push_back( figura );

        figura = new Figura( FIGURA_TROJKAT );
        figura->setPosition( 450, -100 );
        figury.push_back( figura );

        figura = new Figura( FIGURA_KOLO );
        figura->setPosition( 500, -300 );
        figury.push_back( figura );

        figura = new Figura( FIGURA_KOLO );
        figura->setPosition( 350, -300 );
        figury.push_back( figura );

        figura = new Figura( FIGURA_KOLO );
        figura->setPosition( 300, -300 );
        figury.push_back( figura );

        figura = new Figura( FIGURA_KOLO );
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

        int x = 770;
        int y = 100;
        int height = 10;
        czcionkad->print( "Techniki Programowania, zadanie 3.4.3 \"Dzwig\", Marcin Szymczak i Urszula Walicka.", 4, 4 );
        czcionka->print( "Instrukcja obslugi:", x, y ); y+=height;
        czcionka->print( "Strzalki kierunkowe - ruch ramienia", x, y ); y+=height;
        czcionka->print( "Spacja - chwytanie/puszczanie figur", x, y ); y+=height*2;
        czcionka->print( "Mozna podnosic tylko kola", x, y ); y+=height;
        czcionka->print( "Mozna ulozyc na sobie max. 3 kola", x, y ); y+=height;
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
            //dzwig_wysiegnik.setSize( dzwig_wysiegnik.getW(), dzwig_wysiegnik.getH()+CHWYTAK_VSPEED*delta );
        }
        // Podnoszenie wysiegnika
        if( states[SDL_SCANCODE_UP] && dzwig_wysiegnik.getH() > 10 ){
            //dzwig_wysiegnik.setSize( dzwig_wysiegnik.getW(), dzwig_wysiegnik.getH()-CHWYTAK_VSPEED*delta );
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

	Figura* collides( float tx, float ty, Figura* fig )
	{
        for( std::list<Figura*>::iterator it = figury.begin(); it != figury.end(); it++ ){
			if ((!fig || (fig && fig != *it)) && (*it)->collides(tx, ty)){
                return *it;
            }
        }
        return NULL;
	}

}
