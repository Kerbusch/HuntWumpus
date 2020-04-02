#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <stdio.h>
using namespace std;

string bestandtunnel = "tunnel.txt";
vector<vector<int>> kamers_hand = {{2,5,8}, {1,3,10}, {2,4,12}, {3,5,14}, {1,4,6}, {5,7,15}, {6,8,17}, {1,7,9}, {8,10,18}, {2,9,11}, {10,12,19}, {3,11,13}, {12,14,20}, {4,13,15}, {6,14,16}, {15,17,20}, {7,16,18},{9,17,19}, {11,18,20}, {13,16,19}};
vector<vector<int>> kamers_rand = {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}};
int wumpus,vleermuis1,vleermuis2,valkuil1,valkuil2;

void make_wumpus(){
    string line;
    int input;
    while(true){ //wumpus
        cout << "In welke kamer moet de Wumpus zitten (1-20)? ";
        cin >> input;
        if( input >= 1 && input <= 20){
            wumpus = input;
            break;
        }else if(input < 1 && input > 20){
            cout << "Geef een getal tussen de 1 en de 20.\n";
        }else{
            cerr << "error wumpus";
            exit(1);
        }
    }
    return;
}

void make_bat1(){
    string line;
    int input;
    while(true){ //bat 1
        cout << "In welke kamer moet de eerste bat zitten (1-20)? ";
        cin >> input;
        if(( input >= 1 && input <= 20) && input != wumpus){
            vleermuis1 = input;
            break;
        }else if(input < 1 && input > 20){
            cout << "Geef een getal tussen de 1 en de 20.\n";
        }else if(input == wumpus){
            cout << "Deze kamer is al in gebruik. Kies een andere kamer.\n";
        }else{
            cerr << "error vleermuis1";
            exit(1);
        }
    }
    return;
}

void make_bat2(){
    string line;
    int input;
    while(true){ // bat 2
        cout << "In welke kamer moet de tweede bat zitten (1-20)? ";
        cin >> input;
        if(( input >= 1 && input <= 20) && input != wumpus && input != vleermuis1 ){
            vleermuis2 = input;
            break;
        }else if(input < 1 && input > 20){
            cout << "Geef een getal tussen de 1 en de 20.\n";
        }else if(input == wumpus || input == vleermuis1){
            cout << "Deze kamer is al in gebruik. Kies een andere kamer.\n";
        }else{
            cerr << "error vleermuis2";
            exit(1);
        }
    }
    return;
}

void make_valkuil1(){
    string line;
    int input;
    while(true){ //valkuil 1
        cout << "In welke kamer moet de eerste valkuil zitten (1-20)? ";
        cin >> input;
        if(( input >= 1 && input <= 20) && input != wumpus && input != vleermuis1 && input != vleermuis2){
            valkuil1 = input;
            break;
        }else if(input < 1 && input > 20){
            cout << "Geef een getal tussen de 1 en de 20.\n";
        }else if(input == wumpus || input == vleermuis1 || input == vleermuis2){
            cout << "Deze kamer is al in gebruik. Kies een andere kamer.\n";
        }else{
            cerr << "error valkuil1";
            exit(1);
        }
    }
    return;
}

void make_valkuil2(){
    string line;
    int input;
    while(true){ //valkuil 2
        cout << "In welke kamer moet de tweede valkuil zitten (1-20)? ";
        cin >> input;
        if(( input >= 1 && input <= 20) && input != wumpus && input != vleermuis1 && input != vleermuis2 && input != valkuil1){
            valkuil2 = input;
            break;
        }else if(input < 1 && input > 20){
            cout << "Geef een getal tussen de 1 en de 20.\n";
        }else if(input == wumpus || input == vleermuis1 || input == vleermuis2 || input == valkuil1){
            cout << "Deze kamer is al in gebruik. Kies een andere kamer.\n";
        }else{
            cerr << "error valkuil2";
            exit(1);
        }
    }
    return;
}

void schrijf_tunnel(const vector<vector<int>>& kamers){
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

void driver_hand(){
    make_wumpus();
    make_bat1();
    make_bat2();
    make_valkuil1();
    make_valkuil2();
    schrijf_tunnel(kamers_hand);
    exit(0);
    return;
}

//code voor random

int random20(){
    int x = rand() % 20 + 1;
    return x;
}

int random_gen(int x){
    return rand() % (20-x) + (1+x);
}

bool check_limit(int x, const int& random){
    for(int j = 0; j < kamers_rand[x].size(); j++){
        if(kamers_rand[x][j] == random){
            return true;
        }
    }
    return false;
}

bool generate_tunnels(){ // hij loopt vaak en als hij loopt zit hij vast omdat hij als enige optie heeft om een kamer met zich zelf te verbinden. dus nummer allemaal op 3 behalve 1
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

void generate_items(){
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

void driver_random(){
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
    exit(0);
    return;
}

int main(){
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
