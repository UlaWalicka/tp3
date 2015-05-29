#ifndef __FIGURA_HPP
#define __FIGURA_HPP

namespace dzwig
{
    enum {
        FIGURA_KWADRAT,
        FIGURA_KOLO,
        FIGURA_TROJKAT,
    };

    class Figura : public Object
    {
        int rodzaj;
        bool gravity;

        virtual void update( float delta );
        virtual void setPosition( float x, float y );
    };

}

#endif
