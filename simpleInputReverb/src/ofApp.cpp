#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){

    soundStream.listDevices();
    soundStream.setDeviceID(0);
    soundStream.setup(this, 0, 2, 44100, 256, 4);
    
    outSoundStream.setDeviceID(0);
    outSoundStream.setup(this, 2, 0, 44100, 256, 4);
    
    
    RingBuffer _inputS;
    inputBuffer = RingBufferWriter("_inputS", 256, 4);
    RingBufferReader inputReader = RingBufferReader().bufferName("_inputS");
    
    
    
    ControlParameter tempo = synth.addParameter("tempo", 60.f).displayName("Tempo").min(60.f).max(300.f);
    ControlParameter delayTime = synth.addParameter("delayTime", 1.0f).displayName("Delay Time").min( 0.001f).max(1.0f).logarithmic(true); // logarithmic
    ControlParameter feedBack = synth.addParameter("feedback", 0.4f).displayName("Delay Feedback").min(0.0f).max(0.95f);
    ControlParameter delayMix = synth.addParameter("delayMix", 0.3f).displayName("Delay Dry/Wet").min(0.0f).max(1.0f);
    ControlParameter decay = synth.addParameter("decayTime", 0.08f).displayName("Env Decay Time").min(0.05f).max(0.25f).logarithmic(true); // logarithmic
    ControlParameter volume = synth.addParameter("volume", -6.f).displayName("Volume (dbFS)").min(-60.0f).max(0.f);
    
    ControlMetro metro = ControlMetro().bpm(tempo * 4);
    
    ADSR aEnv = ADSR().attack(0.005f).decay(decay).sustain(0.0f).release(0.01f).trigger(metro).doesSustain(false).exponential(true);
    ADSR fEnv = ADSR().attack(0.005f).decay(decay).sustain(0.0f).release(0.01f).trigger(metro).doesSustain(false).exponential(true);
    
    float scalenums[5] = {0,3,5,7,10};
    std::vector<float> scale(scalenums, scalenums + 5);
    
    ControlRandom rand = ControlRandom().min(0).max(36).trigger(metro);
    ControlSnapToScale snap = ControlSnapToScale().setScale(scale).input(rand);
    ControlMidiToFreq freq = ControlMidiToFreq().input(48 + snap);
    
    Generator osc = (
                     (
                      (
                       RectWave().freq( freq * 0.99 ).pwm(0.5f) * aEnv * 0.5
                       )
                      >> MonoToStereoPanner().pan(-0.5)
                      )
                     +
                     (
                      (
                       RectWave().freq(freq * 1.01).pwm(0.5f) * aEnv * 0.5
                       )
                      >> MonoToStereoPanner().pan(0.5)
                      )
                     );
    
    LPF12 filt = LPF12().cutoff(400.0f * (1.0f + fEnv*9.0f)).Q(1.1f);
    
    Generator smoothMix = delayMix.smoothed();
    
    BasicDelay delay = BasicDelay(0.5f, 1.0f)
    .delayTime( delayTime.smoothed(0.5f) )
    .feedback( feedBack.smoothed() )
    .dryLevel( 1.0f - smoothMix )
    .wetLevel( smoothMix );
    
    //    setOutputGen((osc >> filt >> delay) * ControlDbToLinear().input(volume).smoothed());
    synth.setOutputGen((inputReader >> filt >> delay) * ControlDbToLinear().input(volume).smoothed());
}

//--------------------------------------------------------------
void ofApp::update(){

    
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetHexColor(0xFF0000);
    ofDrawBitmapString("This is a very simple audio recording and playback demo.",20,280);
    ofDrawBitmapString("Press 'p' - playback or 'r' for recording into a 10 seconds buffer.",20,300);
    
    // get info about whats going on..
    if (RMode) { ofDrawBitmapString("Rec-Mode",20,380);};
    if (PMode) { ofDrawBitmapString("Play-Mode",20,380);};

    
}

void ofApp::audioRequested(float* output, int bufferSize, int nChannels){
    
    
    
    //if you're playin back:
    if(PMode == true)
    {
        for (int i = 0; i < bufferSize*nChannels; i++)
        {
            if(playPos<LENGTH) output[i] = buffer[playPos++];
  

//            output[i] = _bufferTemp[i];

        }
        
        inputBuffer.write(buffer, bufferSize, nChannels);

        
    }
    
    
    synth.fillBufferOfFloats(output, bufferSize, nChannels);

    
    
}


void ofApp::audioReceived(float* input, int bufferSize, int nChannels){
    
    
    
    //if you're rec-oh-din
    if(RMode == true)
    {
        // this would be faster with a memcpy()
        for (int i = 0; i < bufferSize*nChannels; i++)
        {
            if(recPos<LENGTH) buffer[recPos++] = input[i];
        }
        
        tableBuffer = *buffer;
        
//        tableBuffer.dataPointer();
        
//        inputBuffer.write(_testBuffer, bufferSize, nChannels);
        
    } else {
    }


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == 'r' )  {
        // rec
        RMode = true;
        PMode = false;
        recPos = 0;
    } else if (key == 'p'){
        // play
        RMode = false;
        PMode = true;
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
