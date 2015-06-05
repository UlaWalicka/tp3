#ifndef __OBJECTBMP_HPP
#define __OBJECTBMP_HPP
#include <SDL.h>
#include "object.hpp"

namespace dzwig{
class Objectbmp: public Object{
	
	public:
		SDL_Surface* surface;
        std::string obraz;
		SDL_Texture* pdst;

		SDL_Texture* texture;
		SDL_Renderer* renderer;
		int charw,charh;
		int scale;

		
		Objectbmp();

		void setRenderer( SDL_Renderer* renderer );
		int load( const char* obraz, int charw, int charh );
		void print( const char* pdst, int x, int y );


};


}

#endif