#pragma once

#include "ofMain.h"
#include "ofxIniSettings.h"

class ofApp : public ofBaseApp{
private:
    ofxIniSettings ini;

    int i01,i02,i03;
    float f01,f02,f03;
    string str01,str02,str03;
    ofColor col01;

    vector<int> vector01;
    vector<string> vector02;
    map<string,int> map01;
    
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
};
