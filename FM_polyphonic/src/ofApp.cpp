#include "ofApp.h"


ofxTonicSynth ofApp::createSynthVoiceIn(){
    
    ofxTonicSynth _synth;
    
    ControlParameter _scale = controlSynthParameter.addParameter("Scale", 0.0);
    
    ControlParameter noteNum = _synth.addParameter("polyNote", 0.0);
    ControlParameter gateIn = _synth.addParameter("polyGate", 0.0);
    ControlParameter noteVelocity = _synth.addParameter("polyVelocity", 0.0);
    ControlParameter voiceNumber = _synth.addParameter("polyVoiceNumber", 0.0);
    
    ControlGenerator voiceFreqIn = ControlMidiToFreq().input(noteNum + _scale) + voiceNumber * 1.2; // detune the voices slightly
    
    Generator toneIn = SquareWave().freq(voiceFreqIn) * SineWave().freq(4);
    
    ADSR envIn = ADSR().attack(0.04).decay( 0.1 ).sustain(0.8).release(0.6).doesSustain(true).trigger(gateIn);
    
    ControlGenerator filterFreqIn = voiceFreqIn * 0.5 + 200;
    
    LPF24 filterIn = LPF24().Q(1.0 + noteVelocity * 0.02).cutoff( filterFreqIn );
    
    Generator outputIn = (( toneIn * envIn ) >> filterIn) * (0.02 + noteVelocity * 0.005);
    
    _synth.setOutputGen(outputIn);
    
    return _synth;
    
    
};




//--------------------------------------------------------------
void ofApp::setup(){
 
    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    
    for (int i= 0; i<8; i++) {
        poly.addVoice(createSynthVoiceIn());
    }
    
    
    synthMainOut.setOutputGen(poly);
    
    ofAddListener(ofEvents().keyPressed, this, &ofApp::keyPressed1);
    ofAddListener(ofEvents().keyPressed, this, &ofApp::keyPressed2);
    ofAddListener(ofEvents().keyPressed, this, &ofApp::keyPressed3);
    ofAddListener(ofEvents().keyPressed, this, &ofApp::keyPressed4);
    ofAddListener(ofEvents().keyPressed, this, &ofApp::keyPressed5);

    ofAddListener(ofEvents().keyReleased, this, &ofApp::keyUp1);
    ofAddListener(ofEvents().keyReleased, this, &ofApp::keyUp2);
    ofAddListener(ofEvents().keyReleased, this, &ofApp::keyUp3);
    ofAddListener(ofEvents().keyReleased, this, &ofApp::keyUp4);
    ofAddListener(ofEvents().keyReleased, this, &ofApp::keyUp5);

}


//--------------------------------------------------------------
void ofApp::update(){
    
}



//--------------------------------------------------------------
void ofApp::draw(){

    ofDrawBitmapString("1,2,3,4,5 : note Play", 30, 30);
    ofDrawBitmapString("mouse Ypos : change Scale", 30, 50);
    
}


void ofApp::receiveTrigger(float &note){
    
    noteView = ofMap( note, 0, 127, 0, ofGetHeight() );
    
}



void ofApp::keyPressed1(ofKeyEventArgs &key){
    if (key.key=='1') {
        poly.noteOn(48, 80);
        ofRemoveListener(ofEvents().keyPressed, this, &ofApp::keyPressed1);
    }
}

void ofApp::keyPressed2(ofKeyEventArgs &key){
    if (key.key=='2') {
        poly.noteOn(50, 80);
        ofRemoveListener(ofEvents().keyPressed, this, &ofApp::keyPressed2);
    }
}

void ofApp::keyPressed3(ofKeyEventArgs &key){
    if (key.key=='3') {
        poly.noteOn(52, 80);
        ofRemoveListener(ofEvents().keyPressed, this, &ofApp::keyPressed3);
    }
}

void ofApp::keyPressed4(ofKeyEventArgs &key){
    if (key.key=='4') {
        poly.noteOn(53, 80);
        ofRemoveListener(ofEvents().keyPressed, this, &ofApp::keyPressed4);
    }
}

void ofApp::keyPressed5(ofKeyEventArgs &key){
    if (key.key=='5') {
        poly.noteOn(55, 80);
        ofRemoveListener(ofEvents().keyPressed, this, &ofApp::keyPressed5);
    }
}

void ofApp::keyUp1(ofKeyEventArgs &key){
    if (key.key=='1') {
        poly.noteOff(48);
        ofAddListener(ofEvents().keyPressed, this, &ofApp::keyPressed1);
    }
}

void ofApp::keyUp2(ofKeyEventArgs &key){
    if (key.key=='2') {
        poly.noteOff(50);
        ofAddListener(ofEvents().keyPressed, this, &ofApp::keyPressed2);
    }
}

void ofApp::keyUp3(ofKeyEventArgs &key){
    if (key.key=='3') {
        poly.noteOff(52);
        ofAddListener(ofEvents().keyPressed, this, &ofApp::keyPressed3);
    }
}

void ofApp::keyUp4(ofKeyEventArgs &key){
    if (key.key=='4') {
        poly.noteOff(53);
        ofAddListener(ofEvents().keyPressed, this, &ofApp::keyPressed4);
    }
}

void ofApp::keyUp5(ofKeyEventArgs &key){
    if (key.key=='5') {
        poly.noteOff(55);
        ofAddListener(ofEvents().keyPressed, this, &ofApp::keyPressed5);
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    controlSynthParameter.setParameter("Scale", round(ofMap( mouseY, 0, ofGetHeight(), -40, 40)) );
    
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

void ofApp::audioRequested (float * output, int bufferSize, int nChannels){

    synthMainOut.fillBufferOfFloats(output, bufferSize, nChannels);

}