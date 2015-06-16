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

    class Figura: public Object
    {
        int shape;
        bool gravity;
		int level;

		Figura* up;
		Figura* down;

        static const int W = 40;
        static const int H = 40;

        public:
        Figura();
        Figura( int shape );

        void setGravity( bool );
        bool getGravity();
        virtual void update( float delta );
        virtual void draw( SDL_Renderer* renderer );
		//virtual void getPosition();
		virtual void setPosition( float x, float y );
        virtual bool collides( float tx, float ty );
        void setShape( int shape );
        int getShape();

		void setLevel(int level);
		int getLevel();

		void setDown(Figura* fig);
		void setUp(Figura* fig);
		Figura* getDown();
		Figura* getUp();
	};

}

#endif
