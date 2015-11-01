#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSoundStreamSetup(1, 0, this, 44100, 256, 4);
    
//    ControlParameter _fq = synth.addParameter("Fq");
//    Generator sinTone = SineWave().freq(_fq);
//    synth.setOutputGen(sinTone);

    bGuiDraw = true;
    gui.setup();
    gui.add(viewText.setup("key 'h'", "Toggle Menu"));
    gui.add(amountModGui.setup("amount Mod", 1, 0, 20));
    gui.add(amountFQGui.setup("amount FQ", 3.048, 0, 10));

    // Parameter
    ControlParameter triggerPitch = synth.addParameter("triggerPitch");
    ControlParameter amountMod = synth.addParameter("amountMod");
    ControlParameter amountFQ = synth.addParameter("amountFQ");
    ControlParameter envelopTrigger = synth.addParameter("trigger");
    
    // Main Fq
    Generator mainFq = ControlMidiToFreq().input(triggerPitch).smoothed();
    
    // Modulation Fq
    Generator rModFq     = mainFq * amountFQ;
    Generator modulation = SineWave().freq( rModFq ) * rModFq * amountMod;
    
    // Tone Generator
    Generator tone = SineWave().freq(mainFq + modulation);
    
    // Envelop Generator
    Generator env = ADSR().attack(10).decay(0.001).sustain(0).release(0).trigger(envelopTrigger).legato(false);
    
    // Output
    synth.setOutputGen( tone * env * 0.75 );

    
    
    plotHeight = 128;
	bufferSize = 256;
	
	fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING);
	// To use FFTW, try:
//	fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING, OF_FFT_FFTW);
	
	drawBins.resize(fft->getBinSize());
	middleBins.resize(fft->getBinSize());
	audioBins.resize(fft->getBinSize());

    
    ofAddListener(ofEvents().keyPressed, this, &ofApp::keyPressedOne);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    synth.setParameter( "amountMod", amountModGui );
    synth.setParameter( "amountFQ", amountFQGui );

}

//--------------------------------------------------------------
void ofApp::draw(){

    gui.draw();
    
	ofSetColor(255);
	ofPushMatrix();
	ofTranslate(16, ofGetHeight()-plotHeight-16);
	
	soundMutex.lock();
	drawBins = middleBins;
	soundMutex.unlock();
	
	ofDrawBitmapString("Frequency Domain", 0, 0);
	plot(drawBins, -plotHeight, plotHeight / 2);
	ofPopMatrix();
	string msg = ofToString((int) ofGetFrameRate()) + " fps";
	ofDrawBitmapString(msg, ofGetWidth() - 80, ofGetHeight() - 20);

}

void ofApp::plot(vector<float>& buffer, float scale, float offset) {

    int _size = 4;
    
	ofNoFill();
	int n = buffer.size();
	ofRect(0, 0, n * _size, plotHeight);
	glPushMatrix();
	glTranslatef(0, plotHeight / 2 + offset, 0);
	ofBeginShape();
	for (int i = 0; i < n; i++) {
		ofVertex(i * _size, sqrt(buffer[i]) * scale);
	}
	ofEndShape();
	glPopMatrix();
}

void ofApp::audioRequested(float* output, int bufferSize, int nChannels){
    
    synth.fillBufferOfFloats(output, bufferSize, nChannels);
    
    float maxValue = 0;
	for(int i = 0; i < bufferSize; i++) {
		if(abs(output[i]) > maxValue) {
			maxValue = abs(output[i]);
		}
	}
	for(int i = 0; i < bufferSize; i++) {
		output[i] /= maxValue;
	}
	
	fft->setSignal(output);
	
	float* curFft = fft->getAmplitude();
	memcpy(&audioBins[0], curFft, sizeof(float) * fft->getBinSize());
	
	maxValue = 0;
	for(int i = 0; i < fft->getBinSize(); i++) {
		if(abs(audioBins[i]) > maxValue) {
			maxValue = abs(audioBins[i]);
		}
	}
	for(int i = 0; i < fft->getBinSize(); i++) {
		audioBins[i] /= maxValue;
	}
	
	soundMutex.lock();
	middleBins = audioBins;
	soundMutex.unlock();
}


void ofApp::keyPressedOne(ofKeyEventArgs &key){
    
    switch (key.key) {
            
        case 49:
            synth.setParameter("trigger", 1);
            synth.setParameter("triggerPitch", 48);
            bKey[0] = true;
            break;
            
        case 50:
            synth.setParameter("trigger", 1);
            synth.setParameter("triggerPitch", 50);
            bKey[1] = true;
            break;
            
        case 51:
            synth.setParameter("trigger", 1);
            synth.setParameter("triggerPitch", 52);
            bKey[2] = true;
            break;
            
        case 52:
            synth.setParameter("trigger", 1);
            synth.setParameter("triggerPitch", 53);
            bKey[3] = true;
            break;
            
        case 53:
            synth.setParameter("trigger", 1);
            synth.setParameter("triggerPitch", 55);
            bKey[4] = true;
            break;
            
        case 54:
            synth.setParameter("trigger", 1);
            synth.setParameter("triggerPitch", 57);
            bKey[5] = true;
            break;
            
        case 55:
            synth.setParameter("trigger", 1);
            synth.setParameter("triggerPitch", 59);
            bKey[6] = true;
            break;
            
        case 56:
            synth.setParameter("trigger", 1);
            synth.setParameter("triggerPitch", 60);
            bKey[7] = true;
            break;
            
        default:
            break;
            
    }
    
    
    ofRemoveListener(ofEvents().keyPressed, this, &ofApp::keyPressedOne);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    ofAddListener(ofEvents().keyPressed, this, &ofApp::keyPressedOne);
    for (int i=0; i<KEY_NUM; i++) {
        bKey[i] = false;
    }

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
