#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    springLength = ofGetHeight()/2.0;
    lengthAdjust = 1;
}

//--------------------------------------------------------------
void ofApp::update(){

    // Adjust direction of spring movement if limits reached
    if(springLength > (3.0*ofGetHeight()/5.0))
    {
        lengthAdjust = -1;
    }
    else if(springLength < (2.0*ofGetHeight()/5.0))
    {
        lengthAdjust = 1;
    }

    // Adjust spring length
    springLength += lengthAdjust;
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

    // Initialise spring dimensions
    uint8_t numCoils = 4;
    // double springLength = ofGetHeight()/2.0;
    double springWidth = ofGetWidth()/8.0; // Can have it depend on spring length later
    Coord springStart = {ofGetWidth()/2.0, ofGetHeight()/4.0};
    Coord springEnd = {ofGetWidth()/2.0, springStart.y + springLength};
    
    // Create Polyline to represent spring
    ofPolyline spring;

    for(uint8_t i = 0; i < numCoils; i++)
    {
        double coilLength = springLength/numCoils;
        double coilVertOffset = i*coilLength;
        double coilHorOffset = 0.5*springWidth;

        // Add vertices to polyline for each coil
        spring.addVertex(ofVec3f(springStart.x, springStart.y + coilVertOffset, 0));
        spring.addVertex(ofVec3f(springStart.x - coilHorOffset, springStart.y + coilVertOffset + (coilLength/4), 0));
        spring.addVertex(ofVec3f(springStart.x, springStart.y + coilVertOffset + (2*coilLength/4), 0));
        spring.addVertex(ofVec3f(springStart.x + coilHorOffset, springStart.y + coilVertOffset + (3*coilLength/4), 0));
        spring.addVertex(ofVec3f(springStart.x, springStart.y + coilVertOffset + coilLength, 0));
    
        if(i == numCoils - 1)
        {
            // Add vertices for end point of spring
            spring.addVertex(springStart.x - coilHorOffset, springEnd.y, 0);
            spring.addVertex(springStart.x + coilHorOffset, springEnd.y, 0);
        }
    }

    // Draw spring
    spring.draw();
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
