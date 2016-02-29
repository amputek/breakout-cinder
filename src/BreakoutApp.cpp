#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Brick.hpp"
#include "Collisions.hpp"
#include "Lighting.hpp"
#include "Math.hpp"
#include "Renderer.hpp"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace math;


class BreakoutApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void mouseMove( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    void addExplosion( vec2 loc );
    
  private:
    
    void drawShadow( vector<vec2> );
    
    void setBlendFunction( string bf );
    
    Lighting lighting;
    GameRenderer renderer;
    
    float dt = 1.0f / 60.0f;
    float mx;
    Ball ball;
    Paddle paddle;
    CollisionManager collisions;
    
    Brick bricks[100];

};

void BreakoutApp::setup(){
    setWindowSize( 400, 800 );
    paddle = *new Paddle();
    ball = *new Ball();
    collisions = *new CollisionManager( 400, 800 );
    lighting = *new Lighting();
    renderer = *new GameRenderer( toPixels( getWindowSize() ) );
    
    int i = 0;
    int y = 0;
    while( i < 100 ){
        for (int x = 0; x < 16; x++) {
            if( Rand::randBool() ){
                bricks[i] = *new Brick( vec2( 20 + x * 24, 20 + y * 24) );
                i++;
            }
        }
        y++;
    }
}

void BreakoutApp::mouseDown( MouseEvent event ){}

void BreakoutApp::mouseMove( MouseEvent event ){
    mx = event.getPos().x;
}

void BreakoutApp::update(){
    paddle.update( mx );
    ball.update( dt );
    collisions.paddleCollision( &ball, &paddle );
    collisions.wallCollision( &ball );
    collisions.brickCollision( &ball, bricks );
    for (int i = 0; i < sizeof(*bricks); i++) {
        if( bricks[i].isAlive() ){
            if( collisions.brickCollision( &ball, &bricks[i] ) ){
               bricks[i].kill();
            }
        }
    }
    renderer.drawLightGlows(0, ball.pos, 200 );
    renderer.drawShadow(0, lighting.getShadow( ball.pos, paddle ) );
    for (int i = 0; i < sizeof(*bricks); i++) {
        if( bricks[i].isAlive() ){
            renderer.drawShadow( 0, lighting.getShadow( ball.pos, bricks[i] ) );
        }
    }
}


void BreakoutApp::draw(){
    
    renderer.drawBackground();
    renderer.drawLighting();
    paddle.draw( &renderer );
    
    for (int i = 0; i < sizeof(*bricks); i++) {
        if( bricks[i].isAlive() ) bricks[i].draw( &renderer );
    }
    
    ball.draw( &renderer );
}

CINDER_APP( BreakoutApp, RendererGl )
