#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    
    ControlParameter _fq = synth.addParameter("Frequency");
    
    Generator sinTone = SineWave().freq(_fq);
    
    synth.setOutputGen(sinTone);
        
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

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    synth.setParameter("Frequency", mouseY);
    
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
