//
//  liveClientOsc.cpp
//  e-motion_
//
//  Created by LIFE_MAC_46 on 2019/12/04.
//

#include "liveClientOsc.hpp"

void LiveClientOsc::setup(){
     // listen on the given port
     cout << "listening for osc messages on port " << PORTC << "\n";
     receiver.setup(PORTC);
     current_msg_string = 0;
}

void LiveClientOsc::update(){
     
     // hide old messages
     for(int i = 0; i < NUM_MSG_STRINGS; i++){
          if(timers[i] < ofGetElapsedTimef()){
               msg_strings[i] = "";
          }
     }
     
     // check for waiting messages
     while(receiver.hasWaitingMessages()){
          // get the next message
          ofxOscMessage m;
          receiver.getNextMessage(m);
          if(m.getAddress() == "/live/beat"){
               // both the arguments are int32's
               beat = m.getArgAsInt32(0);
          }
//          else{
               // unrecognized message: display on the bottom of the screen
               string msg_string;
               msg_string = m.getAddress();
               msg_string += ": ";
               for(int i = 0; i < m.getNumArgs(); i++){
                    // get the argument type
                    msg_string += m.getArgTypeName(i);
                    msg_string += ":";
                    // display the argument - make sure we get the right type
                    if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                         msg_string += ofToString(m.getArgAsInt32(i));
                    }
                    else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                         msg_string += ofToString(m.getArgAsFloat(i));
                    }
                    else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                         msg_string += m.getArgAsString(i);
                    }
                    else{
                         msg_string += "unknown";
                    }
               }
               // add to the list of strings to display
               msg_strings[current_msg_string] = msg_string;
               timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
               current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
               // clear the next line
               msg_strings[current_msg_string] = "";
//          }
          
     }
}

void LiveClientOsc::drawDebug(int x, int y){
     ofDrawBitmapString(10, x, y);
     for(int i = 0; i < NUM_MSG_STRINGS; i++){
          ofDrawBitmapString(msg_strings[i], x, y + 15 * i);
     }
     
}
