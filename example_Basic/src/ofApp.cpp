#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    
    ControlParameter volume = synth.addParameter("volume", -12.f).displayName("Volume (dbFS)").min(-60.f).max(0.f);
    ControlParameter carrierPitch = synth.addParameter("carrierPitch", 28.f).displayName("Carrier Pitch").min(20.f).max(32.f);
    ControlParameter modIndex = synth.addParameter("modIndex", 0.25f).displayName("FM Amount").min(0.f).max(1.0f);
    ControlParameter lfoAmt = synth.addParameter("lfoAmt", 0.5f).displayName("LFO Amount").min(0.f).max(1.f);
    
    Generator rCarrierFreq = ControlMidiToFreq().input(carrierPitch).smoothed();
    Generator rModFreq     = rCarrierFreq * 4.0f;
    
    Generator outputGen = SineWave()
    .freq( rCarrierFreq
          + (
             SineWave().freq( rModFreq ) * rModFreq *
             (modIndex.smoothed() * (1.0f + SineWave().freq((LFNoise().setFreq(0.5f) + 1.f) * 2.f + 0.2f) * (lfoAmt * 0.5f).smoothed()))
             )
          ) * ControlDbToLinear().input(volume).smoothed() * ((SineWave().freq(0.15f) + 1.f) * 0.75f + 0.25);
    
    synth.setOutputGen(outputGen);

}

//--------------------------------------------------------------
void ofApp::update(){
 
//    synth.setParameter( "ReceiveFQ", ofMap(mouseY,0,ofGetHeight(),0,100) );
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
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

void ofApp::audioRequested (float * output, int bufferSize, int nChannels){
    synth.fillBufferOfFloats(output, bufferSize, nChannels);
}