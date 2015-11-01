#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
 
    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    
    SineWave tone = SineWave();
    
    ControlGenerator frequency = synth.addParameter("oscModulation");
//    SineWave vibratoOsc = SineWave().freq(frequency);
    
    float basePitch = 880;
    
    tone.freq( basePitch + ( SineWave().freq(30) * basePitch) * frequency);
    
    Generator output = tone;
    
    synth.setOutputGen( output );

}

//--------------------------------------------------------------
void testApp::update(){
 
    synth.setParameter( "oscModulation", ofMap(mouseY,0,ofGetHeight(),0,1) );
    
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