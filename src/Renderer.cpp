//
//  Renderer.cpp
//  Breakout
//
//  Created by Rob Dawson on 28/02/2016.
//
//

#include "Renderer.hpp"

GameRenderer::GameRenderer( vec2 windowsize, int lightCount ){
    gl::Fbo::Format format;
    format.setSamples( 8 );
    lightSourceTexture = gl::Fbo::create( 300, 300, format.depthTexture() );
    finalLightingFbo = gl::Fbo::create( 400, 800, format.depthTexture() );
    lightSourceFbo = gl::Fbo::create( 400, 800, format.depthTexture() );
    
    //create 2 for now...
    for (int i = 0; i < lightCount; i++) {
        lightSourceFbos.push_back( gl::Fbo::create( 400, 800, format.depthTexture() ) );
    }
    
    gl::ScopedViewport scpVp( ivec2( 0 ), lightSourceTexture->getSize() );
    gl::setMatricesWindow( lightSourceTexture->getSize(), false );
    gl::enableAdditiveBlending();
    
    lightSourceTexture->bindFramebuffer();
    
    gl::clear( Color( 0.0f, 0.0f, 0.0f ) );
    setBlendFunction("lighten");
    
    for (int i = 140; i > 10; i--) {
        gl::color( ColorA( 0.6f, 0.4f, 0.2f, pow(i * 0.0011f, 2) ) );
        gl::drawSolidCircle( vec2(150,150) + Rand::randVec2() * 10.0f, i );
    }
    gl::color( ColorA( 1.0f, 0.9f, 0.7f, 0.015f ) );
    for (float i = 5.0f; i < 80.0f; i *= 1.04f ) {
        gl::drawSolidCircle( vec2(150,150) + Rand::randVec2() * 7.0f, i );
    }

    lightSourceTexture->unbindFramebuffer();
    
    gl::setMatricesWindow( windowsize );
    
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
    
    
    
}



void GameRenderer::drawBackground(){
    gl::enableAdditiveBlending();
    gl::clear( Color( 0, 0, 0 ) );
}

void GameRenderer::drawBall( vec2 pos, float r ){
    gl::color( Color( 1.0f, 0.7f, 0.2f ) );
    gl::drawSolidCircle(pos, r+2);
    
    gl::color( Color( 1.0f, 1.0f, 1.0f ) );
    gl::drawSolidCircle(pos, r);
}
void GameRenderer::drawPaddle( vec2 pos, float w, float h ){
    gl::color( Color( 0.05f, 0.1f, 0.15f ) );
    gl::drawSolidRect( Rectf( pos.x - w/2, pos.y - h/2, pos.x + w/2, pos.y + h/2 ) );
}
void GameRenderer::drawBrick( std::string type, float l, float t, float w, float h, bool casting ){
    gl::color( Color( 0.01f + h * 0.5, 0.02f + h * 1.0, 0.03f + h * 1.5) );
    if( casting ) gl::color( Color(1.0f,0.0f,0.0f));
    gl::drawSolidRect( Rectf( l, t, l+w, t+w ) );
}

void GameRenderer::drawExplosiveBrick( std::string type, float l, float t, float w, float h, float c ){
    gl::color( Color( 0.1f  + (h * 2.5) + c , 0.05f + (h * 0.5) + c, 0.0f + (h * 0.5) + c ) );
    gl::drawSolidRect( Rectf( l, t, l+w, t+w ) );
    gl::color( Color( 0.3f  + (h * 2.5) + c , 0.2f + (h * 0.5) + c, 0.0f + (h * 0.5) + c ) );
    gl::drawStrokedRect( Rectf( l, t, l+w, t+w ) );
    gl::drawLine( vec2( l   + 4.0f , t + 4.0f ), vec2( l+w - 4.0f , t+w - 4.0f ) );
    gl::drawLine( vec2( l+w - 4.0f , t + 4.0f ), vec2( l   + 4.0f , t+w - 4.0f ) );

}


void GameRenderer::drawExplosion( vec2 pos, float life ){
    gl::color( ColorA( 1.0f, 0.5f, 0.4f, 1.0f - (life / 100.0f) ) );
    gl::drawStrokedCircle( pos, life );
    gl::color( ColorA( 1.0f, 0.5f, 0.4f, 0.5f - (life / 200.0f) ) );
    gl::drawSolidCircle( pos, life );
}

void GameRenderer::drawDebris( vec2 pos, float radius, float angle, float highlight){
    gl::pushModelMatrix();
    gl::color( Color( 0.1f, 0.2f, 0.3f) );
    gl::translate( pos );
    gl::rotate( angle );
    gl::drawSolidRect( Rectf(-radius,-radius,radius,radius));
    gl::popModelMatrix();
}

void GameRenderer::setBlendFunction( std::string bf ){
    if( bf == "lighten" ){
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    } else if( bf == "source-over" ){
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
}

void GameRenderer::drawLightGlows( int lightIndex, vec2 pos, float radius ){
    lightSourceFbos.at(lightIndex)->bindFramebuffer();
    gl::clear( Color(0.0f,0.0f,0.0f) );
    setBlendFunction("lighten");
    gl::color( Color( 1.0f, 1.0f, 1.0f ) );
    gl::draw( lightSourceTexture->getColorTexture(), Rectf(pos.x-radius ,pos.y-radius,pos.x+radius,pos.y+radius ) );
    lightSourceFbos.at(lightIndex)->unbindFramebuffer();
}

void GameRenderer::drawLighting(){
    
    
    //draw each lightsource fbo to final lighting fbo
    finalLightingFbo->bindFramebuffer();
    
    setBlendFunction("source-over");
    gl::clear( Color(0.0f,0.0f,0.0f) );
    
    setBlendFunction("lighten");
    gl::color( Color( 1.0f, 1.0f, 1.0f ) );
    
    for (int i = 0; i < lightSourceFbos.size() ; i++) {
        gl::draw( lightSourceFbos.at(i)->getColorTexture(), Rectf(0,0,400,800) );
    }
    
    finalLightingFbo->unbindFramebuffer();
    
    //draw final lighting fbo
    gl::draw( finalLightingFbo->getColorTexture(), Rectf(0,0,400,800) );
    setBlendFunction("source-over");
    
}



void GameRenderer::drawShadow( int lightIndex, std::vector<vec2> s, float dist ){
    
    lightSourceFbos.at(lightIndex)->bindFramebuffer();
    setBlendFunction("source-over");
    gl::color( Color( 0.0f, 0.0f, 0.0f ) );
    Shape2d shape;
    shape.moveTo( s[0] );
    shape.lineTo( s[1] );
    shape.lineTo( s[2] );
    shape.lineTo( s[3] );
    if( s.size() > 4 ) shape.lineTo( s[4] );
    shape.close();
    gl::drawSolid( shape );
    gl::color( ColorA( 1.0f, 1.0f, 1.0f, dist ) );
    if( s.size() > 4 ){
        gl::drawLine( s[0], s[4]);
        gl::drawLine( s[4], s[3]);
    } else {
        gl::drawLine( s[0], s[3]);
    }
    
    
    lightSourceFbos.at(lightIndex)->unbindFramebuffer();
}
