//
//  Ball.cpp
//  Breakout
//
//  Created by Rob Dawson on 25/02/2016.
//
//

#include "Ball.hpp"

Ball::Ball(){
    pos.x = 50;
    pos.y = 50;
    vel.x = -3;
    vel.y = -3;
}

void Ball::update( float dt ){
    pos += vel;
}

void Ball::draw(){
    
}