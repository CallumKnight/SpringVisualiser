#include "ofApp.h"
#include <cstdlib>

//--------------------------------------------------------------
void ofApp::setup(){

    // Initialise spring parameters
    springConstant = 1;
    springStart = {ofGetWidth()/2.0, ofGetHeight()/4.0};
    springLength = ofGetHeight()/4.0;
    springWidth = ofGetWidth()/8.0; 
    numCoils = 4;
    position = 1;
    velocity = 0;

    // Initialise fluid parameters
    dampingCoef = 0.05;

    for(uint8_t i = 0; i < static_cast<uint8_t>(dampingCoef * 100); i++)
    {
        // Generate random initial position
        Atom atom;
        atom.pos.x = rand() % (ofGetWidth()/2) + (ofGetWidth()/4);
        atom.pos.y = rand() % (ofGetHeight()/2) + (ofGetHeight()/4);
        atom.radius = 1.0;
        atoms.push_back(atom);
    }

    // Initialise mass parameters
    mass = 1;

    // Initialise applied force
    force = 0;

    // Calculate acceleration based on initial conditions
    acceleration = (-1*(springConstant/mass)*position) - ((dampingCoef/mass)*velocity) + ((1/mass)*force);

    // Start timer for measuring elapsed time
    time = std::chrono::steady_clock::now();
}

//--------------------------------------------------------------
void ofApp::update(){

    // Calculate elapsed time
    std::chrono::steady_clock::time_point updatedTime = std::chrono::steady_clock::now();
    double elapsedTimeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(updatedTime - time).count())/1000.0;
    
    // Update spring position
    velocity = velocity + (acceleration*elapsedTimeSec);
    position = position + (velocity*elapsedTimeSec);
    force = 0;
    acceleration = (-1*(springConstant/mass)*position) - ((dampingCoef/mass)*velocity) + ((1/mass)*force);

    // Update time
    time = std::chrono::steady_clock::now();

    // Adjust spring length
    springLength += position;

    // Update atom positions
    for(auto &atom : atoms)
    {
        atom.pos.x++;
        atom.pos.y++;
        
        if(atom.pos.x > 3.0*(ofGetWidth()/4.0))
        {
            atom.pos.x = ofGetWidth()/4.0;
            atom.pos.y = rand() % (ofGetHeight()/2) + (ofGetHeight()/4);
        }
        if(atom.pos.y > 3.0*(ofGetHeight()/4.0))
        {
            atom.pos.x = rand() % (ofGetWidth()/2) + (ofGetWidth()/4);
            atom.pos.y = ofGetHeight()/4.0;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    // Draw spring mounting point
    Coord lineStart = {ofGetWidth()/4.0, ofGetHeight()/4.0};
    Coord lineEnd = {3.0*(ofGetWidth()/4.0), ofGetHeight()/4.0};

    ofDrawLine(lineStart.x,
               lineStart.y,
               lineEnd.x,
               lineStart.y);

    // Draw atoms
    for(auto &atom : atoms)
    {
        ofDrawCircle(atom.pos.x, atom.pos.y, atom.radius);
    }
    
    // Draw spring
    ofPolyline spring;
    for(uint8_t i = 0; i < numCoils; i++)
    {
        double coilLength = springLength/numCoils;
        double coilVertOffset = i*coilLength;
        double coilHorOffset = 0.5*springWidth;

        // Add vertices to polyline for each coil
        // (Need to update spring dimensions in update function so that it's position 
        // within the window will be adjusted if window size is changed)
        spring.addVertex(ofVec3f(springStart.x, springStart.y + coilVertOffset, 0));
        spring.addVertex(ofVec3f(springStart.x - coilHorOffset, springStart.y + coilVertOffset + (coilLength/4), 0));
        spring.addVertex(ofVec3f(springStart.x, springStart.y + coilVertOffset + (2*coilLength/4), 0));
        spring.addVertex(ofVec3f(springStart.x + coilHorOffset, springStart.y + coilVertOffset + (3*coilLength/4), 0));
        spring.addVertex(ofVec3f(springStart.x, springStart.y + coilVertOffset + coilLength, 0));
    }
    spring.draw();

    // Draw mass
    ofDrawRectangle(springStart.x - (0.5*springWidth), springStart.y + springLength, 0, springWidth, ofGetWidth()/8);
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
