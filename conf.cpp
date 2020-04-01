#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

string bestandtunnel = "tunnel.txt";
vector<vector<int>> kamers = {{2,5,8}, {1,3,10}, {2,4,12}, {3,5,14}, {1,4,6}, {5,7,13}, {6,8,17}, {1,7,9}, {8,10,18}, {2,9,11}, {10,12,19}, {3,11,13}, {12,14,20}, {4,13,15}, {6,14,16}, {15,17,20}, {7,16,18},{8,17,19}, {11,18,20}, {13,16,19}};
int wumpus,bat,pit;

int roel = 0

int main(){
    string line;
    int wumpus_input, bat_input, pit_input;
    while(true){
        cout << "In welke kamer moet de Wumpus zitten (1-20)? ";
        cin >> wumpus_input; // 15
        if( wumpus_input >= 1 || wumpus_input <= 20){
            wumpus = wumpus_input;
            break;
        }
    }
    while(true){
        cout << "In welke kamer moet de bat zitten (1-20)? ";
        cin >> bat_input;
        if(( bat_input >= 1 || bat_input <= 20) && bat_input != wumpus){
            bat = bat_input;
            break;
        }else if(bat_input == wumpus){
            cout << "De bat en de wumpus kunnen niet op de zelfde plaats zitten.\n";
        }
    }
    while(true){
        cout << "In welke kamer moet de pit zitten (1-20)? ";
        cin >> pit_input;
        if(( pit_input >= 1 || pit_input <= 20) && pit_input != wumpus && pit_input != bat){
            pit = pit_input;
            break;
        }else if(pit_input == wumpus || pit_input == bat){
            cout << "De pit en de wumpus en / of bat kunnen niet op de zelfde plaats zitten.\n";
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
    myfile << wumpus << "\n" << bat << "\n" << pit;
    myfile.close();
    return false;
    
}
