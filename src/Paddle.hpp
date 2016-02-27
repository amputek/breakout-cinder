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

class Block {
  public:
    Block(){
        pos = vec2(0,0);
        left = pos.x - 10;
        top = pos.y - 10;
        bottom = pos.y + 10;
        right = pos.x + 10;
    }
    Block( vec2 p, float w, float h ){
        pos = p;
        left = pos.x - w/2;
        top = pos.y - h/2;
        bottom = pos.y + h/2;
        right = pos.x + w/2;
//        std::cout << "new block:" << p.x << " " << p.y << "\n";
    }

    vec2 pos;
    float left;
    float top;
    float bottom;
    float right;
};

class Paddle : public Block {
  public:
    Paddle() ;
    void update( float dt );
    void draw();
    float vx = 0.0f;
};


#include <stdio.h>

#endif /* Paddle_hpp */
