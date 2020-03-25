#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

string bestandtunnel = "tunnel.txt";
vector<vector<int>> kamers = {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}};
int wumpus,bat,pit;

bool check_conf_leeg(){
    ifstream conf_bestand(bestandtunnel);
    if(conf_bestand.peek() == std::ifstream::traits_type::eof()){
        return true;  
    }
    return false;
}

void lees_conf(){
    string line;
    ifstream conf_bestand;
    conf_bestand.open(bestandtunnel);
    for(int i = 0; i < 20;i++){
        vector<int> tmp;
        for(int j = 0; j < 3; j++){
            getline (conf_bestand, line);
            kamers[i].push_back(stoi(line));
        }
    }
    getline (conf_bestand, line);
    wumpus = stoi(line);
    getline (conf_bestand, line);
    bat = stoi(line);
    getline (conf_bestand, line);
    pit = stoi(line);
    conf_bestand.close();
    return;
}

int main(){
    if(check_conf_leeg()){
        cerr << "Error: leeg configuratie bestand. Voer eerst de configuratie uit.\n";
        exit(1);
    }
    lees_conf();
}