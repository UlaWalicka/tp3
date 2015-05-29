#ifndef __CHWYTAK_HPP
#define __CHWYTAK_HPP

#include "object.hpp"
#include "figura.hpp"

namespace dzwig
{
    class Chwytak : public Object
    {
        float min_x, min_y, max_x, max_y;
        Figura* hover;
        Figura* grab;
        float grab_x, grab_y;

        public:
        virtual void setPosition( float x, float y );
        virtual void setSize( float w, float h );
        virtual void updateAbsolutePosition();
        
        void setBounds( float min_x, float max_x, float min_y, float max_y );
        void tryGrab();

        virtual void update( float delta );
        virtual void draw( SDL_Renderer* renderer );
    };
}

#endif
