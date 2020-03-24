#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

string bestandtunnel = "tunnel.txt";
vector<vector<int>> kamers = {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}};
int wumpus,bat,pit;

int main(){
    string line;
    string uitput;
    ifstream myfile;
    myfile.open(bestandtunnel);
    for(int i = 0; i < 20;i++){
        vector<int> tmp;
        for(int j = 0; j < 3; j++){
            getline (myfile, line);
            kamers[i].push_back(stoi(line));
        }
    }
    getline (myfile, line);
    wumpus = stoi(line);
    getline (myfile, line);
    bat = stoi(line);
    getline (myfile, line);
    pit = stoi(line);
    myfile.close();
    for(int i = 0; i < kamers.size();i++){
        for(int j = 0; j < kamers[i].size(); j++){
            cout << kamers[i][j] << ",";
        }
        cout << "\n";
    }
    cout << wumpus << " " << bat << " " << pit;

}