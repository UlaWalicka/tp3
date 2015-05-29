#include <cstdio>

#include <SDL.h>

#include "dzwig.hpp"

int main( int argc, char *argv[] )
{
    if(!SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) )
    {
        SDL_Window* window;
        SDL_Renderer* renderer;

        if(!SDL_CreateWindowAndRenderer( 1024, 600, 0, &window, &renderer )){
            SDL_Event event;

            bool quit = false;

            //inicjalizacja symulatora
            dzwig::init();

            while( !quit )
            {
                while( SDL_PollEvent( &event ) ){
                    switch( event.type ){
                        case SDL_WINDOWEVENT:
                            switch( event.window.event )
                            {
                                //Zamkniecie okna konczy program
                                case SDL_WINDOWEVENT_CLOSE:
                                event.type = SDL_QUIT;
                                SDL_PushEvent(&event);
                                quit = true;
                                break;
                            }
                        break;
                    }
                }

				SDL_SetRenderDrawColor( renderer, 82, 82, 82, 255 );
				SDL_RenderClear( renderer );
				dzwig::update();
				dzwig::draw( renderer );
				SDL_RenderPresent( renderer );

				// Czekamy 10ms aby odciazyc procesor :)
				SDL_Delay( 10 );
            }
        }
    }else{
        printf("SDL_Init error! %s", SDL_GetError() );
    }
    SDL_Quit();

    return 0;
}
