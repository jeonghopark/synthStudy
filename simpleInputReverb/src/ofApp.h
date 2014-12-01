#pragma once

#include "ofMain.h"

#include "ofxTonic.h"

#define LENGTH 441000

using namespace Tonic;

class ofApp : public ofBaseApp{
    
    ofxTonicSynth synth;
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void audioRequested(float* output, int bufferSize, int nChannels);
    void audioReceived(float* input, int bufferSize, int nChannels);
  
    RingBufferWriter inputBuffer;
    
   
    ofSoundStream soundStream;
    ofSoundStream outSoundStream;
    
    //
    float buffer[LENGTH];
    int recPos;
    int playPos;
    bool RMode;
    bool PMode;


    float * _testBuffer;
    vector<TonicFloat>  fTest;
    TonicFrames * testTonicFrame;
    
    SampleTable tableBuffer;
    
};
