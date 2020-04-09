#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <algorithm>
using namespace std;

string bestandhighscore = "tekst/highscore.txt";
vector<string> namen = {};
vector<int> scores = {};

void schrijf_highscore(string naam, int waarde){
    ofstream bestand;
    bestand.open(bestandhighscore, ofstream::app);
    bestand << naam << "\n";
    bestand << waarde << "\n";
    bestand.close();
    return;
}

void lees_highscore(){
    ifstream high_bestand;
    string line;
    high_bestand.open(bestandhighscore);
    while(getline (high_bestand, line)){
        if(line == ""){
            return;
        }namen.push_back(line);
        getline (high_bestand, line);
        scores.push_back(stoi(line));
    }
}

void top_1(){
    int min = scores[0];
    for(int i = 1; i < scores.size(); i++){
        if(scores[i] < min){
            min = scores[i];
        }
    }
    vector<int>::iterator itr = find(scores.begin(),scores.end(),min); // niet onze code.
    int index = distance(scores.begin(), itr); // niet onze code.
    cout << "--" << namen[index] << " met score: " << scores[index] <<"\n";
    scores.erase(scores.begin()+index);
    namen.erase(namen.begin()+index);
    return;
}

void top_3(){
    lees_highscore();
    if(scores.size() < 3){
        for(int i = 0; i < scores.size()+1; i++){
            cout << i+1 << ": ";
            top_1();
        }
    }else{
        for(int i = 0; i < 3; i++){
            cout << i+1 << ": ";
            top_1();
        }
    }
}

int main(){
    top_3();
}