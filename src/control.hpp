//
//  control.hpp
//  videoLooper_sequence
//
//  Created by LIFE_MAC_46 on 2020/01/31.
//
#pragma once

#define lOOPTRACKNUM 8

#include "ofMain.h"
#include "ofxSyphon.h"
#include "ofxTktrPerformanceTuning.h"

#include "OscClient.hpp"


class ControlApp: public ofBaseApp {
public:
     void setup();
     void update();
     void draw();
     void keyPressed(int key);
     
     void playLoop(float x, float y, float w, float h);
     void recClear(int _loopNum);
     void recStart(int _loopNum);
     
     ofVideoGrabber vid;//カメラ
     ofFbo fbo;//カメラのfboオブジェクト
     ofFbo loopSaveFbo[lOOPTRACKNUM];
     ofPixels pix;//fboの一時保存用
     vector<vector<ofPixels>> loopSavePix;//fbo保存用ofPixels
     ofTexture tex[lOOPTRACKNUM];
     
     int camWidth;//カメラのキャプチャ解像度
     int camHeight;
     int width;//コントロール画面の大きさ
     int height;
     int loopNum;//ループの保存先番号
     int pFrameNum = 600;
     bool isRec;//ループ記録の状態
     
     vector<int> beatBegin;
     vector<int> loopBeatNum;
     
     vector<int> recFrame;
     vector<int> currentFrame;
     vector<int> total;
     vector<int> stopper;
     vector<int> mute;
     bool isPlay[lOOPTRACKNUM];
     bool isHave[lOOPTRACKNUM];
     float loopSec;
     
     void drawVid(int x, int y, int w, int h);
     
     int liveMode = 1;
     ofVec2f maskShape;
     
     ofxSyphonServer server;
     ofFbo outFbo;
     
     LiveClientOsc liveClientOsc;
     bool test;
     
};
