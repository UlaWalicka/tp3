#include <SDL.h>

int main( int argc, char** argv )
{
    if(!SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) )
    {
        SDL_Window* window;
        SDL_Renderer* renderer;

        if(!SDL_CreateWindowAndRenderer( 100, 100, 1024, 768, 0, window, renderer )){
            SDL_Event event;
            
            bool quit = false;
            
            while( !quit )
            {
                while( SDL_PollEvent( &event ) ){
                    switch( event.type ){
                    
                    }
                }
            }
        }
    }
}
