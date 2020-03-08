#include "ofApp.h"

#define LOGOUT(var,key) var=ini.get(key, var);cout<<key<<" : "<< var <<endl;

//--------------------------------------------------------------
void ofApp::setup(){
    ini.load("settings.ini");

    ini.print();

    ofColor col = ofColor::fromHex(0xa176ac);
    cout << col <<endl;
    col = ofColor::fromHex(ofHexToInt("0xa176ac"));
    cout << col <<endl;
    col = ofColor::fromHex(ofHexToInt(ini.getString("col01")));
    cout << col <<endl;


    cout<<"-----"<<endl;

    LOGOUT(i01,"i01")
    LOGOUT(i02,"i02")
    LOGOUT(i03,"i03")

    LOGOUT(f01,"f01")
    LOGOUT(f02,"f02")
    LOGOUT(f03,"f03")

    LOGOUT(str01,"str01")
    LOGOUT(str02,"str02")
    LOGOUT(str03,"str03")

    LOGOUT(col01,"col01")
    
    vector01 = ini.getVector<int>("vector01");
    vector02 = ini.getVector<string>("vector02");
    
    map01 = ini.getMap<string, int>("map01");
    cout<<map01["aaa"]<<endl;
    cout<<map01["bbb"]<<endl;
    cout<<map01["ccc"]<<endl;

    //--- Exit
    ofExit();
}
