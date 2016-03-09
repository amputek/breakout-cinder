//
//  Brick.hpp
//  Breakout
//
//  Created by Rob Dawson on 26/02/2016.
//
//

#ifndef Brick_hpp
#define Brick_hpp

#include "Block.hpp"
#include <stdio.h>

class Brick : public Block {
public:
    Brick(){
        left = 1;
        top = 1;
        right = 4;
        bottom = 4;
    };
    Brick( vec2 p, float w ) : Block( p, w, w ){

    }
    void update( float dt );
    void draw( GameRenderer *renderer ){
        count += 0.15f;
        renderer->drawBrick(type,left,top,width,highlight,sin(count) * 0.02f );
    }
    float count = 0.0f;
    std::string type = "brick";
};

class ExplosiveBrick : public Brick {
  public:
    ExplosiveBrick(){
        left = 1;
        top = 1;
        right = 4;
        bottom = 4;
        type = "explosive";
        count = Rand::randFloat() * 3.0f;
    };
    ExplosiveBrick( vec2 p, float w ) : Brick( p, w ){
        type = "explosive";
        count = Rand::randFloat() * 3.0f;
    }
};


#endif /* Brick_hpp */
