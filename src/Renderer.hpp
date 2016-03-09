//
//  Renderer.hpp
//  Breakout
//
//  Created by Rob Dawson on 28/02/2016.
//
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <stdio.h>
#include "cinder/Rand.h"
#include "cinder/gl/Fbo.h"

using namespace ci;

class GameRenderer {
  public:
    GameRenderer(){};
    GameRenderer( vec2 windowsize );
    void drawBackground();
    void drawBall( vec2 pos, float r );
    void drawPaddle( vec2 pos, float w, float h );
    void drawBrick( std::string type, float l, float t, float w, float h );
    void drawExplosion( vec2 pos, float life );
    void drawDebris( vec2 pos, float radius, float angle, float highlight);
    void drawShadows( int lightIndex, std::vector< std::vector<vec2> > shadows );
    void drawShadow( int lightIndex, std::vector<vec2> s, float dist );
    void drawLightGlows( int lightIndex, vec2 pos, float radius );
    void drawLighting();
        
  private:
    
    void setBlendFunction( std::string bf );
    gl::FboRef finalLightingFbo;
    gl::FboRef lightSourceFbo; //this will be a collection eventually
    gl::FboRef lightSourceTexture;
    
};

#endif /* Renderer_hpp */
