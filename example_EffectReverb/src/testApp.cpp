#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    
    ControlParameter dry = synth.addParameter("dry",-6.f).displayName("Dry Level (dbFS)").min(-60.f).max(0.f);
    ControlParameter wet = synth.addParameter("wet",-20.f).displayName("Wet Level (dbFS)").min( -60.f).max(0.f);
    ControlParameter time = synth.addParameter("decayTime", 1.0f).displayName("Decay Time (s)").min(0.1f).max(10.f);
    ControlParameter lowDecay = synth.addParameter("lowDecay", 16000.0f).displayName("Decay Lowpass Cutoff (Hz)").min(4000.0f).max(20000.0f);
    ControlParameter hiDecay = synth.addParameter("hiDecay",20.0f).displayName("Decay Highpass Cutoff (Hz)").min(20.f).max(250.f);
    ControlParameter preDelay = synth.addParameter("preDelay", 0.001f).displayName("Pre-delay").min(0.001f).max(0.05f);
    ControlParameter inputLPF = synth.addParameter("inputLPF",18000.f).displayName("Input LPF cutoff (Hz)").min(4000.0f).max(20000.0f);
    ControlParameter inputHPF = synth.addParameter("inputHPF",20.f).displayName("Input HPF cutoff (Hz)").min(20.f).max(250.f);
    ControlParameter density = synth.addParameter("density",0.5f).displayName("Density");
    ControlParameter shape = synth.addParameter("shape",0.5f).displayName("Shape");
    ControlParameter size = synth.addParameter("size",0.5f).displayName("Room Size");
    ControlParameter stereo = synth.addParameter("stereo",0.5f).displayName("Stereo Width");
    
    float bpm = 30.f;
    
    ControlMetro beat = ControlMetro().bpm(bpm);
    ControlDelay offbeat = ControlDelay(1.2f).input(beat).delayTime(30.0f/bpm);
    
    Generator click = Noise() * ADSR(0.0001f,0.025f,0,0.01f).doesSustain(false).exponential(true).trigger(beat);
    
    Generator tone = RectWave().pwm(0.5f).freq(Tonic::mtof(60)) * ADSR(0.001f, 0.08f, 0, 0.01f).doesSustain(false).exponential(true).trigger(offbeat);
    
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
    
    synth.setOutputGen( ((click + tone) >> reverb) * 0.8f );}

//--------------------------------------------------------------
void testApp::update(){
 
    synth.setParameter("wet", ofGetMouseY());

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