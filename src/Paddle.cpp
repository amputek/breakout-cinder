//
//  Paddle.cpp
//  Breakout
//
//  Created by Rob Dawson on 25/02/2016.
//
//

#include "Paddle.hpp"


Paddle::Paddle() : Block( vec2(50, 400), 200, 20 ){

}

void Paddle::update( float mx ){
    vx = mx - pos.x;
    pos.x = mx;
    pos.y = 400;
    left = pos.x - 100;
    top = pos.y-10;
    bottom = pos.y+10;
    right = pos.x + 100;
}