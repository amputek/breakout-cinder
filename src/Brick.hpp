//
//  Brick.hpp
//  Breakout
//
//  Created by Rob Dawson on 26/02/2016.
//
//

#ifndef Brick_hpp
#define Brick_hpp

#include "Paddle.hpp"
#include <stdio.h>

class Brick : public Block {
public:
    Brick(){
        left = 1;
        top = 1;
        right = 4;
        bottom = 4;
    };
    Brick( vec2 p ) : Block( p, 20, 20 ){
        
    }
    void update( float dt );
    void draw();
    float vx = 0.0f;
    std::string type = "brick";
    bool markedForDeath = false;
};


#endif /* Brick_hpp */
