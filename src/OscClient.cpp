//
//  OscClient.cpp
//  videoLooper_sequence
//
//  Created by LIFE_MAC_46 on 2020/02/08.
//

#include "OscClient.hpp"

void LiveClientOsc::setup(){
     // listen on the given port
     receiver.setup(PORT);
     current_msg_string = 0;
     
     playStatus = 2;
}

void LiveClientOsc::update(){
     
     //---------OSC
     
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
          if(m.getAddress() == "/live/play"){
               // both the arguments are int32's
               playStatus = m.getArgAsInt32(0);
          }
          if(m.getAddress() == "/live/mute"){
               // both the arguments are int32's
               muteStatus[0] = m.getArgAsInt32(0);
               muteStatus[1] = m.getArgAsInt32(1);
                cout << "mute: " << muteStatus << endl;
          }
          if(m.getAddress() == "/live/track/info"){
               // both the arguments are int32's
               for(int i=0; i<4; i++){
                    loopON[i] = m.getArgAsInt32(i);
               }
               loopStatus[2] = m.getArgAsInt32(1);
               
          }
          if(m.getAddress() == "/live/clip/info"){
               for(int i=0; i<3; i++){
                    loopStatus[i] = m.getArgAsInt32(i);
                    cout << "loopStatus: " << loopStatus[i] << endl;
               }
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
     for(int i = 0; i < NUM_MSG_STRINGS; i++){
          ofDrawBitmapString(msg_strings[i], x, y + 15 * i);
     }
     
}
