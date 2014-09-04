#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){


    soundStream.setDeviceID(1);
    soundStream.setup(this, 0, 2, 44100, 256, 4);

//    outSoundStream.setDeviceID(2);
//    outSoundStream.setup(this, 2, 0, 44100, 256, 4);

//    soundStream.setup(2, 2, this, 44100, 256, 4);

    RingBuffer _inputS;
    inputBuffer = RingBufferWriter("_inputS", 256, 4);
    RingBufferReader inputReader = RingBufferReader().bufferName("_inputS");
    
    synth.setOutputGen(inputReader);
        
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


void ofApp::audioReceived(float* input, int bufferSize, int nChannels){
    
    inputBuffer.write(input, bufferSize, nChannels);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
