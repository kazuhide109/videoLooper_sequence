//
//  liveSendOsc.hpp
//  e-motion_
//
//  Created by LIFE_MAC_46 on 2019/09/20.
//
#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 9000

class LiveSendOsc {
     public:
     
          void setup();
          void setPlay();
          void setStop();
          void setTruckClip(int truck, int clip);
     
     ofxOscSender sender;
     
     
     
};
