//
// Created by andre on 5/10/2026.
//

#ifndef UNTITLED1_ARMA_H
#define UNTITLED1_ARMA_H
#include <iostream>
#include<string> //pt std::string
#include "iobject.h"
using namespace std;

class Arma:public obiecti{
private:
    //const int id;
    //char* nume=NULL; s-a dus acum cu proiectu 3
    std::string nume; //deci toata idea cu std e ca daca nu lucram cu variabile cu pointeri sau dastea crude de nu poti pune mana pe ele, compilatorul are deja destructori automati care sa se ocupe de stergerea corecta a lor, si nu exista niciun risc de mem leak sau buffer overflow nici macar la copiere
    char tip; // Sabie,Topor,Buzdugan
    int damage;
    float greutate;
    //static int numararme;
public:
    Arma();
    ~Arma() noexcept; //noexcept e garantia ca destructoru nu va arunca exceptii inafara destructorului, sunt tinute inauntru, pentru a preveni double fault
    Arma(const std::string& P_nume,char P_tip,int P_damage,float P_greutate);
    Arma(const std::string& P_nume,char P_tip);
    std::string toString() const override;
    Arma(const Arma& altul)=default; //nu mai avem nevoie de tine, nu mai avem pointeri alocati dinamic Arma // ASA AM CREZUT AM NEVOIE DE TINE PT ID //nu mai am nev lol
    const std::string& getNume()const{return nume;} //se poate citi, dar nu modifica, read-only
    char getTip()const{return tip;} //returneaza ce tip de arma e
    int getDamage() const{return damage;} //returneaza damageu
    float getGreutate()const{return greutate;} //ghici ce returneaza
    int getId()const noexcept{return this->getid();} //nota 10 daca te prinzi ce afiseaza
    void setTip(char P_tip){this->tip=P_tip;} //setter de schimbarea tipului armei (sincer n-are niciun folos, dar am nevoie pt cerinta) incapsulare
    void setDamage(int P_damage){if(P_damage>0){ //asta e folositor, daca fac chestii gen upgradeuri de arma,incapsulare
        this->damage=P_damage;}}
    void setGreutate(float P_greutate){ //schimba greuattea, de asemenea, bun daca fac upgradeuri, si e si errorproof, mai e si incapsulare
        if (P_greutate>0){
            this->greutate=P_greutate;}}

   //nici de tine nu mai avem nevoie, regula celor 3 e simplificata acum, asta ar fi cod redunant, stie std::string sa se ocupe de copiere Arma& operator=(const Arma& altul); //iara ma iara operatori de intrare iesire //o sa mearga la un fel de looting, gen sabia mea=sabie mort
    Arma& operator=(const Arma& altul)=default; //iarta-ma am nevoie mare de tine imi da crash de la const id fara tine
    friend std::ostream& operator<<(std::ostream& out,const Arma& a); //out, absolut toate proprietatile
    friend std::istream& operator>>(std::istream& in,Arma& a); //in, maestru fierar (practic cheating, arma cu 9999 damage si 0 weight)

    int lovituraCritica()const{ //in cazu in care cer o critica
        return this->damage*2;}
    int operator[](int i) const;//indexu e gen al catelea atribut al armei
    Arma& operator++(); //momentan nu e implementat, va veni si asta, dar cand o sa am un currency primit dupa lupte voi putea upgrada arme cu asta
    Arma operator+(int dmg_bonus)const; //ig potiuni pentru buffuri?
    friend Arma operator+(int dmg_bonus,const Arma&a); //ai vrut comutativitate la 5
    int operator-(int stricare)const{return this->damage-stricare;}
    bool operator==(const Arma& alta) const; //comparare de arme
    bool operator<(const Arma& alta) const;}; //tot comparare

#endif //UNTITLED1_ARMA_H