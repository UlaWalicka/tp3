

#include <cstdio>

#include <SDL.h>

#include "dzwig.hpp"
#include "timer.hpp"

int main( int argc, char *argv[] )
{
    if(!SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) )
    {
        SDL_Window* window;
        SDL_Renderer* renderer;

        if(!SDL_CreateWindowAndRenderer( dzwig::WORLDSIZE_X, dzwig::WORLDSIZE_Y, 0, &window, &renderer )){
            SDL_Event event;
            Timer timer;
            bool quit = false;

            //inicjalizacja symulatora
            dzwig::init( renderer );
            timer.start();

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

                        case SDL_KEYDOWN:
                            dzwig::keyEvent( event.key );
                        break;
                    }
                }

				SDL_SetRenderDrawColor( renderer, 157, 200, 204, 255 );
				SDL_RenderClear( renderer );

				timer.measure();
				dzwig::update( timer.getDelta() );

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
