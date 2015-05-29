#ifndef __DZWIG_HPP
#define __DZWIG_HPP

#include <list>

#include <SDL.h>

#include "figura.hpp"

namespace dzwig
{
    const float CHWYTAK_HSPEED = 2.5;
    const float CHWYTAK_VSPEED = 10;


    const int WORLDSIZE_X = 1000;
    const int WORLDSIZE_Y = 700;

    const int GROUNDLEVEL = WORLDSIZE_Y - 100;

    extern std::list<Figura*> figury;

	void init();
	void draw( SDL_Renderer* renderer );
	void update( float delta );

	void keyDown( SDL_KeyboardEvent event );

	Figura* collides( float tx, float ty );
}

#endif
