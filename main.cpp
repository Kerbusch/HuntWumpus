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
        driver();
    }
}

