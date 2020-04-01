#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

string bestandtunnel = "tunnel.txt";
vector<vector<int>> kamers = {{2,5,8}, {1,3,10}, {2,4,12}, {3,5,14}, {1,4,6}, {5,7,13}, {6,8,17}, {1,7,9}, {8,10,18}, {2,9,11}, {10,12,19}, {3,11,13}, {12,14,20}, {4,13,15}, {6,14,16}, {15,17,20}, {7,16,18},{8,17,19}, {11,18,20}, {13,16,19}};
int wumpus,bat1,bat2,valkuil1,valkuil2;

int main(){
    string line;
    int wumpus_input, bat1_input, bat2_input, valkuil1_input, valkuil2_input;

    while(true){ //wumpus
        cout << "In welke kamer moet de Wumpus zitten (1-20)? ";
        cin >> wumpus_input;
        if( wumpus_input >= 1 && wumpus_input <= 20){
            wumpus = wumpus_input;
            break;
        }else if(bat1_input < 1 && bat1_input > 20){
            cout << "Geef een getal tussen de 1 en de 20.\n";
        }else{
            cerr << "error wumpus";
        }
    }

    while(true){ //bat 1
        cout << "In welke kamer moet de eerste bat zitten (1-20)? ";
        cin >> bat1_input;
        if(( bat1_input >= 1 && bat1_input <= 20) && bat1_input != wumpus){
            bat1 = bat1_input;
            break;
        }else if(bat1_input < 1 && bat1_input > 20){
            cout << "Geef een getal tussen de 1 en de 20.\n";
        }else if(bat1_input == wumpus){
            cout << "Deze kamer is al in gebruik. Kies een andere kamer.\n";
        }else{
            cerr << "error bat1";
        }
    }
    
    while(true){ // bat 2
        cout << "In welke kamer moet de tweede bat zitten (1-20)? ";
        cin >> bat2_input;
        if(( bat2_input >= 1 && bat2_input <= 20) && bat2_input != wumpus && bat2_input != bat1 ){
            bat2 = bat2_input;
            break;
        }else if(bat1_input < 1 && bat1_input > 20){
            cout << "Geef een getal tussen de 1 en de 20.\n";
        }else if(bat2_input == wumpus || bat2_input == bat1){
            cout << "Deze kamer is al in gebruik. Kies een andere kamer.\n";
        }else{
            cerr << "error bat2";
        }
    }

    while(true){ //valkuil 1
        cout << "In welke kamer moet de eerste valkuil zitten (1-20)? ";
        cin >> valkuil1_input;
        if(( valkuil1_input >= 1 && valkuil1_input <= 20) && valkuil1_input != wumpus && valkuil1_input != bat1 && valkuil1_input != bat2){
            valkuil1 = valkuil1_input;
            break;
        }else if(bat1_input < 1 && bat1_input > 20){
            cout << "Geef een getal tussen de 1 en de 20.\n";
        }else if(valkuil1_input == wumpus || valkuil1_input == bat1 || valkuil1_input == bat2){
            cout << "Deze kamer is al in gebruik. Kies een andere kamer.\n";
        }else{
            cerr << "error valkuil1";
        }
    }

    while(true){ //valkuil 2
        cout << "In welke kamer moet de tweede valkuil zitten (1-20)? ";
        cin >> valkuil2_input;
        if(( valkuil2_input >= 1 && valkuil2_input <= 20) && valkuil2_input != wumpus && valkuil2_input != bat1 && valkuil2_input != bat2 && valkuil2_input != valkuil1){
            valkuil2 = valkuil2_input;
            break;
        }else if(bat1_input < 1 && bat1_input > 20){
            cout << "Geef een getal tussen de 1 en de 20.\n";
        }else if(valkuil2_input == wumpus || valkuil2_input == bat1 || valkuil2_input == bat2 || valkuil2_input == valkuil1){
            cout << "Deze kamer is al in gebruik. Kies een andere kamer.\n";
        }else{
            cerr << "error valkuil2";
        }
    }
    

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
    myfile << bat1 << "\n";
    myfile << bat2 << "\n";
    myfile << valkuil1 << "\n";
    myfile << valkuil2 << "\n";
    myfile.close();
    return false;
    
}
