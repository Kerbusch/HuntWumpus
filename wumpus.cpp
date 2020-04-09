#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string>
#include <algorithm>
using namespace std;

//wumpus header
#include "wumpus.hpp"

//global variables
int locatie = 1;
string bestandtunnel = "tekst/tunnel.txt", bestandinstuctie = "tekst/instructie.txt", buur_error, bestandfaal = "tekst/faal.txt", bestandhighscore = "tekst/highscore.txt", bestandvariable2 = "tekst/variabel.txt";
vector<vector<int>> kamers = {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}};
vector<string> namen = {};
vector<int> scores = {};
int wumpus, vleermuis1, vleermuis2, valkuil1, valkuil2, pijlen = 5, zetten = 1;
bool cpu;

void leeg_variabel(){
    ofstream variabel_bestand;
    variabel_bestand.open(bestandvariable2);
    variabel_bestand << "";
    variabel_bestand.close();
    return;
}

int lees_faal(){
    string line;
    int waarde;
    ifstream faal_bestand;
    faal_bestand.open(bestandfaal);
    getline (faal_bestand, line);
    faal_bestand.close();
    return stoi(line);
}

void schrijf_faal(const int& waarde){
    ofstream faal_bestand;
    faal_bestand.open(bestandfaal);
    faal_bestand << waarde;
    faal_bestand.close();
    return;
}

void faal(){
    int waarde = lees_faal();
    waarde++;
    schrijf_faal(waarde);
    return;
}

void schrijf_highscore(string naam, int waarde){
    ofstream bestand;
    bestand.open(bestandhighscore, ofstream::app);
    bestand << naam << "\n";
    bestand << waarde << "\n";
    bestand.close();
    return;
}

void lees_highscore(){
    ifstream high_bestand;
    string line;
    high_bestand.open(bestandhighscore);
    while(getline (high_bestand, line)){
        if(line == ""){
            return;
        }namen.push_back(line);
        getline (high_bestand, line);
        scores.push_back(stoi(line));
    }
}

void top_1(){
    int min = scores[0];
    for(int i = 1; i < scores.size(); i++){
        if(scores[i] < min){
            min = scores[i];
        }
    }
    vector<int>::iterator itr = find(scores.begin(),scores.end(),min); // niet onze code.
    int index = distance(scores.begin(), itr); // niet onze code.
    cout << namen[index] << " met score: " << scores[index] <<"\n";
    scores.erase(scores.begin()+index);
    namen.erase(namen.begin()+index);
    return;
}

void top_3(){
    lees_highscore();
    if(scores.size() < 3){
        for(int i = 0; i < scores.size()+1; i++){
            cout << i+1 << ": ";
            top_1();
        }
    }else{
        for(int i = 0; i < 3; i++){
            cout << i+1 << ": ";
            top_1();
        }
    }
}

int win(){
    int waarde = lees_faal();
    schrijf_faal(0);
    return waarde+1;
}

int random20(){ // geeft een random getal tussen de 1 en 20.
    int x = rand() % 20 + 1;
    return x;
}

int random_buur(){ // geeft een random buur van de locatie.
    int x = rand() % 3;
    return kamers[locatie-1][x];
}

string actie(){ // 50/50 verplaats of schiet. wordt gebruikt door de CPU
    int x = rand() % 2;
    if(x >= 1){
        return "v";
    }
    return "s";
}

bool check_tunnel_leeg(){ //checkt of het tunnel bestand leeg is.
    ifstream conf_tunnel_bestand(bestandtunnel);
    if(conf_tunnel_bestand.peek() == std::ifstream::traits_type::eof()){ // niet onze code.
        return true;
    }
    return false;
}

void lees_instructie(){
    string invoer, line;
    cout << "Wil je instructies(y/n)? ";
    getline (cin, invoer);
    if(invoer == "y" || invoer == "yes" || invoer == "Y" || invoer == "YES" || invoer == "Yes"){
        ifstream read_bestand;
        read_bestand.open(bestandinstuctie);
        while(getline ( read_bestand, line)){
            cout << line << "\n";
        }
    }
    return;
}

void lees_tunnel(){
    //leest het tunnel bestand en importeert de waardes voor de tunnels, Wumpus, vleermuis en pit.
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
    getline (conf_tunnel_bestand, line); // vleermuis1
    vleermuis1 = stoi(line);
    getline (conf_tunnel_bestand, line); // vleermuis2
    vleermuis2 = stoi(line);
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

void verplaats(string x){
    // verplaats de speler naar een andere kamer.
    string string_invoer;
    cout << "\nWaar wil je heen? ";
    if(x == ""){
        getline (cin, string_invoer);
    }else{
        string_invoer = x;
        cout << "\n\nCPU verplaatst naar: " << x << "\n";
    }
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
        if(x != wumpus && x != vleermuis1 && x != vleermuis2 && x != valkuil1 && x != valkuil2){
            wumpus = x;
            break;
        }
    }
    return;
}

