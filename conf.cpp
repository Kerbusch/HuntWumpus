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
int wumpus,bat1,bat2,valkuil1,valkuil2;

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
            bat1 = input;
            break;
        }else if(input < 1 && input > 20){
            cout << "Geef een getal tussen de 1 en de 20.\n";
        }else if(input == wumpus){
            cout << "Deze kamer is al in gebruik. Kies een andere kamer.\n";
        }else{
            cerr << "error bat1";
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
        if(( input >= 1 && input <= 20) && input != wumpus && input != bat1 ){
            bat2 = input;
            break;
        }else if(input < 1 && input > 20){
            cout << "Geef een getal tussen de 1 en de 20.\n";
        }else if(input == wumpus || input == bat1){
            cout << "Deze kamer is al in gebruik. Kies een andere kamer.\n";
        }else{
            cerr << "error bat2";
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
        if(( input >= 1 && input <= 20) && input != wumpus && input != bat1 && input != bat2){
            valkuil1 = input;
            break;
        }else if(input < 1 && input > 20){
            cout << "Geef een getal tussen de 1 en de 20.\n";
        }else if(input == wumpus || input == bat1 || input == bat2){
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
        if(( input >= 1 && input <= 20) && input != wumpus && input != bat1 && input != bat2 && input != valkuil1){
            valkuil2 = input;
            break;
        }else if(input < 1 && input > 20){
            cout << "Geef een getal tussen de 1 en de 20.\n";
        }else if(input == wumpus || input == bat1 || input == bat2 || input == valkuil1){
            cout << "Deze kamer is al in gebruik. Kies een andere kamer.\n";
        }else{
            cerr << "error valkuil2";
            exit(1);
        }
    }
    return;
}

void schrijf_tunnel(){
    ofstream myfile;
    myfile.open(bestandtunnel);
    myfile << "";
    myfile.close();
    myfile.open(bestandtunnel, ofstream::app);
    for(int i = 0; i < kamers_hand.size();i++){
        for(int j = 0; j < kamers_hand[i].size(); j++){
            myfile << kamers_hand[i][j] << "\n";
        }
    }
    myfile << wumpus << "\n";
    myfile << bat1 << "\n";
    myfile << bat2 << "\n";
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
    schrijf_tunnel();
    exit(0);
    return;
}

int random20(){
    int x = rand() % 20 + 1;
    return x;
}

bool testx(int x, const int& random){
    for(int j = 0; j < kamers_rand[x].size(); j++){
        if(kamers_rand[x][j] == random){
            return true;
            //als de tunnel al bestaat
        }
    }
    return false;
}

void generate_tunnels(){
    int random;
    vector<int> nummers = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    for(int i = 0; i < 20; i++){
        while(kamers_rand[i].size() < 3 && nummers[i] < 3){
            random = random20(); // zitten in 1 en krijgen 18
            if(testx(i, random) == false && nummers[random-1] < 3){
                kamers_rand[i].push_back(random); //
                nummers[i]++;
                kamers_rand[random-1].push_back(i+1);
                nummers[random-1]++;
            }
        }
    }
    return;
}

void generate_items(){
    make_wumpus();
    make_bat1();
    make_bat2();
    make_valkuil1();
    make_valkuil2();
    return;
}

void driver_random(){
    srand( (unsigned)time(NULL) );
    generate_tunnels();
    generate_items();
    schrijf_tunnel();
    exit(0);
    return;
}

int main(){
    string line;
    cout << "hand of random: ";
    getline (cin, line);
    if(line == "hand"){
        driver_hand();
    }else if(line == "random"){
        driver_random();
    }else{
        cout << "unknown\n";
    }
}
