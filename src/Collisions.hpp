//
//  Collisions.hpp
//  Breakout
//
//  Created by Rob Dawson on 25/02/2016.
//
//

#ifndef Collisions_hpp
#define Collisions_hpp

#include <stdio.h>
#include "Block.hpp"
#include "Ball.hpp"

using namespace ci;
using namespace std;

struct Collision{
    vec2 pos;
    string dir;
    bool exists = false;
};


class CollisionManager {
  public:
    CollisionManager(){};
    CollisionManager( int w, int h );
    void affectBall( Ball * ball, vec2 pos, string dir ){
        if( dir == "top"  || dir == "bottom" ) ball->bounce( "vert" , pos.y );
        if( dir == "left" || dir == "right" ) ball->bounce( "hor" , pos.x );
    }
    bool wallCollision( Ball * ball );
    bool ballCollision( Ball * ball, Block * rec );
    Block * getWall( std::string s ){
        if( s == "top" ) return &topWall;
        if( s == "left" ) return &leftWall;
        if( s == "right" ) return &rightWall;
        return nullptr;
    }
  private:
    bool checkCollision( Ball * ball, vec2 c, vec2 d, string dir );
    Block topWall;
    Block leftWall;
    Block rightWall;
};

#endif /* Collisions_hpp */
