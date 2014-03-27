#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground( 48, 85, 92 );
    ofSetFrameRate(60);
    
    bGuiDraw = true;
    gui.setup();
    gui.add(viewText.setup("key 'h'", "Toggle Menu"));
    gui.add(amountModGui.setup("amount Mod", 1, 0, 20));
    gui.add(amountFQGui.setup("amount FQ", 3.048, 0, 10));
    

    soundStream.setup(this, 2, 0, 44100, 256, 4);

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
    Generator env = ADSR().attack(0.001).decay(0.5).sustain(0).release(0).trigger(envelopTrigger).legato(false);
    
    // Output
    synth.setOutputGen( tone * env * 0.75 );
    
    ofAddListener(ofEvents().keyPressed, this, &ofApp::keyPressedOne);
    
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    synth.setParameter( "amountMod", amountModGui );
    synth.setParameter( "amountFQ", amountFQGui );
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    keyBoardDraw();
    
    if (bGuiDraw) gui.draw();
    
    
}

void ofApp::keyBoardDraw(){

    ofPushMatrix();
    ofPushStyle();
    
    int _keyWidth = 100;
    int _keyHeight = 400;
    
    ofTranslate( ofGetWidth()*0.5 - (KEY_NUM*100)*0.5, ofGetHeight()-_keyHeight-10 );
    
    for (int i=0; i<KEY_NUM; i++){
        
        ofRect(i * _keyWidth, 0, _keyWidth, _keyHeight);
        float _colorRange = ofMap( i, 0, KEY_NUM, 20, 200 );
        if (bKey[i]) {
            ofSetColor( 244, 104, 81 );
        }
        else {
            float _cColor = ofMap(i, 0, KEY_NUM, 0.2, 2.2 );
            ofSetColor( 84*_cColor, 136*_cColor, 117*_cColor );
        }
        ofRect(i * _keyWidth, 0, _keyWidth, _keyHeight);
        
    }
    ofPopStyle();
    ofPopMatrix();
    
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
    
    if (key=='h') bGuiDraw = !bGuiDraw;
    
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

void ofApp::audioRequested (float * output, int bufferSize, int nChannels){

    synth.fillBufferOfFloats(output, bufferSize, nChannels);

}