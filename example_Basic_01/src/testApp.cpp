#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    
    float basePitch = 400;

    SineWave tone = SineWave();
    
    SineWave vibratoOsc = SineWave();
    vibratoOsc.freq(1);
    
    Generator frequency = basePitch + (vibratoOsc * basePitch * 0.01);
    
    tone.freq(frequency);
    
    synth.setOutputGen( tone );

}

//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}

void testApp::audioRequested (float * output, int bufferSize, int nChannels){
    synth.fillBufferOfFloats(output, bufferSize, nChannels);
}