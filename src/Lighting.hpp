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
#include "Renderer.hpp"

using namespace math;

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
    
    void setLightPosition( int index, vec2 pos ){
        lights.at(index)->pos = pos;
    }
    
    void cast( GameRenderer* renderer, Block &object ){
        object.highlight = 0.0f;
        for (int i = 0; i < lights.size() ; i++) {
            int lightIndex = i;
            if( withinRange( lightIndex, object.pos ) ){
                float lum = getLum( lightIndex , object.pos );
                vector<vec2> shadowShape = getShadowShape( lightIndex, object );
                float edgeLum = 10.0f * lum;
                renderer->drawShadow( lightIndex, shadowShape, edgeLum );
                object.incHighlight( lum );
            }
        }
    }
    
    void drawLightGlow( GameRenderer* renderer ){
        for (int i = 0; i < lights.size() ; i++) {
            renderer->drawLightGlows(i, lights.at(i)->pos, lights.at(i)->radius );
        }
    }
    
    int getLightCount(){
        return lights.size();
    }
    
  private:
    
    vector<Light*> lights;
    
    vector<vec2> getShadowShape( int index, Block &object );
    
    float getLum( int index, vec2 objectpos  ){
        vec2 source = lights.at(index)->pos;
        float radius = lights.at(index)->radius;
        float highlight = 0.15f * (1.0 - (distance( source, objectpos) / radius ));
        if( highlight < 0.0 ) highlight = 0.0;
        return highlight;
    }
    
    bool withinRange( int index, vec2 obj ){
        vec2 source = lights.at(index)->pos;
        return distance( source, obj ) < lights.at(index)->radius;
    }
    
};



#endif /* Lighting_hpp */
