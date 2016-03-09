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
    Collision paddleCollision( vec2 pos, vec2 vel, float r, Block *rec );
    Collision wallCollision( vec2 pos, vec2 vel, float r );
    Collision brickCollision( vec2 pos, vec2 vel, float r, Block *brick );
  private:
    Collision ballIntercept( vec2 pos, vec2 vel, float r, Block *rec );
    void checkCollision( Collision *pt, vec2 a, vec2 b, vec2 c, vec2 d, string dir );
    Block topWall;
    Block leftWall;
    Block rightWall;
};

#endif /* Collisions_hpp */
