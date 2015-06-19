#ifndef __OBJECTBMP_HPP
#define __OBJECTBMP_HPP
#include <SDL.h>
#include "object.hpp"
#include "image.hpp"

namespace dzwig{
class Objectbmp: public Object{
    private:
        Image image;
	public:

		int loadImage( SDL_Renderer* renderer, const char* path );
        virtual void draw( SDL_Renderer* renderer );
};


}

#endif
