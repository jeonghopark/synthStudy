#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    ofSoundStreamSetup(2,2,this, 44100, 512, 4);
    
    RMode = true;
    PMode = false;
    recPos = 0;
    
    
    RingBuffer _inputS;
    inputBuffer = RingBufferWriter("_inputS", 512, 4);
    RingBufferReader inputReader = RingBufferReader().bufferName("_inputS");

    synth.setOutputGen(inputReader);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetHexColor(0xFF0000);
    ofDrawBitmapString("This is a very simple audio recording and playback demo.",20,280);
    ofDrawBitmapString("Press 'p' - playback or 'r' for recording into a 2 seconds buffer.",20,300);
    
    // get info about whats going on..
    if (RMode) { ofDrawBitmapString("Rec-Mode",20,380);};
    if (PMode) { ofDrawBitmapString("Play-Mode",20,380);};
    
}

void ofApp::audioRequested(float* output, int bufferSize, int nChannels){
    
    synth.fillBufferOfFloats(output, bufferSize, nChannels);
    
}


void ofApp::audioReceived(float* input, int bufferSize, int nChannels){
    
    
    if(RMode == true) {
        for (int i=0; i<bufferSize*nChannels; i++) {
            if(recPos<LENGTH) buffer[recPos++] = input[i];
        }
        inputBuffer.write(input, bufferSize, nChannels);
    }
    
    
    if(PMode == true) {
        for (int i = 0; i < bufferSize*nChannels; i++) {
            if(playPos<LENGTH) inputBuffer.write(&buffer[playPos++], bufferSize, nChannels);
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 'r' )  {
        // rec
        RMode = true;
        PMode = false;
        recPos = 0;
    } else if (key == 'p'){
        // play
        RMode = false;
        PMode = true;
        playPos = 0;
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
