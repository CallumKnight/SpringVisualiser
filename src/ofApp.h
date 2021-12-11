// See following MATLAB Tech Talk for how to implement differential equation:
// https://www.google.com/search?q=how+to+implement+transfer+function+dynamics+on+a+computer&oq=how+to+implement+transfer+function+dynamics+on+a+computer&aqs=chrome..69i57.8375j0j4&sourceid=chrome&ie=UTF-8#kpvalbx=_93S0YYPYArPB8gLm2IagDw98

#pragma once

#include "ofMain.h"
#include <vector>

typedef struct coord{
	double x;
	double y;
} Coord;

typedef struct atom{
	Coord pos;
	double radius;
} Atom;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
	private:
		// Spring parameters
		Coord springStart;
		double springLength;
		double springWidth;
		uint8_t numCoils;
		int8_t lengthAdjust;
		
		// Fluid parameters
		double dampingCoef;
		std::vector<Atom> atoms;
		uint8_t atomAdjust;
};
