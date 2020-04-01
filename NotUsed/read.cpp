#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

string bestandtunnel = "tunnel.txt";
vector<vector<int>> kamers = {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}};
int wumpus,bat1,bat2,valkuil1,valkuil2;

bool check_conf_leeg(){
    ifstream conf_tunnel_bestand(bestandtunnel);
    if(conf_tunnel_bestand.peek() == std::ifstream::traits_type::eof()){
        return true;  
    }
    return false;
}

void lees_conf(){
    string line;
    ifstream conf_tunnel_bestand;
    conf_tunnel_bestand.open(bestandtunnel);
    for(int i = 0; i < 20;i++){ // tunnnels tussen de kamers
        vector<int> tmp;
        for(int j = 0; j < 3; j++){
            getline (conf_tunnel_bestand, line);
            kamers[i].push_back(stoi(line));
        }
    }
    getline (conf_tunnel_bestand, line); // wumpus
    wumpus = stoi(line);
    getline (conf_tunnel_bestand, line); // bat1
    bat1 = stoi(line);
    getline (conf_tunnel_bestand, line); // bat2
    bat2 = stoi(line);
    getline (conf_tunnel_bestand, line); // valkuil1
    valkuil1 = stoi(line);
    getline (conf_tunnel_bestand, line); // valkuil1
    valkuil2 = stoi(line);
    conf_tunnel_bestand.close();
    return;
}

int main(){
    if(check_conf_leeg()){
        cerr << "Error: leeg configuratie bestand. Voer eerst de configuratie uit.\n";
        exit(1);
    }
    lees_conf();
}