// See following MATLAB Tech Talk for how to implement differential equation:
// https://www.google.com/search?q=how+to+implement+transfer+function+dynamics+on+a+computer&oq=how+to+implement+transfer+function+dynamics+on+a+computer&aqs=chrome..69i57.8375j0j4&sourceid=chrome&ie=UTF-8#kpvalbx=_93S0YYPYArPB8gLm2IagDw98

#pragma once

#include "ofMain.h"
#include <vector>
#include <chrono>

typedef struct coord{
	double x;
	double y;
} Coord;

typedef struct particle{
	Coord pos;
	double radius;
} Particle;

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
		double springConstant;
		double position;
		double velocity;
		double acceleration;
		double springLength;
		
		// Fluid parameters
		double dampingCoef;
		std::vector<Particle> particles;

		// Mass parameters
		double mass;

		// Applied force
		double force;

		// Time
		std::chrono::steady_clock::time_point time;

		// User Input
		bool mousePressed();

};
