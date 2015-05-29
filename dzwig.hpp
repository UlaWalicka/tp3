#ifndef __DZWIG_HPP
#define __DZWIG_HPP

#include <SDL.h>

namespace dzwig
{
    const int CHWYTAK_HSPEED = 3;
    const int CHWYTAK_VSPEED = 5;

    const int WORLDSIZE_X = 1000;
    const int WORLDSIZE_Y = 700;

    const int GROUNDLEVEL = WORLDSIZE_Y - 100;

	void init();
	void draw( SDL_Renderer* renderer );
	void update( float delta );
}

#endif
