#include "ofApp.h"
#include <cstdlib>

//--------------------------------------------------------------
void ofApp::setup(){
    
    // Initialise spring parameters
    springConstant = 10;
    position = 0;
    velocity = 0;
    springLength = ofGetHeight()/4.0 + position;

    // Initialise fluid parameters
    dampingCoef = 0.5;
    for(uint8_t i = 0; i < static_cast<uint8_t>(dampingCoef * 100); i++)
    {
        // Generate random initial position for fluid particles
        Particle particle;
        particle.pos.x = rand() % (ofGetWidth()/2) + (ofGetWidth()/4);
        particle.pos.y = rand() % (ofGetHeight()/2) + (ofGetHeight()/4);
        particle.radius = 1.0;
        particles.push_back(particle);
    }

    // Initialise mass parameters
    mass = 1;

    // Initialise applied force
    force = 0;

    // Calculate initial acceleration
    acceleration = (-1*(springConstant/mass)*position) - ((dampingCoef/mass)*velocity) + ((1/mass)*force);

    // Initialise plot coordinate
    Particle plotCoordinate = {ofGetWidth()/2.0, (ofGetHeight()/8.0) + (position/4.0), 0.5};
    plotCoordinates.push_back(plotCoordinate);

    // Start timer for measuring elapsed time
    time = std::chrono::steady_clock::now();
}

//--------------------------------------------------------------
void ofApp::update(){

    if(ofGetMousePressed())
    {
        time = std::chrono::steady_clock::now();

        if(ofGetMouseY() < (ofGetHeight()/4))
        {
            springLength = 0;
            position = springLength - (ofGetHeight()/4);
        }
        else if(ofGetMouseY() > (3*(ofGetHeight()/4)))
        {
            springLength = ofGetHeight()/2;
            position = springLength - (ofGetHeight()/4);
        }
        else
        {
            springLength = ofGetMouseY() - (ofGetHeight()/4);
            position = springLength - (ofGetHeight()/4);
        }
        velocity = 0;
        force = 0;
        acceleration = (-1*(springConstant/mass)*position) - ((dampingCoef/mass)*velocity) + ((1/mass)*force);
    }
    else
    {
        // Calculate elapsed time
        std::chrono::steady_clock::time_point updatedTime = std::chrono::steady_clock::now();
        double elapsedTimeSec = (std::chrono::duration_cast<std::chrono::milliseconds>(updatedTime - time).count())/1000.0;
        
        // Update spring position
        velocity = velocity + (acceleration*elapsedTimeSec);
        position = position + (velocity*elapsedTimeSec);
        force = 0;
        acceleration = (-1*(springConstant/mass)*position) - ((dampingCoef/mass)*velocity) + ((1/mass)*force);
        springLength = (ofGetHeight()/4.0) + position;

        // Update time
        time = std::chrono::steady_clock::now();

        // Update particle positions
        for(auto &particle : particles)
        {
            particle.pos.x++;
            particle.pos.y++;
            
            if(particle.pos.x > 3.0*(ofGetWidth()/4.0))
            {
                particle.pos.x = ofGetWidth()/4.0;
                particle.pos.y = rand() % (ofGetHeight()/2) + (ofGetHeight()/4);
            }
            if(particle.pos.y > 3.0*(ofGetHeight()/4.0))
            {
                particle.pos.x = rand() % (ofGetWidth()/2) + (ofGetWidth()/4);
                particle.pos.y = ofGetHeight()/4.0;
            }
        }

        // Update plot coordinates
        for(auto& coordinate : plotCoordinates)
        {
            coordinate.pos.x--;
            if(coordinate.pos.x < ofGetWidth()/4.0)
            {
                plotCoordinates.erase(plotCoordinates.begin());
            }
        }
        // Add new coordinate to plot
        Particle plotCoordinate = {ofGetWidth()/2.0, (ofGetHeight()/8.0) + (position/4.0), 0.5};
        plotCoordinates.push_back(plotCoordinate);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // Draw spring mounting point
    ofDrawLine(ofGetWidth()/4.0,
               ofGetHeight()/4.0,
               3.0*(ofGetWidth()/4.0),
               ofGetHeight()/4.0);

    // Draw fluid
    for(auto &particle : particles)
    {
        ofDrawCircle(particle.pos.x, particle.pos.y, particle.radius);
    }
    
    // Draw spring
    Coord springStart = {ofGetWidth()/2.0, ofGetHeight()/4.0};
    double springWidth = ofGetWidth()/8.0;
    uint8_t numCoils = 4;

    ofPolyline spring;
    for(uint8_t i = 0; i < numCoils; i++)
    {
        double coilLength = springLength/numCoils;
        double coilVertOffset = i*coilLength;
        double coilHorOffset = 0.5*springWidth;

        // Add vertices to polyline for each coil
        spring.addVertex(ofVec3f(springStart.x, springStart.y + coilVertOffset, 0));
        spring.addVertex(ofVec3f(springStart.x - coilHorOffset, springStart.y + coilVertOffset + (coilLength/4), 0));
        spring.addVertex(ofVec3f(springStart.x, springStart.y + coilVertOffset + (coilLength/2), 0));
        spring.addVertex(ofVec3f(springStart.x + coilHorOffset, springStart.y + coilVertOffset + (3*coilLength/4), 0));
        spring.addVertex(ofVec3f(springStart.x, springStart.y + coilVertOffset + coilLength, 0));
    }
    spring.draw();
    
    // Draw mass
    ofNoFill();
    ofDrawRectangle(springStart.x - (0.5*springWidth), springStart.y + springLength, 0, springWidth, ofGetWidth()/16);

    // Draw plot
    ofFill();
    for(auto& coordinate : plotCoordinates)
    {
        ofDrawCircle(coordinate.pos.x, coordinate.pos.y, coordinate.radius);
    }
    double lineLength = 0.0;
    double dashLength = 5.0;
    double dashSpacing = 10.0;
    do
    {
        ofDrawLine((ofGetWidth()/4.0) + lineLength,
                   ofGetHeight()/8.0,
                   (ofGetWidth()/4.0) + lineLength + dashLength,
                   ofGetHeight()/8.0);
        lineLength += dashLength + dashSpacing;
    }while(lineLength < (ofGetWidth()/2));
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
