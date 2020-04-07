#include "wumpus.hpp"

using std::cout;

//cpu varables:
vector<int> valkuil_v = {}, vleermuis_v = {}, safe = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}, cpu_vleermuis = {}, cpu_valkuil = {};
int cpu_wumpus = -1;

// kijken welke optie van de buuren het best is om naar te verplaatsem
// kijken waaneer de cpu moet schieten.
// vector gebruiken voor onthouden waar de wumpus, vleermuizen en valkuilen kunnen zijn
// if doel == wumpus,vleermuis,put then niet verplaatsen!
// route onthouden <--

void print_all(){
    cout << "valkuil_v: \n";
    for(int i = 0; i < valkuil_v.size(); i++){
        cout << valkuil_v[i] << "\n";
    }
    cout << "vleermuis_v: \n";
    for(int i = 0; i < vleermuis_v.size(); i++){
        cout << vleermuis_v[i] << "\n";
    }
    cout << "safe: \n";
    for(int i = 0; i < safe.size(); i++){
        cout << safe[i] << "\n";
    }
    cout << "cpu_vleermuis: \n";
    for(int i = 0; i < cpu_vleermuis.size(); i++){
        cout << cpu_vleermuis[i] << "\n";
    }
    cout << "cpu_valkuil: \n";
    for(int i = 0; i < cpu_valkuil.size(); i++){
        cout << cpu_valkuil[i] << "\n";
    }
    cout << "cpu_wumpus: " << cpu_wumpus << "\n";
    return;
}

int random_buur_vector(const vector<int>& opties){
    int x = rand() % opties.size();
    return opties[x];
}

void remove_from_safe(const int& x){
    safe.erase(safe.begin()+x-1);
    return;
}

void end_game(const string& x){
    if(x == "wumpus"){
        remove_from_safe(locatie);
        cpu_wumpus = locatie;
    }else if(x == "valkuil"){
        remove_from_safe(locatie);  
        cpu_valkuil.push_back(locatie);
    }
    print_all();
    exit(0);
    return;
}

bool check_spel_end(){
    if(locatie == wumpus){
        cout << "Helaas je bent opgegeten door de Wumpus, GAME OVER!\n";
        end_game("wumpus");
        return true;
    }else if(pijlen <= 0){
        cout << "Je pijlen zijn op! GAME OVER!\n";
        end_game("pijlen");
        return true;
    }else if(valkuil_check()){
        cout << "Je ben in een put gevallen! GAME OVER!\n";
        end_game("valkuil");
        return true;
    }else if(vleermuis_check()){
        remove_from_safe(locatie);
        cpu_vleermuis.push_back(locatie);
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
    vector<int> opties;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < safe.size(); j++){
            if(kamers[locatie-1][i] == safe[j]){
                opties.push_back(kamers[locatie-1][i]);
            }
        }
    }
    int tmp = random_buur_vector(opties);
    verplaats(to_string(tmp));
}