///SPER SA FIE VARIANTA OK SA SE FI COPIAT CORECT IN FISIERUL ASTA, CODUL RULA PERFECT PE CLION

#include <iostream>
#include <cstring>
#include <cstdlib> //randomizerul
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <optional>//pt sfml
#include <utility> //tot pt sfml si harta
#include "include/arma.h"
#include "include/armura.h"
#include "include/harta_map.h"
#include "include/arena.h"
#include "include/personajesicaractere.h"
#include "include/meniu.h"
using namespace std;
//insane changes aici, facem harta


//under construction santier

///PAUZA
///Trecem la clasa 3, Armura, o facem identic cu Arma (neironic dau copy paste la cod, e identic)
// Aici avem clasa abstracta deoarece este formata doar din functii pur virtuale, iar ea nu poate fi instantiata direct cu o comanda de genu Personaj x, aia doar ar da eroare











///PAUZA
///Trecem la clasa 2, arma, o facem identic cu gladiator   //le-am mutat pe amandoua sus



///PAUZA
///Oficial primele 3 clase sunt gata, urmeaza a 4a si ultima, arena

///Fieraria pentru a actiona toate functiile armelor si armurilor


///menu copiat de la profu


//


//
int main(){
    srand(time(NULL));
    Arena arena_activa;
    do{Menu::showMenu(arena_activa);}
    while(Menu::getoptiune()!=0);
    Gladiator::emptygladiator();
    return 0;}