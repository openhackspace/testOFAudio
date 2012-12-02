#include "testApp.h"

testApp::~testApp() {
    free(data);
}

void testApp::setup(){
    // Setup the ofSoundStream object and the audio-related constants
    sampleRate=44100;
    bufferSize=1024;
    soundStream.listDevices();
    soundStream.setup(this,1,0,sampleRate,bufferSize,4);

    // Data initialization for the oscillator
    frequency=440.f;
    phase = 0.0f;

    // Allocating space for the data that will be drawn and setting some oF values for the graphics
    data = new float[bufferSize];
    ofEnableSmoothing();
    ofSetLineWidth(4);
    ofBackgroundHex(0x111111);
}

void testApp::update(){}

// This method will draw the audio data as a line (waveform)
void testApp::draw(){

    // Calculate ratio between the windows width and the audio buffer size
    float ratX = ofGetWidth()/bufferSize;

    // Set the color of the curve and disable fill
    ofSetHexColor(0xAA3322);
    ofNoFill();

    // Initialize the shape and start drawing the line point by point
    ofBeginShape();
    for(int i=0;i<bufferSize;i++)
        ofVertex(i*ratX,ofGetHeight()*(data[i]*0.5F+0.5F));
    ofEndShape(false);  // ofEndShape with a value of false tells oF not to connect the last point with the first
}


void testApp::audioOut(float *output, int bufferSize, int nChannels) {
    // Fill the buffer with audio data between -1 and 1
    for(int i=0;i<bufferSize;i++) {
        // Calculate phase of sine wave
        phase += frequency*TWO_PI/sampleRate;
        // Wrap to prevent artefacts
        while(phase>TWO_PI)
            phase-=TWO_PI;
        // Generate sine wave to audio output and data array simultaneously
        output[i] = data[i] = sinf(phase);
    }
}

void testApp::mouseMoved(int x, int y){
    frequency = x;
}
