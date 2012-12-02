#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{
	public:
        ~testApp();
		void setup();
		void update();
		void draw();

		void mouseMoved(int x, int y);
		void audioOut(float * output, int bufferSize, int nChannels);

    private:
		ofSoundStream soundStream;
		float phase;
		float frequency;
		int sampleRate;
		int bufferSize;
		float *data;
};
