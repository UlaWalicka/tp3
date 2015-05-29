#ifndef __FIGURA_HPP
#define __FIGURA_HPP

#include "object.hpp"

namespace dzwig
{
    enum {
        FIGURA_KWADRAT,
        FIGURA_KOLO,
        FIGURA_TROJKAT,
    };

    class Figura : public Object
    {
        int shape;
        bool gravity;

        static const int W = 80;
        static const int H = 80;

        public:
        Figura();

        void setGravity( bool );
        bool getGravity();
        virtual void update( float delta );
        virtual void setPosition( float x, float y );
        virtual bool collides( float tx, float ty );
    };

}

#endif
