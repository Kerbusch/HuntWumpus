#include <iostream>

#include <string>
using namespace std;

#include "header.hpp"

int main(){
    srand( (unsigned)time(NULL) );
    if(check_tunnel_leeg()){
        cerr << "Error: leeg configuratie bestand. Voer eerst de configuratie uit.\n";
        exit(1);
    }
    lees_tunnel();
    while(true){
        int random = random20();
        if(random != wumpus && random != bat1 && random != bat2 && random != valkuil1 && random != valkuil2){
            locatie = random;
            break;
        }
    }
    lees_instructie();
    while(true){
        driver();
    }
}
