//
//  Brick.hpp
//  Breakout
//
//  Created by Rob Dawson on 26/02/2016.
//
//

#ifndef Brick_hpp
#define Brick_hpp

#include "Block.hpp"
#include <stdio.h>

class Brick : public Block {
public:
    Brick(){};
    Brick( vec2 p, float w ) : Block( p, w, w ){}
    virtual void update( float dt ){ }
    virtual void draw( GameRenderer *renderer ){ }
    std::string type = "brick";
    bool dead = false;
    bool isDead(){ return dead; }
    void kill(){ dead = true; }
    bool casting = false;
};

class StandardBrick : public Brick {
public:
    StandardBrick(){
        type = "brick";
    };
    StandardBrick( vec2 p, float w ) : Brick( p, w ){
        type = "brick";
    }
    void draw( GameRenderer *renderer ){
        renderer->drawBrick(type,left,top,width,highlight,casting);
    }

};


class ExplosiveBrick : public Brick {
  public:
    ExplosiveBrick(){
        type = "explosive";
        count = Rand::randFloat() * 3.142;
    };
    ExplosiveBrick( vec2 p, float w ) : Brick( p, w ){
        type = "explosive";
        count = Rand::randFloat() * 3.142f;
    }
    void update( float dt ){
        count += 7.0f * dt;
    }
    void draw( GameRenderer *renderer ){
        renderer->drawExplosiveBrick(type,left,top,width,highlight,sin(count) * 0.07f );
    }
  private:
    float count = 0.0f;

};


#endif /* Brick_hpp */
