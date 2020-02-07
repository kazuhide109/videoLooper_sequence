//
//  control.cpp
//  videoLooper_sequence
//
//  Created by LIFE_MAC_46 on 2020/01/31.
//

#include "control.hpp"

void ControlApp::setup(){
     loopSec = 2.0f; //ループする長さ
     isRec = false;
     loopNum = 0;
     recFrame = 0;
     currentFrame = 0;
     total = 120; //録画が終わるフレーム数
     
     //カメラの処理
     camWidth = 1280;
     camHeight = 720;
     vid.listDevices();
     vid.setDeviceID(1);
     vid.initGrabber(camWidth, camHeight);
     
     fbo.allocate(camWidth, camHeight, GL_RGBA);
     pix.allocate(camWidth*0.2, camHeight, 4);
     outFbo.allocate(camWidth, camHeight, GL_RGB);
     
     //保存用fboの設定
     loopSavePix.resize(lOOPTRACKNUM);
     pFrameNum = total;//loopSavePix初期の大きさ
     switch (liveMode) {
          case 0:
               maskShape.set(camWidth*0.2, camHeight);
               break;
          case 1:
               maskShape.set(camWidth, camHeight);
               break;
               
          default:
               break;
     }
     for(int i=0; i<lOOPTRACKNUM; i++){
          loopSaveFbo[i].allocate(maskShape.x, maskShape.y);
          loopSavePix[i].resize(pFrameNum);
          for(int j=0; j<pFrameNum; j++){
               loopSavePix[i][j].allocate(camWidth*0.2, camHeight, 3);
          }
          isPlay[i] =false; //再生モードをオフ
          isHave[i] = false;
     }
     
}

void ControlApp::update(){
     ofSetWindowTitle(ofToString(ofGetFrameRate()));
     
     //画面のサイズ
     width = ofGetWidth();
     height  =ofGetHeight();
     
     //フレームの繰り返し
     currentFrame++;
     if(ofGetElapsedTimef() > loopSec){
          ofResetElapsedTimeCounter();
          currentFrame = 0;
     }
     
     vid.update();//カメラ更新
     
     //カメラ画像のFbo作成
     if(vid.isFrameNew()){
          fbo.allocate(camWidth, camHeight);
          ofSetColor(255);
          fbo.begin();
          ofClear(0);
          vid.draw(0, 0, camWidth, camHeight);
          fbo.end();
     }
     
    
     
     if(isRec){
          loopSaveFbo[loopNum].begin();
          ofClear(0);
          ofSetColor(255);
          switch (liveMode) {
               case 0:
                    fbo.getTexture().drawSubsection(0, 0, maskShape.x, maskShape.y, maskShape.x*loopNum, 0, maskShape.x, maskShape.y);
                    break;
               case 1:
                    fbo.getTexture().drawSubsection(0, 0, maskShape.x, maskShape.y, 0, 0, maskShape.x, maskShape.y);
                    break;
               default:
                    break;
          }
          loopSaveFbo[loopNum].end();
          loopSaveFbo[loopNum].readToPixels(pix);
          
          loopSavePix[loopNum][recFrame] = pix;
          recFrame++;
          if(recFrame > total-1){
               isRec = false;
          }
     }
     
}

