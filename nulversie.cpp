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
vector<vector<int>> kamers = {{2,4,8},{1,3,7},{2,4,6},{1,3,5},{4,6,8},{3,5,7},{2,6,8},{1,5,7}};

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
