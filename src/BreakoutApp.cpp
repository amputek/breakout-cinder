#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Brick.hpp"
#include "Collisions.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;


float distance( vec2 a, vec2 b){
    return sqrt( pow(a.x-b.x, 2) + pow(a.y-b.y, 2));
}






class BreakoutApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void mouseMove( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    void addExplosion( vec2 loc );
    
  private:
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
    
    int i = 0;
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 5; y++) {
//            cout << "new brick: " << i << ": " << x*11 << " " << y*11 << "\n";
            bricks[i] = *new Brick( vec2( 20 + x * 22, 20 + y * 22) );
            i++;
        }
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
}

void BreakoutApp::draw(){
	gl::clear( Color( 0, 0, 0 ) );
    gl::color( Color( 0.2f, 0.5f, 0.7f ) );
    gl::drawSolidRect( Rectf( paddle.pos.x - 100, 390, paddle.pos.x + 100, 410 ) );
    gl::drawSolidCircle( ball.pos, ball.radius );
    
    for (int i = 0; i < sizeof(*bricks); i++) {
        float d = 1.0f / (distance( bricks[i].pos, ball.pos ) * 0.03f);
        float r = 0.1f + d;
        if( r > 1.0) r = 1.0;
        gl::color( Color( r, r, r ) );
        gl::drawSolidRect( Rectf( bricks[i].left, bricks[i].top, bricks[i].right, bricks[i].bottom ) );
    }
}

CINDER_APP( BreakoutApp, RendererGl )
