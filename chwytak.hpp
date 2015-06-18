#ifndef __CHWYTAK_HPP
#define __CHWYTAK_HPP

#include "figura.hpp"
#include "image.hpp"
#include "object.hpp"

namespace dzwig
{
    class Chwytak : public Object
    {
        float min_x, min_y, max_x, max_y;
        Figura* hover;
        Figura* grab;
        float grab_x, grab_y;
		bool lowering;

        Image image_chwytak;
        Image image_base;

        public:
        virtual void setPosition( float x, float y );
        virtual void updateAbsolutePosition();

        void setBounds( float min_x, float max_x, float min_y, float max_y );
		void stretch(float amount);
        void tryGrab();

        void loadImages( SDL_Renderer* renderer );

        virtual void update( float delta );
        virtual void draw( SDL_Renderer* renderer );
    };
}

#endif
