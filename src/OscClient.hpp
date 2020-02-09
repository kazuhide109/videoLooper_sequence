//
//  OscClient.hpp
//  videoLooper_sequence
//
//  Created by LIFE_MAC_46 on 2020/02/08.
//

#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "localhost"

#define PORT 9001
#define NUM_MSG_STRINGS 20

class LiveClientOsc {
public:
     
     void setup();
     void update();
     void drawDebug(int x, int y);
     
     //---------OSC
     ofTrueTypeFont font;
     ofxOscReceiver receiver;
     
     int current_msg_string;
     string msg_strings[NUM_MSG_STRINGS];
     float timers[NUM_MSG_STRINGS];
     
     
     int beat;
     ofVec4f loopON;
     ofVec3f loopStatus;
     
     int playStatus;
     ofVec2f muteStatus;
     
};
