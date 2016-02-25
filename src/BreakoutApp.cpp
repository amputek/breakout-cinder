#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Collisions.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class BreakoutApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void mouseMove( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    //void createDebris( Brick brick, Source source, int blockSize );
    void addExplosion( vec2 loc );
    
  private:
    float dt = 1.0f / 60.0f;
    float mx;
//    Lighting lighting;
    Ball ball;
    Paddle paddle;
    Paddle topWall;
    Paddle rightWall;
    Paddle leftWall;
    CollisionManager collisions;
    
};

void BreakoutApp::setup(){
    
    topWall = Paddle();
    topWall.pos.y = 0;
    
    leftWall.left = -50;
    leftWall.right = 0;
    leftWall.top = rightWall.top = -50;
    leftWall.bottom = rightWall.bottom = 1000;
    
    rightWall.left = 600;
    rightWall.right = 700;
    
    paddle = *new Paddle();
    ball = *new Ball();
    collisions = *new CollisionManager();
}

void BreakoutApp::mouseDown( MouseEvent event )
{
}

void BreakoutApp::mouseMove( MouseEvent event ){
    mx = event.getPos().x;
}

void BreakoutApp::update(){
    paddle.update( mx );
    ball.update( dt );
//    Collision* c = new Collision();
    collisions.ballIntercept( &ball, &paddle );
    collisions.ballIntercept( &ball, &topWall );
    collisions.ballIntercept( &ball, &leftWall );
    collisions.ballIntercept( &ball, &rightWall );
//    if( c->exists == true ){
//        std::cout << c->dir << "\n";
//        if( c->dir == "top" || c->dir == "bottom" ){
//            ball.pos.y = c->pos.y;
//            ball.vel.y = -ball.vel.y;
//        }
//        if( c->dir == "left" || c->dir == "right" ){
//            ball.pos.x = c->pos.x;
//            ball.vel.x = -ball.vel.x;
//        }
//    }
//    delete c;
}

void BreakoutApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    gl::color( Color( 20, 50, 70 ) );
    gl::drawSolidRect( Rectf( paddle.pos.x - 50,
                             400,
                             paddle.pos.x + 50,
                             410 ) );
    
    gl::drawSolidCircle( ball.pos, ball.radius );
}

CINDER_APP( BreakoutApp, RendererGl )
