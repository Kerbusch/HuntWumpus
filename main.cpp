#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std;

//Global variable
int locatie = 1;
string bestandtunnel = "tunnel.txt";
vector<vector<int>> kamers = {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}};
int wumpus,bat,pit;
int pijlen = 5;
string buur_error;

bool check_tunnel_leeg(){
    //checkt of het tunnel bestand leeg is.
    ifstream conf_tunnel_bestand(bestandtunnel);
    if(conf_tunnel_bestand.peek() == std::ifstream::traits_type::eof()){
        return true;
    }
    return false;
}

void lees_tunnel(){
    //leest het tunnel bestand en importeert de waardes voor de tunnels, wumpus, bat en pit.
    string line;
    ifstream conf_tunnel_bestand;
    conf_tunnel_bestand.open(bestandtunnel);
    for(int i = 0; i < 20;i++){
        vector<int> tmp;
        for(int j = 0; j < 3; j++){
            getline (conf_tunnel_bestand, line);
            kamers[i].push_back(stoi(line));
        }
    }
    getline (conf_tunnel_bestand, line);
    wumpus = stoi(line);
    getline (conf_tunnel_bestand, line);
    bat = stoi(line);
    getline (conf_tunnel_bestand, line);
    pit = stoi(line);
    conf_tunnel_bestand.close();
    return;
}

bool check_buur(const string& string_invoer){
    if(string_invoer.size() > 2){
        buur_error = "Geef waarde tussen 1 en 20.";
        return false;
    }else{
        try{
            int invoer = stoi(string_invoer);
            for(int i = 0; i < 3; i ++){
                if(kamers[locatie-1][i] == invoer){
                    return true;
                }
            }
            if(locatie != invoer){
                buur_error = "kan_niet";
                return false;
            }
        }
        catch(std::invalid_argument){
            buur_error = "Geef alleen numerieke tekens.";
            return false;
        }
    }
    return false;
}

void verplaats(){
    string string_invoer;
    cout << "\nWaar wil je heen? ";
    getline (cin, string_invoer);
    if(check_buur(string_invoer)){
        int invoer = stoi(string_invoer);
        locatie = invoer;
    }else{
        if(buur_error == "kan_niet"){
            cout << "\n" << "Je hiet niet heen verplaatsen." << "\n";
        }else{
            cout << "\n" << buur_error << "\n";
        }
    }
    cout << "\n";
    return;
}

void verplaats_wumpus(){
    srand( (unsigned)time(NULL) );
    int x = (rand()%19)+1;
    if(x == wumpus){
        x++;
    }
    wumpus = x;
}

void schiet(){
    string string_invoer;
    cout << "\nWaar wil je heen schieten? ";
    getline (cin, string_invoer);
    if(check_buur(string_invoer) && pijlen > 0){
        int invoer = stoi(string_invoer);
        if(invoer == wumpus){
            cout << "hit the wumpus. you win! endgame\n";
            exit(0);
        }else{
            verplaats_wumpus();
        }pijlen--;
    }else if(pijlen <= 0){
        cout << "je pijlen zijn op! endgame\n";
        exit(0);
    }else{
        if(buur_error == "kan_niet"){
            cout << "\n" << "Je hiet niet heen schieten." << "\n";
        }else{
            cout << "\n" << buur_error << "\n";
        }
    }cout << "\n";
    return;
}

bool ruik(){
    // deze funtie kijkt of de wumpus binnen 2 kamers en als dat zo is return hij true
    vector<int> x;
    for(unsigned int i = 0; i < kamers[wumpus-1].size(); i++){
        if(kamers[wumpus-1][i] == locatie){
            return true;
        }
        x.push_back(kamers[wumpus-1][i]);
    }
    for(unsigned int j = 0; j < x.size(); j++){
        for(unsigned int l = 0; l < kamers[x[j]-1].size(); l++){
            if(kamers[x[j]-1][l] == locatie){
                return true;
            }
        }
    }
    return false;
}

void driver(){
    // deze funtie is de code die er voor zorgt dat het spel werkt.
    if(locatie == wumpus){ //eindigt spel als speler op de zelfde locatie is als de wumpus
        cout << "killed by wumpus. endgame\n";
        exit(0);
    }else if(ruik()){ //kijkt of je wumpus kan ruiken
        cout << "Je ruikt een wumpus.\n";
    }
    cout << "Je bent in kamer: " << locatie << ". De tunnels lijden naar: ";    //cout locatie
    for(int i = 0; i < 3; i ++){    //For-loop die itereerd over de vector met kamers
            cout << kamers[locatie-1][i] << ", ";
    }
    string string_invoer; // maakt de string voor de invoer
    cout << "\nSchiet of verplaats (S of V)? "; //print de opties die de gebruiker kan doen
    getline (cin, string_invoer); // leest de invoer can de gebruiker
    if(string_invoer == "S" || string_invoer == "s"){ // kijkt of de gebruiker wil schieten
        schiet();
    }else if(string_invoer == "V" || string_invoer == "v"){ // kijkt of de gebruiker wil verplaatsen
        verplaats();
    }
    return;
}

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