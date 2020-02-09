#include "ofMain.h"
#include "control.hpp"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
     ofSetupOpenGL(1920*0.75,1080*0.75,OF_WINDOW);               // <-------- setup the GL context
     
     // this kicks off the running of my app
     // can be OF_WINDOW or OF_FULLSCREEN
     // pass in width and height too:
     ofRunApp(new ControlApp());
}
