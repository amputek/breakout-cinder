//
//  Debris.hpp
//  Breakout
//
//  Created by Rob Dawson on 29/02/2016.
//
//

#ifndef Debris_hpp
#define Debris_hpp

#include <stdio.h>
#include "Renderer.hpp"

using namespace ci;

class Debris {
  public:
    Debris(){
        pos = vec2(0,0);
        vel = vec2(0,0);
        radius = 5.0f;
        angle = 0.0f;
        vr = 0.0f;
    }
    Debris( vec2 p, vec2 v, float r, float avr ){
        pos = p;
        vel = vec2(v * 2.0f);
        radius = r;
        vr = avr * 5.0f;
    }
    void update( float dt ){
        pos += (vel * dt);
        vel *= (1.0 - (dt * 0.5));
//        vel *= 0.998;
        vr *= (1.0 - dt * 0.01);
        angle += (vr * dt);
        vel.y += (1000.0f * dt);
    }
    void draw( GameRenderer *renderer ){
        renderer->drawDebris( pos, radius, angle, 1.0f );
    }
    float getY(){
        return pos.y;
    }
    
  private:
    vec2 pos;
    vec2 vel;
    float radius = 5.0f;
    float angle = 0.0f;
    float vr = 0.0f;
};



#endif /* Debris_hpp */
