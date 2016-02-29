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

class Collision{
  public:
    Collision(){ };
    vec2 pos;
    string dir;
    bool exists = false;
};


class CollisionManager {
  public:
    CollisionManager(){};
    CollisionManager( int w, int h );
    void paddleCollision( Ball *ball, Block *rec );
    void wallCollision( Ball *ball );
    bool brickCollision( Ball *ball, Block *brick );
  private:
    bool ballIntercept( Ball *ball, Block *rec );
    void checkCollision( Collision *pt, vec2 a, vec2 b, vec2 c, vec2 d, string dir );
    
    Block topWall;
    Block leftWall;
    Block rightWall;
};

#endif /* Collisions_hpp */
