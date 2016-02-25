//
//  Paddle.hpp
//  Breakout
//
//  Created by Rob Dawson on 25/02/2016.
//
//

#ifndef Paddle_hpp
#define Paddle_hpp

using namespace ci;

class Paddle {
  public:
    Paddle();
    
    void update( float dt );
    void draw();
    
    //void createDebris( Brick brick, Source source, int blockSize );
    void addExplosion( vec2 loc );
    
//  private:
    vec2 pos = vec2(300,0);
    float left = pos.x - 1000;
    float top = pos.y-10;
    float bottom = pos.y+10;
    float right = pos.x + 1000;
    
    float vx = 0.0f;
};


#include <stdio.h>

#endif /* Paddle_hpp */
