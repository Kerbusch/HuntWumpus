#include <algorithm>

#include "wumpus.hpp"

using std::cout;

//cpu varables:
vector<int> safe = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}, cpu_vleermuis = {}, cpu_valkuil = {}, route = {}, route_last = {} ;
int cpu_wumpus = 99, route_index = 0;
bool route_find = false;
string bestandvariable = "tekst/variabel.txt";

// kijken welke optie van de buuren het best is om naar te verplaatsem
// kijken waaneer de cpu moet schieten.
// vector gebruiken voor onthouden waar de wumpus, vleermuizen en valkuilen kunnen zijn
// if doel == wumpus,vleermuis,put then niet verplaatsen!
// route onthouden <--

void schrijf_variabel_bestand(){
    ofstream bestand;
    //leeg bestand:
    bestand.open(bestandvariable);
    bestand << "";
    bestand.close();
    //schrijf in bestand
    bestand.open(bestandvariable, ofstream::app);
    bestand << safe.size() << "\n";
    for(int i = 0; i < safe.size(); i++){
        bestand << safe[i] << "\n";
    }
    bestand << cpu_vleermuis.size() << "\n";
    for(int i = 0; i < cpu_vleermuis.size(); i++){
        bestand << cpu_vleermuis[i] << "\n";
    }
    bestand << cpu_valkuil.size() << "\n";
    for(int i = 0; i < cpu_valkuil.size(); i++){
        bestand << cpu_valkuil[i] << "\n";
    }
    bestand << route.size() << "\n";
    for(int i = 0; i < route.size(); i++){
        bestand << route[i] << "\n";
    }
    bestand << cpu_wumpus << "\n";
    bestand.close();
    return;
}

void lees_variabel_bestand(){
    int max;
    string line;
    ifstream bestand;
    bestand.open(bestandvariable);
    safe = {};
    getline (bestand, line);
    max = stoi(line);
    for(int i = 0; i < max; i++){
        getline (bestand, line);
        safe.push_back(stoi(line));
    }
    getline (bestand, line);
    max = stoi(line);
    for(int i = 0; i < max; i++){
        getline (bestand, line);
        cpu_vleermuis.push_back(stoi(line));
    }
    getline (bestand, line);
    max = stoi(line);
    for(int i = 0; i < max; i++){
        getline (bestand, line);
        cpu_valkuil.push_back(stoi(line));
    }
    getline (bestand, line);
    max = stoi(line);
    for(int i = 0; i < max; i++){
        getline (bestand, line);
        route_last.push_back(stoi(line));
    }
    getline (bestand, line);
    cpu_wumpus = stoi(line);
    bestand.close();
}

bool check_variabel_leeg(){ //checkt of het tunnel bestand leeg is.
    ifstream bestand(bestandvariable);
    if(bestand.peek() == std::ifstream::traits_type::eof()){ // niet onze code.
        return true;
    }
    return false;
}

void print_all(){
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
    cout << "route: \n";
    for(int i = 0; i < route.size(); i++){
        cout << route[i] << ", ";
    }
    cout << "\n";
    return;
}

int random_buur_vector(const vector<int>& opties){
    int x = rand() % opties.size();
    return opties[x];
}

void remove_from_safe(const int& x){
    vector<int>::iterator itr = find(safe.begin(),safe.end(),x);
    int index = distance(safe.begin(), itr);
    safe.erase(safe.begin()+index);
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
    schrijf_variabel_bestand();
    exit(0);
    return;
}

void check_route_last(){
    bool check = true;
    for(int i = route_last.size()-1; i > -1; i--){
        if(route_last[i] == 99){
            check = false;
            cout << "niet geldige route\n";
            return;
        }
    }
    if(check){
        for(int i = route_last.size()-1; i > -1; i--){
            if(route_last[i] == locatie){
                cout << "route found\n";
                route_index = i;
                route_find = true;
            }
        }
    }
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
        route.push_back(99);
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
    
    if(route_find){
        cout << "\n--route volgen --route_index: " << route_index << "\n";
        if(route_last[route_index+1] )
        verplaats(to_string(route_last[route_index+1]));
        route_index++;
        return;
    }else{
        cout << "--route_find false\n";
        check_route_last();
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
    route.push_back(locatie);
    return;
}