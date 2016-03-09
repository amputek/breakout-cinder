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
#include "Renderer.hpp"

using namespace ci;

class Ball {
  public:
    Ball(){
        pos.x = 250;
        pos.y = 300;
        vel.x = -3;
        vel.y = -6;
    }
    void update( float dt ){
        pos += vel;
    }
    void draw( GameRenderer *renderer ){
        renderer->drawBall( pos, radius );
    }
    void bounce( std::string dir, float p ){
        pvel = vec2( vel );        
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
    vec2 pvel;
    float radius = 3.0f;
};

#endif /* Ball_hpp */
