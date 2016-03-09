#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Brick.hpp"
#include "Debris.hpp"
#include "Collisions.hpp"
#include "Lighting.hpp"
#include "Math.hpp"
#include "Renderer.hpp"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace math;

class DebrisManager{
  public:
    DebrisManager(){}
    vector<Debris*> debris;
    void addDebris( vec2 p, vec2 v ){
        for( int i = 0; i < 5; i ++){
            vec2 vel = vec2( v * Rand::randFloat(4.0f, 20.0f) );
            vel += Rand::randVec2() * Rand::randFloat(30.0f, 100.0f);
            vec2 pos = p + (Rand::randVec2() *= Rand::randFloat(0.0f, 10.0f));
            Debris* d = new Debris( pos, vel, Rand::randFloat(2.0f, 6.0f), Rand::randFloat(-10.0f, 10.0f) );
            debris.push_back( d );
        }
        
    }
    void update(float dt){
        for(int i = 0; i < debris.size();  i++){ debris.at(i)->update( dt );  }
        for( vector<Debris*>::iterator d = debris.begin(); d < debris.end(); ){
            if( (*d)->getY() > 900 ){
                d = debris.erase(d);
            } else {
                ++d;
            }
        }
        
    }
    void draw( GameRenderer *renderer){
        for(int i = 0; i < debris.size();  i++){ debris.at(i)->draw( renderer );  }
    }
    
};



class BricksManager{
public:
    BricksManager(){}
    vector<Brick*> bricks;
    void addBrick( int x, int y, string type ){
        if( type == "brick" ){
            Brick* b = new Brick( vec2( 40 + x * 18, 40 + y * 18), 14 );
            bricks.push_back( b );
        } else {
            Brick* b = new ExplosiveBrick( vec2( 40 + x * 18, 40 + y * 18), 14 );
            bricks.push_back( b );
        }
    }
    void kill( Brick* b ){
        for( vector<Brick*>::iterator j = bricks.begin(); j < bricks.end(); ){
            if( b == *j ){
                j = bricks.erase(j);
            } else {
                ++j;
            }
        }
        
    }
    void update(float dt){

    }
    void draw( GameRenderer *renderer){
        for(int i = 0; i < bricks.size();  i++){
            bricks.at(i)->draw( renderer );
        }
        
    }
    vector<Brick*> getBricks(){
        return bricks;
    }
    
};


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
    
    int fc = 0;
};


void BreakoutApp::setup(){
    setWindowSize( 400, 800 );
    setFrameRate( 60.0f );
    

    paddle = *new Paddle();
    ball = *new Ball();
    collisions = *new CollisionManager( 400, 800 );
    lighting = *new Lighting();
    renderer = *new GameRenderer( toPixels( getWindowSize() ) , lighting.getLightCount() );
    debris = *new DebrisManager();
    
    int i = 0;
    int y = 0;
    while( i < 100 ){
        for (int x = 0; x < 18; x++) { //18
            if( Rand::randFloat() < 0.7 && x != 8 && x != 9 && x != 10 ){
                string type = "brick";
                if( Rand::randFloat() < 0.2 ) type = "explsoive";
                bricks.addBrick( x, y, type );
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
//    ball.update( dt );
    debris.update( dt );
    
    vector<Brick*> allBricks = bricks.getBricks();

    if( affectBall( collisions.paddleCollision( ball.pos, ball.vel, ball.radius, &paddle ) ) ){
        ball.vel.x += paddle.vx * 0.1;
    }
    
    affectBall( collisions.wallCollision( ball.pos, ball.vel, ball.radius ) );

    for (int i = 0; i < allBricks.size() ; i++) {
        Block b = *allBricks.at(i);

        if( affectBall( collisions.brickCollision( ball.pos, ball.vel, ball.radius, &b ) ) ){
            bricks.kill( allBricks.at(i) );
            debris.addDebris( allBricks.at(i)->pos, ball.pvel );
            return;
        }
    }
    
    lighting.drawLightGlow( &renderer );

    lighting.cast( &renderer, paddle );
    ball.pos = mousepos;
    lighting.setLightPosition( 0, ball.pos );
    
    
    for (int i = 0; i < allBricks.size() ; i++) {
        Block* ab = allBricks.at(i);
        lighting.cast( &renderer, *ab );
    }
}


void BreakoutApp::draw(){
    renderer.drawBackground();
    renderer.drawLighting();
    paddle.draw( &renderer );
    bricks.draw( &renderer );
    ball.draw( &renderer );
    debris.draw( &renderer );
    
    gl::drawString( "Framerate: " + to_string(getAverageFps()), vec2( 10.0f, 10.0f ) );
}

CINDER_APP( BreakoutApp, RendererGl )
