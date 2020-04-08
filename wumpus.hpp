#ifndef wumpus_hpp
#define wumpus_hpp

#include "wumpus.cpp"

int random20();
int random_buur();
string actie();
bool check_bestand_leeg();
void lees_instructie();
void lees_tunnel();
bool check_buur(const string& string_invoer);
void verplaats();
void verplaats_wumpus();
void schiet();
bool ruik();
bool hoor_vleermuis();
bool voelWind();
bool valkuil_check();
bool vleermuis_check();
void driver();

#include "cpu.cpp"

void schrijf_variabel_bestand();
void lees_variabel_bestand();
bool check_variabel_leeg();
void print_all();
int random_buur_vector(const vector<int>& opties);
void remove_from_safe(const int& x);
void end_game(const string& x);
void check_route_last();
bool check_spel_end();
void cpu_driver();

#endif /* wumpus_hpp */