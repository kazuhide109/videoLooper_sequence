#include "ofMain.h"
#include "ofApp.h"
#include "control.hpp"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
//     ofSetupOpenGL(1024,768,OF_WINDOW);               // <-------- setup the GL context
//
//     // this kicks off the running of my app
//     // can be OF_WINDOW or OF_FULLSCREEN
//     // pass in width and height too:
//     ofRunApp(new ofApp());
     
     ofGLFWWindowSettings settings;
     
//     settings.width = 1920/4;
//     settings.height = 1080/4;
//     settings.setPosition(ofVec2f(0,0));
//     settings.resizable = true;
//     shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
     
     settings.width = 1920/2;
     settings.height = 1080/2;
     settings.setPosition(ofVec2f(0,1080/4));
     settings.resizable = false;
     shared_ptr<ofAppBaseWindow> controlWindow = ofCreateWindow(settings);
     
//     shared_ptr<ofApp> mainApp(new ofApp);
     shared_ptr<ControlApp> controlApp(new ControlApp);
//     mainApp->control = controlApp;
     
     ofRunApp(controlWindow, controlApp);
//     ofRunApp(mainWindow, mainApp);
     ofRunMainLoop();

}
