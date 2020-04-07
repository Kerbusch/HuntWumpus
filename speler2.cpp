#include "wumpus.hpp"
 
int main(){
    srand( (unsigned)time(NULL) ); //random
    if(check_tunnel_leeg()){ // kijkt of het tunnel bestand leeg is.
        cerr << "Error: leeg configuratie bestand. Voer eerst de configuratie uit.\n";
        exit(1);
    }
    lees_tunnel(); // leest het tunnel bestand
    while(true){
        int random = random20(); // geeft random de waarde van random20
        if(random != wumpus && random != vleermuis1 && random != vleermuis2 && random != valkuil1 && random != valkuil2){ // kijkt of er geen conflicten zijn
            locatie = random; // zet locatie op random
            break;
        }
    }
    cpu = true;
    print_all();
    while(true){
        cpu_driver();
    }
}