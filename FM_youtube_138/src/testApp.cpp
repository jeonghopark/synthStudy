#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
 
    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    
    
    SineWave vibratoOsc = SineWave();
    vibratoOsc.freq(100);
    
    Generator tone2 = SawtoothWave().freq( 440 * vibratoOsc );
    
    ControlGenerator cutOff = synth.addParameter("cutOff");
    
    float basePitch = 440 * 2;
    
    Generator tone = SawtoothWave().freq(basePitch);
    
    Generator output = LPF24().input(tone2).Q(1).cutoff( basePitch - basePitch * 0.4 * cutOff );
    
    synth.setOutputGen( output );

}

//--------------------------------------------------------------
void testApp::update(){
 
    synth.setParameter( "cutOff", round(ofMap(mouseY,0,ofGetHeight(),0,2)) );
    
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