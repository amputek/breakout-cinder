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
    float radius = 150.0f;
    float lum = 1.0f;
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
    vector<vec2> getShadowShape( int index, Block &object );
    vector< vector<vec2> > getShadows( vec2 source, vector<Block*> objects );
    
    float getLum( int index, vec2 objectpos  ){

        vec2 source = lights.at(index)->pos;
        float radius = lights.at(index)->radius;
        
        float highlight = 0.15f * (1.0 - (distance( source, objectpos) / 150.0f));
        if( highlight < 0.0 ) highlight = 0.0;
        return highlight;
    }
    
    vector<Light*> lights;
    
    bool withinRange( int index, vec2 obj ){
        vec2 source = lights.at(index)->pos;
        return distance( source, obj ) < 115.0f;
    }
    
  private:
    float generateHighlight( Light &source, Block &object, float lum );
//    bool withinRange( Light &source, Block &object ){
//        return distance( source.pos, object.pos ) < source.radius;
//    }
    
};



#endif /* Lighting_hpp */
