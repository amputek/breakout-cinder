//
//  Lighting.hpp
//  Breakout
//
//  Created by Rob Dawson on 28/02/2016.
//
//

#ifndef Lighting_hpp
#define Lighting_hpp

#include <stdio.h>
#include "Block.cpp"
#include "Math.hpp"

using namespace math;

struct LightSource{
    vec2 pos;
    float radius;
};

class Light{
  public:
    Light(){}
    Light( vec2 p, float r ){
        pos = p;
        radius = r;
    }
    vec2 pos;
    float radius;
};

class Lighting {
  public:
    Lighting();
    vector<vec2> getShadow( vec2 source, Block &object );
    vector<Light> lights;
    
  private:
    float generateHighlight( Light &source, Block &object, float lum );
//    bool withinRange( Light &source, Block &object ){
//        return distance( source.pos, object.pos ) < source.radius;
//    }
    
};



#endif /* Lighting_hpp */
