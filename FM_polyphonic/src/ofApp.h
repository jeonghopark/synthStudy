#pragma once

#include "ofMain.h"
#include "ofEvents.h"

#include "ofxTonic.h"

#include "PolySynth.h"


using namespace Tonic;

class ofApp : public ofBaseApp{
    
    ofxTonicSynth synthMainOut;
    
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
    
    void keyPressed1 (ofKeyEventArgs &key);
    void keyPressed2 (ofKeyEventArgs &key);
    void keyPressed3 (ofKeyEventArgs &key);
    void keyPressed4 (ofKeyEventArgs &key);
    void keyPressed5 (ofKeyEventArgs &key);

    void keyUp1 (ofKeyEventArgs &key);
    void keyUp2 (ofKeyEventArgs &key);
    void keyUp3 (ofKeyEventArgs &key);
    void keyUp4 (ofKeyEventArgs &key);
    void keyUp5 (ofKeyEventArgs &key);

    float controlScale;
    
    ofxTonicSynth createSynthVoiceIn();
    ofxTonicSynth controlSynthParameter;
    
    PolySynth poly;

    void receiveTrigger(float &note);
    float noteView;
    TonicFloat testFloat;
    
};
