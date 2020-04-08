#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

string bestandtunnel = "tekst/tunnel.txt", bestandfaal = "tekst/faal.txt";
vector<vector<int>> kamers_hand = {{2,5,8}, {1,3,10}, {2,4,12}, {3,5,14}, {1,4,6}, {5,7,15}, {6,8,17}, {1,7,9}, {8,10,18}, {2,9,11}, {10,12,19}, {3,11,13}, {12,14,20}, {4,13,15}, {6,14,16}, {15,17,20}, {7,16,18},{9,17,19}, {11,18,20}, {13,16,19}};
vector<vector<int>> kamers_rand = {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}};
int wumpus,vleermuis1,vleermuis2,valkuil1,valkuil2;

void leeg_faal(){
    ofstream faal_bestand;
    faal_bestand.open(bestandfaal);
    faal_bestand << 0;
    faal_bestand.close();
    return;
}

int check_input(const string& input){ //checkt of de locatie waar de gebruiker het item wil plaatsen kan en of er geen conflict
    try{
        int x = stoi(input);
        if(x == wumpus || x == vleermuis1 || x == vleermuis2 || x == valkuil1 || x == valkuil2){
            cout << "De locatie mag niet het zelfde zijn als de andere items.\n\n";
            return -1;
        }else if(x < 1 || x > 20){
            cout << "Geef een getal tussen de 1 en de 20.\n\n";
            return -1;
        }else{
            return x;
        }
    }catch(std::invalid_argument){
        cout << "Geef alleen numerieke tekens.\n\n";
        return -1;
    }
    return -1;
}

void make_wumpus(){ //vraagt de gebruiker waar de wumpus moet zitten
    string line;
    while(true){
        cout << "In welke kamer moet de Wumpus zitten (1-20)? ";
        getline (cin, line);
        int x = check_input(line);
        if(x != -1){
            wumpus = x;
            break;
        }
    }
    return;
}

void make_vleermuis1(){ //vraagt de gebruiker waar de 1e vleermuis moet zitten
    string line;
    while(true){
        cout << "In welke kamer moet de eerste vleermuis zitten (1-20)? ";
        getline (cin, line);
        int x = check_input(line);
        if(x != -1){
            vleermuis1 = x;
            break;
        }
    }
    return;
}

void make_vleermuis2(){ //vraagt de gebruiker waar de 2e vleermuis moet zitten
    string line;
    while(true){
        cout << "In welke kamer moet de tweede vleermuis zitten (1-20)? ";
        getline (cin, line);
        int x = check_input(line);
        if(x != -1){
            vleermuis2 = x;
            break;
        }
    }
    return;
}

void make_valkuil1(){ //vraagt de gebruiker waar de 1e valkuil moet zitten
    string line;
    while(true){
        cout << "In welke kamer moet de eerste valkuil zitten (1-20)? ";
        getline (cin, line);
        int x = check_input(line);
        if(x != -1){
            valkuil1 = x;
            break;
        }
    }
    return;
}

void make_valkuil2(){ //vraagt de gebruiker waar de 2e valkuil moet zitten
    string line;
    while(true){ 
        cout << "In welke kamer moet de tweede valkuil zitten (1-20)? ";
        getline (cin, line);
        int x = check_input(line);
        if(x != -1){
            valkuil2 = x;
            break;
        }
    }
    return;
}

void schrijf_tunnel(const vector<vector<int>>& kamers){ // schrijft de tunnels en de andere items naar het bestand
    ofstream myfile;
    myfile.open(bestandtunnel);
    myfile << "";
    myfile.close();
    myfile.open(bestandtunnel, ofstream::app);
    for(int i = 0; i < kamers.size();i++){
        for(int j = 0; j < kamers[i].size(); j++){
            myfile << kamers[i][j] << "\n";
        }
    }
    myfile << wumpus << "\n";
    myfile << vleermuis1 << "\n";
    myfile << vleermuis2 << "\n";
    myfile << valkuil1 << "\n";
    myfile << valkuil2 << "\n";
    myfile.close();
    return;
}

void driver_hand(){ // de driver code voor het handmatig invoeren van de locaties
    make_wumpus();
    make_vleermuis1();
    make_vleermuis2();
    make_valkuil1();
    make_valkuil2();
    schrijf_tunnel(kamers_hand);
    cout << "\nConfiguratie gelukt. Je kan nu het spel spelen met deze configuratie\n\n"; 
    exit(0);
    return;
}

//code voor random

int random20(){ // maakt een random getal tussen de 1 en de 20
    int x = rand() % 20 + 1;
    return x;
}

int random_gen(int x){ // maakt een random getal tussen de 1 en de 20, maar slaat de eerste x over
    return rand() % (20-x) + (1+x);
}

bool check_limit(int x, const int& random){ // checkt of de code kamers het aantal max tunnels zit
    for(int j = 0; j < kamers_rand[x].size(); j++){
        if(kamers_rand[x][j] == random){
            return true;
        }
    }
    return false;
}

bool generate_tunnels(){ // genereert random de tunnels tussen de kamers
    kamers_rand = {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}};
    int random, trys;
    vector<int> nummers = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    for(int i = 0; i < 20; i++){
        trys = 0;
        while(kamers_rand[i].size() < 3){
            if(trys > 20){
                return false;
            }
            random = random_gen(i);
            if(check_limit(i, random) == false && nummers[random-1] < 3 && random != i+1){
                kamers_rand[i].push_back(random); //
                nummers[i]++;
                kamers_rand[random-1].push_back(i+1);
                nummers[random-1]++;
            }
            trys++;
        }
    }
    //for(int i = 0; i < kamers_rand.size(); i++){
    //    for(int j = 0; j < kamers_rand[i].size(); j++){
    //        cout << kamers_rand[i][j] << ",";
    //    }
    //    cout << "\n";
    //}
    return true;
}

bool check_item_conflict(const int& random){ // true als er een conflict is anders false
    if(random == wumpus || random == vleermuis1 || random == vleermuis2 || random == valkuil1 || random == valkuil2){
        return true;
    }
    return false;
}

void generate_items(){ // geeft de items een random plek die net conflict
    int random;
    wumpus = random20();
    while(true){
        random = random20();
        if(not check_item_conflict(random)){
            vleermuis1 = random;
            break;
        }
    }
    while(true){
        random = random20();
        if(not check_item_conflict(random)){
            vleermuis2 = random;
            break;
        }
    }
    while(true){
        random = random20();
        if(not check_item_conflict(random)){
            valkuil1 = random;
            break;
        }
    }
    while(true){
        random = random20();
        if(not check_item_conflict(random)){
            valkuil2 = random;
            break;
        }
    }
    return;
}

void driver_random(){ // driver code voor het random maken van de tunnels en items
    srand( (unsigned)time(NULL) );
    while(true){
        if(generate_tunnels()){
            cout << "done\n";
            break;
        }
        cout << "error: retrying\n";
    }
    generate_items();
    schrijf_tunnel(kamers_rand);
    leeg_faal();
    cout << "\nConfiguratie gelukt. Je kan nu het spel spelen met deze configuratie\n\n"; 
    exit(0);
    return;
}

int main(){ // main code
    string line;
    cout << "Wil je de voorgedefinieerde tunnels gebruiken of ze random genergen?\n(voor of random): ";
    getline (cin, line);
    if(line == "voor"){
        driver_hand();
    }else if(line == "random"){
        driver_random();
    }else{
        cout << "unknown\n";
    }
}