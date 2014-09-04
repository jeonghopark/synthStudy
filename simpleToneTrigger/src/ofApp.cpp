#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    
    ControlParameter _fq = synth.addParameter("Frequency");
    ControlParameter _trigger = synth.addParameter("Trigger");
    
    Generator sinTone = SineWave().freq(_fq);
    
    Generator env = ADSR().attack(0.001).decay(0.2).sustain(0).release(0).trigger(_trigger);
    
    synth.setOutputGen(sinTone * env);
        
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

void ofApp::audioRequested(float* output, int bufferSize, int nChannels){
    
    synth.fillBufferOfFloats(output, bufferSize, nChannels);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key=='1') {
        synth.setParameter("Trigger", 1);
        synth.setParameter("Frequency", 440);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
