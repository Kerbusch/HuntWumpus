#include <iostream>

#include <string>
using namespace std;

#include "header.hpp"

int main(){
    if(check_tunnel_leeg()){
        cerr << "Error: leeg configuratie bestand. Voer eerst de configuratie uit.\n";
        exit(1);
    }
    lees_tunnel();
    while(true){
        driver();
    }
}

// bugs:
// als je schiet naar 5 vanaf 1 ruik je de wumpus. Als je naar andere kamers gaat blijft hij dit zeggen.

