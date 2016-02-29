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
#include "Renderer.hpp"
#include <stdio.h>

class Brick : public Block {
public:
    Brick(){
        left = 1;
        top = 1;
        right = 4;
        bottom = 4;
    };
    Brick( vec2 p ) : Block( p, 20, 20 ){
        
    }
    void update( float dt );
    void draw( GameRenderer *renderer ){
        renderer->drawBrick("brick",left,top,20,20);
    }
    void kill(){
        alive = false;
    }
    bool isAlive(){
        return alive;
    }
    std::string type = "brick";
    

  private:
    bool alive = true;
    bool markedForDeath = false;
};


#endif /* Brick_hpp */