void ControlApp::draw(){
     ofSetColor(255);
     vid.draw(0, height*0.5, width*0.5, height*0.5);//キャプチャ画面
     //ループ映像表示
     outFbo.begin();
     ofClear(0);
     playLoop(0, 0, outFbo.getWidth(), outFbo.getHeight());
     outFbo.end();
     outFbo.draw(0, 0, width*0.5, height*0.5);
     
     //枠線表示
     ofNoFill();
     ofSetLineWidth(3);
     switch (liveMode) {
          case 0:
               for(int i=0; i<5; i++){
                    ofSetColor(255);
                    ofDrawRectangle(i*width*0.1, height*0.5, width*0.1, height*0.5);
                    ofDrawRectangle(i*width*0.1, 0, width*0.1, height*0.5);
               }
               ofSetColor(255, 0, 0);
               ofDrawRectangle(loopNum*width*0.1, height*0.5, width*0.1, height*0.5);
               for(int i=0; i<5; i++){
                    if(isPlay[i]){
                         ofSetColor(0, 0, 255);
                         ofDrawRectangle(i*width*0.1, 0, width*0.1, height*0.5);
                    }
               }
               break;
          case 1:
               ofSetColor(255);
               //カメラ
               ofDrawRectangle(width*0.01, height*0.51, width*0.48, height*0.48);
               //出力画面
               for(int i=0; i<3; i++){
                    for(int j=0; j<3; j++){
                         ofDrawRectangle(i*width/3*0.5, j*height/3*0.5, width/3*0.5, height/3*0.5);
                    }
               }
               for(int i=0; i<lOOPTRACKNUM; i++){
                    int k;
                    int j;
                    if(i>2 && i<=4){
                         j = 1;
                         k = i - 3;
                         if(i>3) k++;
                    }
                    else if(i>4){
                         j = 2;
                         k = i - 5;
                    }
                    else{
                         j = 0;
                         k = i;
                    }
                    if(isPlay[i]){
                         ofSetColor(0, 0, 255);
                         ofDrawRectangle(k*width/3*0.5, j*height/3*0.5, width/3*0.5, height/3*0.5);
                    }
                    if(i==loopNum){
                         ofSetColor(0, 255, 255);
                         ofDrawRectangle(k*width/3*0.5, j*height/3*0.5, width/3*0.5, height/3*0.5);
                    }
               }
               break;
          default:
               break;
     }
     ofSetColor(255);
     ofDrawRectangle(width*0.8, height*0.05, width*0.18, height*0.93);
     ofFill();
     
     //ループRec中のランプ表示
     isRec ? ofSetColor(255, 0, 0) : ofSetColor(100);
     ofDrawCircle(width*0.54, height*0.54, width*0.02);
     
     //情報の表示
     ofSetColor(255);
     stringstream playStatus;
     for(int i=0; i<lOOPTRACKNUM; i++){
          string mesii;
          if(!isHave[i]) mesii = "NONE";
          else mesii = (isPlay[i] == true) ? "PLAY" : "MUTE";
          playStatus << "LOOPTRACK: " << mesii << "\n";
     }
     stringstream mess;
         mess << "recFrame: " << recFrame
     << "\n" << "currentFrame: " << currentFrame
     << "\n" << "selectNum: " << loopNum+1
     << "\n" << playStatus.str();
     ofDrawBitmapString(mess.str(), width*0.52, height*0.6);
     
     server.publishTexture(&outFbo.getTexture());
     
}

void ControlApp::playLoop(float x, float y, float w, float h){
     ofSetColor(255);
     switch (liveMode) {
          case 0:
               vid.draw(x, y, w, h);
               for(int i=0; i<lOOPTRACKNUM; i++){
                    if(isPlay[i]){
                         tex[i].allocate(loopSavePix[i][currentFrame%total]);
                         tex[i].draw(i*w*0.2, 0, w*0.2, h);
                    }
               }
               break;
          case 1:
               vid.draw(1*w/3, 1*h/3, w/3, h/3);//キャプチャ画面
               for(int i=0; i<lOOPTRACKNUM; i++){
                    int k;
                    int j;
                    if(i>2 && i<=4){
                         j = 1;
                         k = i - 3;
                         if(i>3) k++;
                    }
                    else if(i>4){
                         j = 2;
                         k = i - 5;
                    }
                    else{
                         j = 0;
                         k = i;
                    }
                    if(isPlay[i]){
                         tex[i].allocate(loopSavePix[i][currentFrame%total]);
                         tex[i].draw(k*w/3, j*h/3, w/3, h/3);
                    }
               }
               break;
               
          default:
               break;
     }
}

void ControlApp::recClear(int _loopNum){
     isPlay[_loopNum] = false;
     loopSavePix[_loopNum].clear();
     loopSavePix[_loopNum].resize(pFrameNum);
     for(int j=0; j<pFrameNum; j++){
          loopSavePix[_loopNum][j].allocate(camWidth*0.2, camHeight, 3);
     }
}

void ControlApp::keyPressed(int key){
     for(int i=0; i<lOOPTRACKNUM; i++){
          if(key == i+49){
               loopNum = i;
          }
     }
     
     switch (key) {
          case ' ':
               isRec = true;
               recFrame = 0;
               isHave[loopNum] = true;
               break;
          case 's'://曲のスタート
               ofResetElapsedTimeCounter();
               break;
               
          case 'r'://ループ描画
               if(isHave[loopNum])
               isPlay[loopNum] = !isPlay[loopNum];
               break;
               
          case 'w'://描画削除
               recClear(loopNum);
               break;
               
          case 'e'://頭スタート
               currentFrame  = 0;
               ofResetElapsedTimeCounter();
               break;
               
          case 'z'://完全リセット
               pFrameNum = total;//loopSavePix初期の大きさ
               for(int i=0; i<lOOPTRACKNUM; i++){
                    isPlay[i] = false;
                    loopSaveFbo[i].clear();
                    loopSaveFbo[i].allocate(camWidth*0.2, camHeight);
                    loopSavePix[i].resize(pFrameNum);
                    for(int j=0; j<pFrameNum; j++){
                         loopSavePix[i][j].allocate(camWidth*0.2, camHeight, 3);
                    }
                    isPlay[i] =false; //再生モードをオフ
                    isHave[i] = false;
                    
               }
               break;
               
               
          default:
               break;
     }
}
