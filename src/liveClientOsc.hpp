//
//  liveClientOsc.hpp
//  e-motion_
//
//  Created by LIFE_MAC_46 on 2019/12/04.
//

#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "localhost"

#define PORTC 9001
#define NUM_MSG_STRINGS 20

class LiveClientOsc {
public:
     
     void setup();
     void update();
     void drawDebug(int x, int y);
     
     ofxOscReceiver receiver;
     
     int beat;
     
     int current_msg_string;
     string msg_strings[NUM_MSG_STRINGS];
     float timers[NUM_MSG_STRINGS];
};

