#include "wumpus.hpp"

using std::cout;

//cpu varables:
vector<int> wumpus_v = {}, valkuil_v = {}, vleermuis_v = {}, safe = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}, cpu_vleermuis = {}, cpu_valkuil = {};
int cpu_wumpus = -1;

// kijken welke optie van de buuren het best is om naar te verplaatsem
// kijken waaneer de cpu moet schieten.
// vector gebruiken voor onthouden waar de wumpus, vleermuizen en valkuilen kunnen zijn
// if doel == wumpus,vleermuis,put then niet verplaatsen!!



void end(string x){
    if(x == "wumpus"){
        remove_from_safe(locatie);
        cpu_wumpus = locatie;
    }else if(x == "valkuil"){
        remove_from_safe(locatie);  
        cpu_valkuil.push_back(locatie);
    }
    exit(0);
    return;
}

bool check_spel_end(){
    if(locatie == wumpus){
        cout << "Helaas je bent opgegeten door de Wumpus, GAME OVER!\n";
        end("wumpus");
        return true;
    }else if(pijlen <= 0){
        cout << "Je pijlen zijn op! GAME OVER!\n";
        end("pijlen");
        return true;
    }else if(valkuil_check()){
        cout << "Je ben in een put gevallen! GAME OVER!\n";
        end("valkuil");
        return true;
    }else if(vleermuis_check()){
        remove_from_safe(locatie);
        while(true){
            int random = random20();
            if(random != vleermuis1 && random != vleermuis2){
                locatie = random;
                cout << "In deze kamer zit een Supervleermuis, hij verplaatst je naar kamer " << random << "!\n\n";
                break;
            }
        }
        return true;
    }
    return false;
}

void remove_from_safe(const int& x){
    safe.erase(safe.begin()+x-1);
    return;
}

void cpu_driver(){
    cout << "----------------------------------------\n";

    // kijkt of het spel beeindigt word
    if(check_spel_end()){
        return;
    }

    //kijkt of je Wumpus kan ruiken
    if(ruik()){ 
        cout << "\n" << "Je ruikt de Wumpus.\n";
        // deduction
    }

    //kijkt of je vleermuis hoort
    if(hoor_vleermuis()){ 
        cout << "\nJe hoort geflapper van een Supervleermuis.\n";
        // deduction
    }

    //kijkt of je wind voelt
    if(voelWind()){ 
        cout << "\nJe voelt een lichte bries.\n";
        // deduction
    }

    //---cout---
    //cout de mogelijke kamers:
    cout << "Locatie: " << locatie << ". Tunnels: ";
    for(int i = 0; i < 3; i ++){
            cout << kamers[locatie-1][i] << ", ";
    }

    //alleen schieten als de wumpus een buur is.
    for(int i = 0; i < 3; i ++){
        if(kamers[locatie-1][i] == cpu_wumpus){
            schiet(to_string(cpu_wumpus));
            return;
        }
    }

    // als hij niet weet waar de wumpus is of niet ziet dan:
    

}