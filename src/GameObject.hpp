//
//  GameObject.hpp
//  Breakout
//
//  Created by Rob Dawson on 11/03/2016.
//
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include "Renderer.hpp"

class GameObject{
  public:
    virtual void draw( GameRenderer *renderer ){}
    virtual void update( float dt){}
    virtual bool isDead(){ return false; }
};

#endif /* GameObject_hpp */
