#pragma once

#include "ofMain.h"

#include "ofxGui.h"

#include "ofxTonic.h"

#include "ofxFft.h"

#define KEY_NUM 8

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
    
    void keyPressedOne(ofKeyEventArgs &key);
    float sendfq;
    bool bKey[KEY_NUM];

    void plot(vector<float>& buffer, float scale, float offset);

    int plotHeight, bufferSize;
    
	ofxFft* fft;
	
	ofMutex soundMutex;
	vector<float> drawBins, middleBins, audioBins;

    ofxPanel gui;
    ofxFloatSlider amountModGui;
    ofxFloatSlider amountFQGui;
    ofxLabel viewText;
    bool bGuiDraw;

};
