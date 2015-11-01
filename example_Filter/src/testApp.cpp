#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    
    // create a new oscillator which we'll use for the actual audio signal
    
    // create a sine wave we'll use for some vibrato
    
    
    float frequency = 440;
    
    SawtoothWave().freq(frequency);
    
    Generator tone = SawtoothWave().freq(frequency);
    
    tone = LPF12().input(tone).Q(100).cutoff(frequency*2 + SineWave().freq(30) * 1.5 * frequency);
    
    ControlGenerator envelopeTrigger = synth.addParameter("trigger");
    Generator env = ADSR().attack(0.001).decay(0.5).sustain(0).release(0).trigger(envelopeTrigger).legato(true);
    
    Generator output = tone * env;
    // set the synth's final output generator
    synth.setOutputGen( output );
    
}

//--------------------------------------------------------------
void testApp::update(){
 
    

}

//--------------------------------------------------------------
void testApp::draw(){
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    if (key=='1') synth.setParameter("trigger", 1);

    
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