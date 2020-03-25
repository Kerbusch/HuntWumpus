#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

//Global variable
int locatie = 1;
string bestandtunnel = "tunnel.txt";
vector<vector<int>> kamers = {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}};
int wumpus,bat,pit;


bool check_conf_leeg(){
    //checkt of het configuratie bestand leeg is.
    ifstream conf_bestand(bestandtunnel);
    if(conf_bestand.peek() == std::ifstream::traits_type::eof()){
        return true;
    }
    return false;
}

void lees_conf(){
    //leest het configuratie bestand en importeert de waardes voor de tunnels, wumpus, bat en pit.
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

void verplaats(){
    string string_invoer;
    cout << "\nWaar wil je heen? ";
    getline (cin, string_invoer);
    if(string_invoer.size() > 2){
        cout << "\nGeef waarde tussen 1 en 20.\n";
    }else{
        try{
            int invoer = stoi(string_invoer);
            for(int i = 0; i < 3; i ++){
                if(kamers[locatie-1][i] == invoer){
                    locatie = invoer;
                }
            }
            if(locatie != invoer){
                cerr << "\nJe kan niet naar deze kamer.\n";
            }
        }
        catch(std::invalid_argument){
            cerr << "\nGeef alleen numerieke tekens.\n";
        }
    }
    cout << "\n";
}

void schiet(){
    cout << "schiet!\n";
    return;
}

void test1(){
    cout << "Je bent in kamer: " << locatie << ". De tunnels lijden naar: ";    //cout locatie
    for(int i = 0; i < 3; i ++){    //For-loop die itereerd over de vector met kamers
            cout << kamers[locatie-1][i] << ", ";
    }
    string string_invoer;
    cout << "\nSchiet of verplaats (S of V)? ";
    getline (cin, string_invoer);
    if(string_invoer == "S" || string_invoer == "s"){
        schiet();
    }else if(string_invoer == "V" || string_invoer == "v"){
        verplaats();
    }
    return;
}

int main(){
    if(check_conf_leeg()){
        cerr << "Error: leeg configuratie bestand. Voer eerst de configuratie uit.\n";
        exit(1);
    }
    lees_conf();
    while(true){
        test1();
    }
}