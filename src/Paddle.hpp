//
//  Paddle.hpp
//  Breakout
//
//  Created by Rob Dawson on 25/02/2016.
//
//

#ifndef Paddle_hpp
#define Paddle_hpp

#include "Block.hpp"
#include "Renderer.hpp"

class Paddle : public Block {
  public:
    Paddle() ;
    void update( float dt );
    void draw( GameRenderer *renderer );
    float vx = 0.0f;
};


#include <stdio.h>

#endif /* Paddle_hpp */
