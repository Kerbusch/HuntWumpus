#ifndef header_hpp
#define header_hpp
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string>
using namespace std;

//Global variable
int locatie = 1;
string bestandtunnel = "tunnel.txt";
vector<vector<int>> kamers = {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}};
int wumpus,bat1,bat2,valkuil1,valkuil2;
int pijlen = 5;
string buur_error;
int zetten = 0;
bool helper = false;
string instructies = "instructie.txt";

void lees_instructie(){
    string invoer, line;
    cout << "Wil je instructies(y/n)? ";
    getline (cin, invoer);
    if(invoer == "y" || invoer == "yes" || invoer == "Y" || invoer == "YES" || invoer == "Yes"){
        ifstream read_bestand;
        read_bestand.open(instructies);
        while(getline ( read_bestand, line)){
            cout << line << "\n";
        }
    }
    return;
}
int random20(){
    int x = rand() % 20 + 1;
    return x;
}

bool check_tunnel_leeg(){
    //checkt of het tunnel bestand leeg is.
    ifstream conf_tunnel_bestand(bestandtunnel);
    if(conf_tunnel_bestand.peek() == std::ifstream::traits_type::eof()){ // niet onze code
        return true;
    }
    return false;
}

void lees_tunnel(){
    //leest het tunnel bestand en importeert de waardes voor de tunnels, Wumpus, bat en pit.
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

bool check_buur(const string& string_invoer){
    // kijkt of de ingevoerde waarde een buur is van de locatie van de speler.
    if(string_invoer.size() > 2){
        buur_error = "Geef een waarde tussen 1 en 20.";
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
    // verplaats de speler naar een andere kamer.
    string string_invoer;
    cout << "\nWaar wil je heen? ";
    getline (cin, string_invoer);
    if(check_buur(string_invoer)){
        zetten++;
        int invoer = stoi(string_invoer);
        locatie = invoer;
    }else{
        if(buur_error == "kan_niet"){
            cout << "\n" << "Je kan hier niet heen verplaatsen." << "\n";
        }else{
            cout << "\n" << buur_error << "\n";
        }
    }
    cout << "\n";
    return;
}

void verplaats_wumpus(){
    // verplaatst de Wumpus naar een random kamer.
    int x;
    while(true){
        x = random20();
        if(x != wumpus && x != bat1 && x != bat2 && x != valkuil1 && x != valkuil2){
            wumpus = x;
            break;
        }
    }
    return;
}

void schiet(){
    // schiet funtie
    string string_invoer;
    cout << "\nWaar wil je heen schieten? ";
    getline (cin, string_invoer);
    if(check_buur(string_invoer) && pijlen > 0){ // kijkt of de opgegeven kamer een buur is.
        zetten++;
        int invoer = stoi(string_invoer);
        if(invoer == wumpus){ // kijkt of de Wumpus geraakt wordt.
            cout << "Gefeliciteerd! Je hebt de Wumpus gedood!\n";
            exit(0);
        }
        else{
            cout << "\nMis! Je hebt de Wumpus gemist.\n";
            verplaats_wumpus();
        }pijlen--;
        cout << "Je hebt nog " << pijlen << " pijl(en) over.\n";
    }
    else{
        if(buur_error == "kan_niet"){
            cout << "\n" << "Je kan hier niet heen schieten." << "\n";
        }else{
            cout << "\n" << buur_error << "\n";
        }
    }cout << "\n";
    return;
}

bool ruik(){
    // deze funtie kijkt of de Wumpus binnen 2 kamers en als dat zo is return hij true
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

bool hoorBat(){
    // deze funtie kijkt of de bat binnen 1 kamers zit en als dat zo is return hij true
    for(unsigned int i = 0; i < kamers[bat1-1].size(); i++){
        if(kamers[bat1-1][i] == locatie){
            return true;
        }
    }
    for(unsigned int i = 0; i < kamers[bat2-1].size(); i++){
        if(kamers[bat2-1][i] == locatie){
            return true;
        }
    }
    return false;
}

bool voelWind(){
    // deze funtie kijkt of de valkuil binnen 1 kamers zit en als dat zo is return hij true
    for(unsigned int i = 0; i < kamers[valkuil1-1].size(); i++){
        if(kamers[valkuil1-1][i] == locatie){
            return true;
        }
    }
    for(unsigned int i = 0; i < kamers[valkuil2-1].size(); i++){
        if(kamers[valkuil2-1][i] == locatie){
            return true;
        }
    }
    return false;
}

bool valkuil_check(){
    // deze functie kijkt of de speler in een valkuil terecht is gekomen.
    if(locatie == valkuil1 || locatie == valkuil2){
        return true;
    }
    return false;
}

bool vleermuis_check(){
    // deze functie kijkt of de speler in een kamer met een vleermuis is.
    if(locatie == bat1 || locatie == bat2){
        return true;
    }
    return false;
}

void driver(){
    // deze funtie is de code die er voor zorgt dat het spel werkt.
    if(locatie == wumpus){ //eindigt spel als speler op de zelfde locatie is als de Wumpus
        cout << "Helaas je bent opgegeten door de Wumpus, GAME OVER!\n";
        exit(0);
    }
    else if(pijlen <= 0){
        cout << "Je pijlen zijn op! GAME OVER!\n";
        exit(0);
    }
    else if(valkuil_check()){
        cout << "Je ben in een put gevallen! GAME OVER!\n";
        exit(0);
    }
    else if(vleermuis_check()){
        while(true){
            int random = random20();
            if(random != bat1 && random != bat2){
                locatie = random;
                cout << "In deze kamer zit een Supervleermuis, hij verplaatst je naar kamer " << random << "!\n\n";
                break;
            }
        }
        return;
    }

    if(zetten == 20 && not helper){
        cout << "Je kan de oplossing krijgen als je door: 'help' te typen.\n";
    }

    if(ruik()){ //kijkt of je Wumpus kan ruiken
        cout << "\n" << "Je ruikt de Wumpus.\n";
    }
    if(hoorBat()){ //kijkt of je bat hoort
        cout << "Je hoort geflapper van een Supervleermuis.\n";
    }
    if(voelWind()){ //kijkt of je wind voelt
        cout << "Je voelt een lichte bries.\n";
    }
    cout << "\nJe bent in kamer: " << locatie << ". De tunnels leiden naar kamers: ";    //cout locatie
    for(int i = 0; i < 3; i ++){    //For-loop die itereerd over de vector met kamers
            cout << kamers[locatie-1][i] << ", ";
    }
    string string_invoer; // maakt de string voor de invoer
    cout << "\nSchiet of verplaats (S of V)? "; //print de opties die de gebruiker kan doen
    getline (cin, string_invoer); // leest de invoer can de gebruiker
    if(string_invoer == "S" || string_invoer == "s"){ // kijkt of de gebruiker wil schieten
        schiet();
    }
    else if(string_invoer == "V" || string_invoer == "v"){ // kijkt of de gebruiker wil verplaatsen
        verplaats();
    }else if((string_invoer == "help" || string_invoer == "HELP") && zetten >= 20){
        cout << "\nJammer dat je opgeeft, maar hier zijn de locaties:\n";
        cout << "De wumpus zit in kamer: " << wumpus << "\n";
        cout << "De vleermuizen zitten in kamers: " << bat1 << " en " << bat2 << "\n";
        cout << "De valkuilen zitten in kamers: " << valkuil1 << " en " << valkuil2 << "\n\n";
        helper = true;
    }
    return;
}

#endif /* header_hpp */