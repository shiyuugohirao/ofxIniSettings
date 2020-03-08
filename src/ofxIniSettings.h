//
//  ofxIniSettings.h
//
//  Customized by shugohirao on 2018/10/13.
//  refer to
//  https://github.com/companje/ofxIniSettings
//

#pragma once
#include "ofMain.h"

class ofxIniSettings {
private:
    map<string,string> keys;

public:
    ofxIniSettings() { keys.clear(); }
    ofxIniSettings(string filename) { keys.clear(); load(filename); }
    virtual ~ofxIniSettings() {}

    bool load(string filename, bool clear=true){
        filename = ofToDataPath(filename);
        ofLogNotice("ofxIniSettings") << "load " << filename;
        if (!ofFile(filename).exists()) {
            ofLogError("ofxIniSettings")<<"file not found:" << filename;
            return false;
        }

        string cmd,section,key,value,id;
        ifstream f(filename.c_str(),ios::in);
        if(clear) keys.clear();
        while (getline(f,cmd)) {
            cmd = ofTrimBack(cmd); //remove \n \r \t space etc
            switch (cmd[0]) {
                case '#': break; //comment for ini
                case ';': break; //comment for ini
                case '[': {
                    int pos = cmd.find(";");
                    if(pos!=string::npos) cmd.erase(pos);
                    cmd = ofTrim(cmd);
                    section = cmd.substr(1,cmd.length()-2);
                    break;
                }
                default:{
                    {   //--- key ---//
                        int pos = cmd.find("=", 0);
                        if (pos==string::npos) break;
                        key = cmd.substr(0, pos);
                        key = ofTrim(key);
                        value = cmd.substr(pos+1);
                    }
                    {   //--- value ---//
                        int pos = value.find(";");
                        if(pos!=string::npos) value.erase(pos);
                        value = ofTrim(value);
                        id = section!="" ? (section + "." + key) : key;
                        keys[id] = value;
                    }
                    break;
                }
            }
        }
        f.close();
        return true;
    }

    bool has(string key) { return keys[key]!=""; }

    void print() {
        for (map<string,string>::iterator i=keys.begin(); i!=keys.end() ; i++) {
            ofLogNotice("ofxIniSettings") << i->first << "=" << i->second;
        }
    };

    //getters
    template<typename T>
    T get(string key, T defaultValue){ return has(key) ? ofTo<T>(keys[key]) : defaultValue; }

    //[*] ofTo<string> will cut by whitespace (ex: "a b c"-> "a")
    //    this cause errors using ofToVector(), you should use raw keys[key]
    string  get(string key, string  defaultValue) { return has(key) ? keys[key] : defaultValue; }
    int     get(string key, int     defaultValue) { return has(key) ? ofToInt(keys[key]) : defaultValue; }
    float   get(string key, float   defaultValue) { return has(key) ? ofToFloat(keys[key]) : defaultValue; }
    bool    get(string key, bool    defaultValue) { return has(key) ? ofToBool(keys[key]) : defaultValue; }
    ofColor get(string key, ofColor defaultValue) { return has(key) ? getColor(key) : defaultValue; }

    string  getString(string key)   { return get(key,string("")); }
    int     getInt(string key)      { return get(key,0); }
    float   getFloat(string key)    { return get(key,0.0f); }
    bool    getBool(string key)     { return get(key,false); }

    //--- HexColor(0x000000~0xFFFFFF)
    ofColor getColor(string key) { return ofColor::fromHex(ofHexToInt(getString(key))); }
    template<typename T> vector<T> getVector(string key) { return ofToVector<T>(getString(key)); }
    template<typename T1,typename T2> map<T1,T2> getMap(string key) { return ofToMap<T1,T2>(getString(key)); }

protected:
    template<typename T>
    vector<T> ofToVector(string s, string delimiter=",") {
        vector<T> v;
        vector<string> items = ofSplitString(s,delimiter,true,true);
        for(auto &i:items) v.push_back( ofTo<T>(i) );
        return v;
    }

    template<typename T1,typename T2>
    map<T1,T2> ofToMap(string s){
        vector<string> items = ofSplitString(s,"},",true,true);
        map<T1,T2> map;
        for(auto &i:items){
            int pos = i.find("{");
            if (pos==string::npos) break;
            i = i.substr(pos+1);
            //cout<<"i:"<< i <<endl;
            vector<string> kv = ofSplitString(i,",",true,true);
            map.insert(make_pair( ofTo<T1>(kv[0]), ofTo<T2>(kv[1]) ) );
        }
        return map;
    }
};
