#ifndef wumpus_hpp
#define wumpus_hpp

#include "wumpus.cpp"

int random20();
bool check_bestand_leeg();
void lees_instructie();
void lees_tunnel();
bool check_buur(const string& string_invoer);
void verplaats();
void verplaats_wumpus();
void schiet();
bool ruik();
bool hoorBat();
bool voelWind();
bool valkuil_check();
bool vleermuis_check();
void driver();

#endif /* wumpus_hpp */