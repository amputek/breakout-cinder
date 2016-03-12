//
//  Paddle.cpp
//  Breakout
//
//  Created by Rob Dawson on 25/02/2016.
//
//

#include "Paddle.hpp"


Paddle::Paddle() : Block( vec2(50, 600), 200, 20 ){

}

void Paddle::update( float mx ){
    
    float oldx = pos.x;
    float newx = mx;
    if( newx < width/2 ) newx = width/2;
    if( newx > 400-width/2 ) newx = 400-width/2;
    vx = newx - oldx;
    pos.x = newx;
    
    left = pos.x - width/2;
    top = pos.y - height/2;
    bottom = pos.y + height/2;
    right = pos.x + width/2;
}

void Paddle::draw( GameRenderer *renderer ){
    renderer->drawPaddle( pos, width, height );
}