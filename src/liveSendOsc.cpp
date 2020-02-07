//
//  liveSendOsc.cpp
//  e-motion_
//
//  Created by LIFE_MAC_46 on 2019/09/20.
//

#include "liveSendOsc.hpp"

void LiveSendOsc::setup(){
     sender.setup(HOST, PORT);
}

void LiveSendOsc::setPlay(){
     ofxOscMessage m;
     m.setAddress("/live/play");
     m.addIntArg(1);
     sender.sendMessage(m);
}

void LiveSendOsc::setStop(){
     ofxOscMessage m;
     m.setAddress("/live/stop");
     m.addIntArg(1);
     sender.sendMessage(m);
}

void LiveSendOsc::setTruckClip(int truck, int clip){
     ofxOscMessage m;
     m.setAddress("/live/play/clipslot");
     m.addIntArg(truck);
     m.addIntArg(clip);
     sender.sendMessage(m);
}


