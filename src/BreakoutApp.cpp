#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Brick.hpp"
#include "Debris.hpp"
#include "Explosion.hpp"
#include "EntityManager.hpp"
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
    bool affectBall( Collision col );
    void setBlendFunction( string bf );
    void addDebris( vec2 pos, vec2 v );
    
    Lighting lighting;
    GameRenderer renderer;
    
    float dt = 1.0f / 60.0f;
    float mx;
    vec2 mousepos;
    Ball ball;
    Paddle paddle;
    CollisionManager collisions;
    DebrisManager debris;
    BricksManager bricks;
    ExplosionManager explosions;
    
    int fc = 0;
};


void BreakoutApp::setup(){
    setWindowSize( 400, 800 );
    setFrameRate( 60.0f );
    
    //whats the difference?
    paddle = Paddle();
//    paddle = *new Paddle();

    //BALL "ball" is a new ball (dereferenced from constructor)
    ball = *new Ball();
    collisions = *new CollisionManager( 400, 800 );
    lighting = *new Lighting();
    renderer = *new GameRenderer( toPixels( getWindowSize() ) , lighting.getLightCount() );
    debris = *new DebrisManager();
    explosions = *new ExplosionManager();
    
    int i = 0;
    int y = 0;
    while( i < 100 ){
        for (int x = 0; x < 18; x++) {
            if( Rand::randFloat() < 0.7 && x != 8 && x != 9 && x != 10 ){
                string type = "brick";
                if( Rand::randFloat() < 0.2 ) type = "explsoive";
                bricks.add( x, y, type );
                i++;
            }
        }
        y++;
    }
    
}

void BreakoutApp::mouseDown( MouseEvent event ){}

void BreakoutApp::mouseMove( MouseEvent event ){
    mx = event.getPos().x;
    mousepos = event.getPos();
}

bool BreakoutApp::affectBall( Collision pt ){
    if( pt.exists ){
        if( pt.dir == "top" || pt.dir == "bottom" ) ball.bounce( "vert" , pt.pos.y );
        if( pt.dir == "left" || pt.dir == "right" ) ball.bounce( "hor" , pt.pos.x );
    }
    return pt.exists;
}

void BreakoutApp::update(){
    paddle.update( mx );
    bricks.update( dt );
//    ball.update( dt );
    ball.pos = mousepos;
    debris.update( dt );
    explosions.update(dt);

    int bricksSize = bricks.size();

    
    collisions.ballCollision( &ball, collisions.getWall("top") );
    collisions.ballCollision( &ball, collisions.getWall("left") );
    collisions.ballCollision( &ball, collisions.getWall("right") );
    
    if( collisions.ballCollision( &ball, &paddle ) ){
        ball.vel.x += paddle.vx * 0.1;
    }

    for (int i = 0; i < bricksSize; i++) {
        GameObject bb = *bricks.get( i );
        Block b = *dynamic_cast<Block*>( bricks.get(i) );
        Brick ab = *dynamic_cast<Brick*>( bricks.get(i) );

        if( collisions.ballCollision( &ball, &b ) ){
            bricks.kill( i );
            debris.add( b.pos, ball.pvel );
            if( ab.type == "explosive" ) explosions.add( b.pos );
            return;
        }
    }

    lighting.setLightPosition( 0, ball.pos );
    lighting.drawLightGlow( &renderer );
    lighting.cast( &renderer, paddle );
    
//    bricks.checkCast( ball.pos );
    
    for (int i = 0; i < bricksSize; i++) {
        Block* b = dynamic_cast<Block*>( bricks.get(i) );
        lighting.cast( &renderer, *b );
    }
}


void BreakoutApp::draw(){
    renderer.drawBackground();
    renderer.drawLighting();
    paddle.draw( &renderer );
    bricks.draw( &renderer );
    ball.draw( &renderer );
    explosions.draw( &renderer );
    debris.draw( &renderer );
    
    gl::drawString( "Framerate: " + to_string(getAverageFps()), vec2( 10.0f, 10.0f ) );
}

CINDER_APP( BreakoutApp, RendererGl )
