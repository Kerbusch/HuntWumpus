#ifndef cpu_hpp
#define cpu_hpp

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

#endif /* cpu_hpp */