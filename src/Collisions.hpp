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
#include "Paddle.hpp"
#include "Ball.hpp"

using namespace ci;
using namespace std;

class Collision{
  public:
    vec2 pos;
    string dir;
    bool exists = false;
    Collision(){
        
    }
};


class CollisionManager {
  public:
    CollisionManager();

    vec2 areaSize;

    void ballIntercept( Ball *ball, Paddle *rec );
  private:
    void checkCollision( Collision *pt, vec2 a, vec2 b, vec2 c, vec2 d, string dir );
};

#endif /* Collisions_hpp */