void schiet(string x){
    // schiet funtie
    string string_invoer;
    cout << "\nWaar wil je heen schieten? ";
    if(x == ""){
        getline (cin, string_invoer);
    }else{
        string_invoer = x;
        cout << "\n\nCPU schiet naar: " << x << "\n";
    }
    if(check_buur(string_invoer) && pijlen > 0){ // kijkt of de opgegeven kamer een buur is.
        zetten++;
        int invoer = stoi(string_invoer);
        if(invoer == wumpus){ // kijkt of de Wumpus geraakt wordt.
            int winner = win();
            cout << "\n\nGefeliciteerd! Je hebt de Wumpus gedood! Je hebt er " << winner << " spell(en) over gedaan.\n";
            string line;
            if(not cpu){
                cout << "\n\nNaam: ";
                getline(cin, line);
            }else{
                line = "Computerspeler";
            }
            schrijf_highscore(line,winner);
            cout << "\n\n----------------------------------------\n";
            top_3();
            cout << "----------------------------------------\n";
            leeg_variabel();
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

bool hoor_vleermuis(){
    // deze funtie kijkt of de vleermuis binnen 1 kamers zit en als dat zo is return hij true
    for(unsigned int i = 0; i < kamers[vleermuis1-1].size(); i++){
        if(kamers[vleermuis1-1][i] == locatie){
            return true;
        }
    }
    for(unsigned int i = 0; i < kamers[vleermuis2-1].size(); i++){
        if(kamers[vleermuis2-1][i] == locatie){
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
    if(locatie == vleermuis1 || locatie == vleermuis2){
        return true;
    }
    return false;
}

void driver(string x){
    if(cpu){
        cout << "----------------------------------------\n";
        string tmp_invoer;
        cout << "(druk op enter om verder te gaan: )";
        getline(cin, tmp_invoer);
    }
    
    // deze funtie is de code die er voor zorgt dat het spel werkt.
    string string_random = "";
    cout << "----------------------------------------\n";
    

    if(locatie == wumpus){ //eindigt spel als speler op de zelfde locatie is als de Wumpus
        cout << "Helaas je bent opgegeten door de Wumpus, GAME OVER!\n";
        faal();
        exit(0);
    }
    else if(pijlen <= 0){
        cout << "Je pijlen zijn op! GAME OVER!\n";
        faal();
        exit(0);
    }
    else if(valkuil_check()){
        cout << "Je ben in een put gevallen! GAME OVER!\n";
        faal();
        exit(0);
    }
    else if(vleermuis_check()){
        while(true){
            int random = random20();
            if(random != vleermuis1 && random != vleermuis2){
                locatie = random;
                cout << "In deze kamer zit een Supervleermuis, hij verplaatst je naar kamer " << random << "!\n\n";
                break;
            }
        }
        return;
    }

    if(zetten >= 20){
        cout << "Je kan de oplossing krijgen als je door: 'help' te typen.\n";
    }

    if(ruik()){ //kijkt of je Wumpus kan ruiken
        cout << "\n" << "Je ruikt de Wumpus.\n";
    }
    if(hoor_vleermuis()){ //kijkt of je vleermuis hoort
        cout << "\nJe hoort geflapper van een Supervleermuis.\n";
    }
    if(voelWind()){ //kijkt of je wind voelt
        cout << "\nJe voelt een lichte bries.\n";
    }
    cout << "\nZet: " << zetten << "\n";
    cout << "Je bent in kamer: " << locatie << ". De tunnels leiden naar kamers: ";    //cout locatie
    for(int i = 0; i < 3; i ++){    //For-loop die itereerd over de vector met kamers
            cout << kamers[locatie-1][i] << ", ";
    }
    string string_invoer; // maakt de string voor de invoer
    
    cout << "\nSchiet of verplaats (S of V)? "; //print de opties die de gebruiker kan doen
    if(x == "v" || x == "s"){ // kijkt of de code wordt gebruikt door een echte speler of computer spelen en vraagt een cin bij de echte speler.
        string_invoer = x;
        string_random = to_string(random_buur());
    }else{
        getline (cin, string_invoer); // leest de invoer can de gebruiker
    }
    if(string_invoer == "S" || string_invoer == "s"){ // kijkt of de gebruiker wil schieten
        schiet(string_random);
    }
    else if(string_invoer == "V" || string_invoer == "v"){ // kijkt of de gebruiker wil verplaatsen
        verplaats(string_random);
    }else if((string_invoer == "help" || string_invoer == "HELP") && zetten >= 20){
        cout << "\nJammer dat je opgeeft, maar hier zijn de locaties:\n";
        cout << "De wumpus zit in kamer: " << wumpus << "\n";
        cout << "De vleermuizen zitten in kamers: " << vleermuis1 << " en " << vleermuis2 << "\n";
        cout << "De valkuilen zitten in kamers: " << valkuil1 << " en " << valkuil2 << "\n\n";
    }
    return;
}