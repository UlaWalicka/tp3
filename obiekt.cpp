#include "obiekt.hpp"

namespace dzwig
{
	void Obiekt::update( float delta )
	{

	}

	void Obiekt::draw( SDL_Renderer* renderer )
	{
		SDL_SetRenderDrawColor( renderer, 255, 255, 0, 255 );
		SDL_Rect rect = { x - w/2, y - h/2, w, h };
		SDL_RenderDrawRect( renderer, &rect );
	}
}