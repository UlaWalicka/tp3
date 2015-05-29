#ifndef __CHWYTAK_HPP
#define __CHWYTAK_HPP

#include "object.hpp"

namespace dzwig
{
    class Chwytak : public Object
    {
        float min_x, min_y, max_x, max_y;

        public:
        virtual void setPosition( float x, float y );
        virtual void setSize( float w, float h );
        virtual void updateAbsolutePosition();
        void setBounds( float min_x, float max_x, float min_y, float max_y );
    };
}

#endif
