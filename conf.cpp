#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

string bestandtunnel = "tunnel.txt";
vector<vector<int>> kamers = {{2,5,8}, {1,3,10}, {2,4,12}, {3,5,14}, {1,4,6}, {5,7,13}, {6,8,17}, {1,7,9}, {8,10,18}, {2,9,11}, {10,12,19}, {3,11,13}, {12,14,20}, {4,13,15}, {6,14,16}, {15,17,20}, {7,16,18},{8,17,19}, {11,18,20}, {13,16,19}};
int wumpus,bat1,bat2;
vector<int> valkuil = {};

int main(){
    string line;
    int wumpus_input, bat1_input, bat2_input,valkuil_input;

    while(true){
        cout << "In welke kamer moet de Wumpus zitten (1-20)? ";
        cin >> wumpus_input; // 15
        if( wumpus_input >= 1 || wumpus_input <= 20){
            wumpus = wumpus_input;
            break;
        }
    }

    while(true){
        cout << "In welke kamer moet de eerste bat zitten (1-20)? ";
        cin >> bat1_input;
        if(( bat1_input >= 1 || bat1_input <= 20) && bat1_input != wumpus){
            bat1 = bat1_input;
            break;
        }else if(bat1_input == wumpus){
            cout << "De 1ste bat en de wumpus kunnen niet op de zelfde plaats zitten.\n";
        }
    }
    
    while(true){
        cout << "In welke kamer moet de tweede bat zitten (1-20)? ";
        cin >> bat2_input;
        if(( bat2_input >= 1 || bat2_input <= 20) && bat2_input != wumpus && bat2_input != bat1){
            bat2 = bat2_input;
            break;
        }else if(bat2_input == wumpus || bat2_input == bat1){
            cout << "De 2e bat en de wumpus en / of 1ste bat kunnen niet op de zelfde plaats zitten.\n";
        }
    }
    //valkuilen
    while(true){
        bool val_error = false;
        cout << "In welke kamer moet een valkuil zitten (1-20)?\nType 0 als je klaar bent met de valkuilen. ";
        cin >> valkuil_input;
        if(valkuil_input == wumpus || valkuil_input == bat1 || valkuil_input == bat2){
            cout << "De valkuil kan hier niet zitten probeer een andere plek.\n";
            val_error == true;
        }
        for(int i = 0; i < valkuil.size(); i++){
            if(valkuil_input == valkuil[i]){
                cout << "De valkuil kan hier niet zitten probeer een andere plek.\n";
                val_error == true;
            }
        }
        if(( valkuil_input >= 1 || valkuil_input <= 20) && val_error == false){
            valkuil.push_back(valkuil_input);
        }
        if(valkuil_input == 0){
            break;
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
    myfile << wumpus << "\n" << bat1 << "\n" << bat2 << "\n" << valkuil.size() << "\n";
    for(int i = 0; i < valkuil.size(); i++){
        myfile << valkuil[i] << "\n";
    }
    myfile.close();
    return false;
    
}
