#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BreakoutApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void BreakoutApp::setup()
{
}

void BreakoutApp::mouseDown( MouseEvent event )
{
}

void BreakoutApp::update()
{
}

void BreakoutApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( BreakoutApp, RendererGl )
