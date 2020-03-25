//
//  main.cpp
//  huntTheWumpus
//
//  Created by Roel Stierum on 24/03/2020.
//  Copyright © 2020 Roel Stierum. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

//Global variable
int locatie = 1;
vector<vector<int>> kamers = {{2,5,8}, {1,3,10}, {2,4,12}, {3,5,14}, {1,4,6}, {5,7,13}, {6,8,17}, {1,7,9}, {8,10,18}, {2,9,11}, {10,12,19}, {3,11,13}, {12,14,20}, {4,13,15}, {6,14,16}, {15,17,20}, {7,16,18},{8,17,19}, {11,18,20}, {13,16,19}};

//main code
int main(){
    while(true){
        int input;
        string string_input;
//        Vraagt om een locatie
        cout << "Je bent in kamer: " << locatie << ". Je kan verplaatsen naar: ";
//        For-loop die itereerd over de vector met kamers
        for(int i = 0; i < 3; i ++){
            cout << kamers[locatie-1][i] << ", ";
        }
//        Vraagt waar je heen wil en zet de waarde in int input
        cout << "\n" << "Waar wil je heen? ";
        getline (cin, string_input);
//        Zorgt ervoor dat alleen int's kunnen worden gegeven
        if(string_input.size() > 2){
            cout << "\n" << "Geef waarde tussen 1 en 20." << "\n\n";
        }else{
            try{
                input = stoi(string_input);
                for(int i = 0; i < 3; i ++){
                    if(kamers[locatie-1][i] == input){
                        locatie = input;
                    }
                }
                if(locatie != input){
                    cerr << "\n" << "Je kan niet naar deze kamer." << "\n\n";
                }
            }
            catch(std::invalid_argument){
                cerr << "\n" << "Geef alleen numerieke tekens." << "\n\n";
            }
        }
    }
}
