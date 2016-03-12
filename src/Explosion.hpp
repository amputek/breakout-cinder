//
//  Explosion.hpp
//  Breakout
//
//  Created by Rob Dawson on 11/03/2016.
//
//

#ifndef Explosion_hpp
#define Explosion_hpp

#include <stdio.h>
#include "GameObject.hpp"

using namespace ci;

class Explosion : public GameObject {
public:
    Explosion(){};
    Explosion( vec2 p ) : GameObject(){
        pos = p;
    }
    void update( float dt ){
        life += 2.0f;
    }
    void draw( GameRenderer *renderer ){
        renderer->drawExplosion( pos, life );
    }
    bool isDead(){
        return life > 100.0f;
    }
    vec2 pos;
    float life = 0.0f;
    
};


#endif /* Explosion_hpp */
