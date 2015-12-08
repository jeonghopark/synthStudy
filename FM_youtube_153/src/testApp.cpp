#include "testApp.h"

const int NUM_VOICES = 5;

//--------------------------------------------------------------
void testApp::setup(){
 
    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    
    float frequency = 440;
    
    ControlParameter carrierPitch = synth.addParameter("carrierPitch", 52);

    ControlGenerator amountMod = synth.addParameter("amountMod");

    Generator rCarrierFreq = ControlMidiToFreq().input(carrierPitch).smoothed();
    Generator rModFreq = rCarrierFreq * 3.489;

    
    Generator modulationTone = SineWave().freq( rModFreq ) * rModFreq * amountMod;
    
    Generator tone = SineWave().freq(rCarrierFreq + modulationTone);

    ControlGenerator envelopTrigger = synth.addParameter("trigger");
    Generator env = ADSR().attack(0.001).decay(0.7).sustain(0).release(0).trigger(envelopTrigger).legato(false);
    
    synth.setOutputGen( tone * env );

    ofAddListener(ofEvents().keyPressed, this, &testApp::keyPressedOne);
    
    ofEvent<float>* noteOut = synth.createOFEvent(carrierPitch);
    ofAddListener(* noteOut, this, &testApp::receiveTrigger);
    
}

//--------------------------------------------------------------
void testApp::update(){
 
    synth.setParameter( "amountMod", ofMap( mouseY, 0, ofGetHeight(), 0, 5 ) );
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofRect( ofGetWidth()/2-50, ofGetHeight(), 100, -noteView );
    
}


void testApp::keyPressedOne(ofKeyEventArgs &key){

    if (key.key=='1') {
        synth.setParameter("trigger", 1);
        synth.setParameter("carrierPitch", 48);
    }
    
    if (key.key=='2') {
        synth.setParameter("trigger", 1);
        synth.setParameter("carrierPitch", 50);
    }
    
    if (key.key=='3') {
        synth.setParameter("trigger", 1);
        synth.setParameter("carrierPitch", 52);
    }
    
    if (key.key=='4') {
        synth.setParameter("trigger", 1);
        synth.setParameter("carrierPitch", 53);
    }
    
    if (key.key=='5') {
        synth.setParameter("trigger", 1);
        synth.setParameter("carrierPitch", 55);
    }
    
    if (key.key=='6') {
        synth.setParameter("trigger", 1);
        synth.setParameter("carrierPitch", 57);
    }
    
    if (key.key=='7') {
        synth.setParameter("trigger", 1);
        synth.setParameter("carrierPitch", 59);
    }
    
    if (key.key=='8') {
        synth.setParameter("trigger", 1);
        synth.setParameter("carrierPitch", 60);
    }

    ofRemoveListener(ofEvents().keyPressed, this, &testApp::keyPressedOne);

}


void testApp::receiveTrigger(float & note){
    
    noteView = ofMap( note, 0, 127, 0, ofGetHeight() );

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    ofAddListener(ofEvents().keyPressed, this, &testApp::keyPressedOne);

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