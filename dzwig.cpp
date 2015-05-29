#include "dzwig.hpp"

#include <iostream>

#include "obiekt.hpp"

namespace dzwig
{

	Obiekt ob;

	void init()
	{
        std::cout<<"Dzwig zainicjowany"<<std::endl;
		ob.x = 200;
		ob.y = 150;
		ob.w = 64;
		ob.h = 32;
	}



	void draw( SDL_Renderer* renderer )
	{
		ob.draw( renderer );
	}

	void update()
	{

	}

}
