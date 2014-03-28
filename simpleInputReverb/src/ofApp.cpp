#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){

    ofSoundStreamSetup(2, 2, this, 44100, 256, 4);

    RingBuffer _inputS;
    inputBuffer = RingBufferWriter("_inputS", 256, 4);
    RingBufferReader inputReader = RingBufferReader().bufferName("_inputS");
    
    // Reverb
    ControlParameter dry = synth.addParameter("dry",-6.f).displayName("Dry Level (dbFS)").min(-60.f).max(0.f);
    ControlParameter wet = synth.addParameter("wet",-6.f).displayName("Wet Level (dbFS)").min( -60.f).max(0.f);
    ControlParameter time = synth.addParameter("decayTime", 4.0f).displayName("Decay Time (s)").min(0.1f).max(10.f);
    ControlParameter lowDecay = synth.addParameter("lowDecay", 16000.0f).displayName("Decay Lowpass Cutoff (Hz)").min(4000.0f).max(20000.0f);
    ControlParameter hiDecay = synth.addParameter("hiDecay",20.0f).displayName("Decay Highpass Cutoff (Hz)").min(20.f).max(250.f);
    ControlParameter preDelay = synth.addParameter("preDelay", 0.001f).displayName("Pre-delay").min(0.001f).max(0.05f);
    ControlParameter inputLPF = synth.addParameter("inputLPF",18000.f).displayName("Input LPF cutoff (Hz)").min(4000.0f).max(20000.0f);
    ControlParameter inputHPF = synth.addParameter("inputHPF",20.f).displayName("Input HPF cutoff (Hz)").min(20.f).max(250.f);
    ControlParameter density = synth.addParameter("density",0.5f).displayName("Density");
    ControlParameter shape = synth.addParameter("shape",0.5f).displayName("Shape");
    ControlParameter size = synth.addParameter("size",0.5f).displayName("Room Size");
    ControlParameter stereo = synth.addParameter("stereo",0.5f).displayName("Stereo Width");
    
    Reverb reverb = Reverb()
    .preDelayTime(preDelay)
    .inputLPFCutoff(inputLPF)
    .inputHPFCutoff(inputHPF)
    .decayTime(time)
    .decayLPFCutoff(lowDecay)
    .decayHPFCutoff(hiDecay)
    .stereoWidth(stereo)
    .density(density)
    .roomShape(shape)
    .roomSize(size)
    .dryLevel(ControlDbToLinear().input(dry))
    .wetLevel(ControlDbToLinear().input(wet));
    
    Generator output = inputReader >> reverb;
    
    synth.setOutputGen(output);
        
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
