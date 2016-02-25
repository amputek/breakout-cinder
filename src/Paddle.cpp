//
//  Paddle.cpp
//  Breakout
//
//  Created by Rob Dawson on 25/02/2016.
//
//

#include "Paddle.hpp"


Paddle::Paddle(){
    
}

void Paddle::update( float mx ){
    vx = mx - pos.x;
    pos.x = mx;
    pos.y = 400;
    left = pos.x - 1000;
    top = pos.y-10;
    bottom = pos.y+10;
    right = pos.x + 1000;
}