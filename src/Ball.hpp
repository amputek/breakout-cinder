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
    Ball(){
        pos.x = 250;
        pos.y = 300;
        vel.x = -1;
        vel.y = -2;
    }
    void update( float dt ){
        pos += vel;
    }
    void draw(){
        
    }
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
    float radius = 10.0f;
};

#endif /* Ball_hpp */
