//
//  Block.hpp
//  Breakout
//
//  Created by Rob Dawson on 29/02/2016.
//
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include "GameObject.hpp"

using namespace ci;

class Block : public GameObject {
  public:
    Block() : GameObject(){
        pos = vec2(0,0);
        left = pos.x - 10;
        top = pos.y - 10;
        bottom = pos.y + 10;
        right = pos.x + 10;
        width = 50;
        height = 50;
    }
    Block( vec2 p, float w, float h ) : GameObject(){
        pos = p;
        left = pos.x - w/2;
        top = pos.y - h/2;
        bottom = pos.y + h/2;
        right = pos.x + w/2;
        width = w;
        height = h;
    }
    void incHighlight( float f ){
        highlight = f;
    }
    virtual bool isDead(){ return false; }
    ci::vec2 pos;
    float left;
    float top;
    float bottom;
    float right;
    float width;
    float height;
    float highlight;
};

#endif /* Block_hpp */
