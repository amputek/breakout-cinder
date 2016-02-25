//
//  Ball.hpp
//  Breakout
//
//  Created by Rob Dawson on 25/02/2016.
//
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>


using namespace ci;

class Ball {
  public:
    Ball();
    void update( float dt );
    void draw();
    void bounce( std::string dir, float p ){
        if( dir == "hor" ){
            vel.x = -vel.x;
            pos.x = p;
        } else if( dir == "vert" ){
            vel.y = -vel.y;
            pos.y = p;
        }

    }
    
    vec2 pos;
    vec2 vel;
    float radius = 15.0f;
};

#endif /* Ball_hpp */
