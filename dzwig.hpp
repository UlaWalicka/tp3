#ifndef __DZWIG_HPP
#define __DZWIG_HPP

#include <list>

#include <SDL.h>

#include "figura.hpp"

namespace dzwig
{
    const float CHWYTAK_HSPEED = 250;
    const float CHWYTAK_VSPEED = 400;


    const int WORLDSIZE_X = 1000;
    const int WORLDSIZE_Y = 700;

    const int GROUNDLEVEL = WORLDSIZE_Y - 100;

	const int FIGURA_GRAVITY = 300;

    extern std::list<Figura*> figury;

	void init( SDL_Renderer* renderer );
	void draw( SDL_Renderer* renderer );
	void update( float delta );

	void keyEvent( SDL_KeyboardEvent event );
    void keyDown( int code );

	Figura* collides(float tx, float ty, Figura* fig = NULL);
}

#endif
