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
    Brick(){
        left = 1;
        top = 1;
        right = 4;
        bottom = 4;
    };
    Brick( vec2 p, float w ) : Block( p, w, w ){

    }
    void update( float dt );
    void draw( GameRenderer *renderer ){
        renderer->drawBrick("brick",left,top,width,highlight);
    }
    
    std::string type = "brick";
};


#endif /* Brick_hpp */
