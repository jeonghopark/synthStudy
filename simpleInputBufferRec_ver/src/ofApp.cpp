#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    ofSoundStreamSetup(2,2,this, 44100, 512, 4);
    
    record = true;
    rewrite = false;
    recordPos = 0;
    
    
    sample = SampleTable(44100*2);
    player.setBuffer(sample).loop(false).trigger(mainBang);

    RingBuffer _inputS;
    inputBuffer = RingBufferWriter("_inputS", 512, 4);
    RingBufferReader inputReader = RingBufferReader().bufferName("_inputS");

    mainOut.setOutputGen(player*0.8);
    
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
    if (record) { ofDrawBitmapString("Rec-Mode",20,380);};
    if (rewrite) { ofDrawBitmapString("Play-Mode",20,380);};
    
}

void ofApp::audioRequested(float* output, int bufferSize, int nChannels){
    
    synth.fillBufferOfFloats(output, bufferSize, nChannels);
    
}


void ofApp::audioReceived(float* input, int bufferSize, int nChannels){
    
    
    if (record) {
        for (int i=0; i<bufferSize*nChannels; i++) {
            if(recordPos<44100*2) {
                buffer[recordPos++] = input[i];
            } else {
                record = false;
                rewrite = true;
            }
        }
    }
    
    
    if (rewrite) {
        TonicFloat *data = sample.dataPointer();
        
        for (int i =0; i < 44100*2; i++) {
            *data++ = buffer[i];
        }
        
        rewrite = false;
        cout << "ready"<< endl;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 'r' )  {
        // rec
        record = true;
//        rewrite = false;
        recordPos = 0;
    } else if (key == 'p'){
        // play
//        record = false;
//        rewrite = true;
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
