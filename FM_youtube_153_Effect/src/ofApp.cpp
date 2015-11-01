#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofBackground(255);
    
    gui.setup();
    gui.add(amountMod.setup("AmountMod", 1, 0.4, 20));
    gui.add(fqRatio.setup("fqRatio", 1, 0, 10));
    gui.add(pitchChangeRatioGui.setup("PitchChangeRatio", 1, 0.1, 2));
    gui.add(pitchScaleChangeGui.setup("pitchScaleChange", 1, 0, 6));
    
    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    
    float frequency = 440;
    
    // control
    ControlParameter carrierPitch = synth.addParameter("carrierPitch");
    ControlParameter pitchChangeRatio = synth.addParameter("pitchChangeRatio");
    ControlParameter pitchScaleChange = synth.addParameter("pitchScaleChange");
    ControlParameter amountMod = synth.addParameter("amountMod");
    ControlParameter fqRatio = synth.addParameter("fqRatio");
    
    // OSC
    Generator rCarrierFreq = ControlMidiToFreq().input((carrierPitch * pitchChangeRatio) + pitchScaleChange).smoothed();

    // FM
    Generator rModFreq = rCarrierFreq * fqRatio;
    Generator modulationTone = SineWave().freq( rModFreq ) * rModFreq * amountMod;
    Generator tone = SineWave().freq(rCarrierFreq + modulationTone);

    // Trigger
    ControlGenerator envelopTrigger = synth.addParameter("trigger");
    
    // Envelop
    Generator env = ADSR().attack(0.001).decay(0.1).sustain(0).release(0).trigger(envelopTrigger).legato(false);

    // Reverb
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
    
    // Delay
    ControlParameter delayTime = synth.addParameter("delayTime", 0.12f).displayName("Delay Time").min( 0.001f).max(1.0f).logarithmic(true); // logarithmic
    ControlParameter feedBack = synth.addParameter("feedback", 0.4f).displayName("Delay Feedback").min(0.0f).max(0.95f);
    ControlParameter delayMix = synth.addParameter("delayMix", 0.3f).displayName("Delay Dry/Wet").min(0.0f).max(1.0f);
    ControlParameter decay = synth.addParameter("decayTime", 0.08f).displayName("Env Decay Time").min(0.05f).max(0.25f).logarithmic(true); // logarithmic

    Generator smoothMix = delayMix.smoothed();
    
    BasicDelay delay = BasicDelay(0.5f, 1.0f)
    .delayTime( delayTime.smoothed(0.5f) )
    .feedback( feedBack.smoothed() )
    .dryLevel( 1.0f - smoothMix )
    .wetLevel( smoothMix );

    synth.setOutputGen( ((tone * env) >> delay >> reverb) * 0.75f );
    
    ofAddListener(ofEvents().keyPressed, this, &ofApp::keyPressedOne);
    
    ofEvent<float>* noteOut = synth.createOFEvent(carrierPitch);
    ofAddListener(* noteOut, this, &ofApp::receiveTrigger);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    synth.setParameter( "amountMod", amountMod );
    synth.setParameter( "fqRatio", fqRatio );
    synth.setParameter( "pitchChangeRatio", pitchChangeRatioGui );
    synth.setParameter( "pitchScaleChange", pitchScaleChangeGui );
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushStyle();
    ofSetColor(ofColor::fromHsb(0, 0, 120, 255));
    ofRect( ofGetWidth()/2-50, ofGetHeight(), 100, -noteView );
    ofPopStyle();
    
    gui.draw();
}


void ofApp::keyPressedOne(ofKeyEventArgs &key){
    
    switch (key.key) {
            
        case 49:
            synth.setParameter("trigger", 1);
            synth.setParameter("carrierPitch", 48);
            break;
            
        case 50:
            synth.setParameter("trigger", 1);
            synth.setParameter("carrierPitch", 50);
            break;
            
        case 51:
            synth.setParameter("trigger", 1);
            synth.setParameter("carrierPitch", 52);
            break;
            
        case 52:
            synth.setParameter("trigger", 1);
            synth.setParameter("carrierPitch", 53);
            break;
            
        case 53:
            synth.setParameter("trigger", 1);
            synth.setParameter("carrierPitch", 55);
            break;
            
        case 54:
            synth.setParameter("trigger", 1);
            synth.setParameter("carrierPitch", 57);
            break;
            
        case 55:
            synth.setParameter("trigger", 1);
            synth.setParameter("carrierPitch", 59);
            break;
            
        case 56:
            synth.setParameter("trigger", 1);
            synth.setParameter("carrierPitch", 60);
            break;
            
        default:
            break;
            
    }
    
    ofRemoveListener(ofEvents().keyPressed, this, &ofApp::keyPressedOne);
    
}


void ofApp::receiveTrigger(float &note){
    
    noteView = ofMap( note, 0, 127, 0, ofGetHeight() );
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    ofAddListener(ofEvents().keyPressed, this, &ofApp::keyPressedOne);
    
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