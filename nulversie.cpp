#include <iostream>
#include <vector>
using namespace std;

//Global variable
int locatie = 1;
vector<vector<int>> kamers = {{2,4,8},{1,3,7},{2,4,6},{1,3,5},{4,6,8},{3,5,7},{2,6,8},{1,5,7}};

int main(){
    while(true){
        int invoer;
        cout << "Locatie: " << locatie << ". De andere locaties zijn: ";
        for(int i = 0; i < 3; i ++){
            cout << kamers[locatie-1][i] << ", ";
        }
        cout << "\nWaar: ";
        cin >> invoer;
        for(int i = 0; i < 3; i ++){
            if(kamers[locatie-1][i] == invoer){
                locatie = invoer;
            }
        }
        if(locatie != invoer){
            cerr << "Kan niet\n";
        }
    }
}