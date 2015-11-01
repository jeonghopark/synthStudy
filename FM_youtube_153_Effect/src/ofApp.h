#pragma once

#include "ofMain.h"
#include "ofEvents.h"

#include "ofxTonic.h"

#include "ofxGui.h"


using namespace Tonic;

class ofApp : public ofBaseApp{
    
    ofxTonicSynth synth;
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void audioRequested (float * output, int bufferSize, int nChannels);
    
    
    float sendfq;
    
    void keyPressedOne (ofKeyEventArgs &key);
    
    void receiveTrigger(float & note);
    float noteView;
    
    ofxPanel gui;
    ofxFloatSlider amountMod;
    ofxFloatSlider fqRatio;
    ofxFloatSlider pitchChangeRatioGui;
    ofxIntSlider pitchScaleChangeGui;
    
};
