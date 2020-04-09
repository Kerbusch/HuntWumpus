#ifndef wumpus_hpp
#define wumpus_hpp

#include "wumpus.cpp"

void leeg_variabel();
int lees_faal();
void schrijf_faal(const int& waarde);
void faal();
void schrijf_highscore(string naam, int waarde);
void lees_highscore();
void top_1();
void top_3();
int win();
int random20();
int random_buur();
string actie();
bool check_tunnel_leeg();
void lees_instructie();
void lees_tunnel();
bool check_buur(const string& string_invoer);
void verplaats(string x);
void verplaats_wumpus();
void schiet(string x);
bool ruik();
bool hoor_vleermuis();
bool voelWind();
bool valkuil_check();
bool vleermuis_check();
void driver(string x);

#endif /* wumpus_hpp */