#include "dzwig.hpp"

#include <iostream>

#include "obiekt.hpp"

namespace dzwig
{

	Obiekt ob;

	void init()
	{
        std::cout<<"Dzwig zainicjowany"<<std::endl;
		ob.setPosition( 200, 300 );
		ob.setSize( 64, 32 );
	}



	void draw( SDL_Renderer* renderer )
	{
		ob.draw( renderer );
	}

	void update()
	{

	}

}
