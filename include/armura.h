//
// Created by andre on 5/10/2026.
//

#ifndef UNTITLED1_ARMURA_H
#define UNTITLED1_ARMURA_H
#include <iostream>
#include<string>
#include "iobject.h"
using namespace std;

 //PENTRU COMENTARIILE LEGATE DE CE AM STERS CE AM STERG SI MODIFICAT CE AM MODIFICAT, CLASA ASTA E APROAPE IDENTICA CU CLASA ARMA, UNDE AM EXPLICAT SCHIMBARILE, SE APLICA SI PENTRU FISIERUL ASTA SI PENTRU FISIERUL .CPP
class Armura:public obiecti{  ///MULTE ADNOTATII N-AU FOST SCHIMBATE DE LA ARMA, N-AVEAM DE CE CA E ACELASI CONCEPT
private:
    //const int id;
    std::string nume;
    char tip; // Usoara, Grea
    int protectie;
    float greutate;
    //static int numararmuri;
public:
    Armura(); //constructor principal
    ~Armura() noexcept; //destructor principal
    Armura(const std::string& P_nume,char P_tip,int P_protectie,float P_greutate); // constructor shaorma cu de toate
    Armura(const std::string& P_nume,char P_tip); //constructor shaorma cu vita, cartofi si usturoi
    std::string toString()const override;
    Armura(const Armura& altul)=default; // de data asta te pastrez bebe
    const std::string& getNume()const{return nume;} //se poate citi, dar nu modifica, read-only
    char getTip()const{return tip;} //returneaza ce tip de armura e
    int getProtectie() const{return protectie;} //returneaza damageu
    float getGreutate()const{return greutate;} //ghici ce returneaza
    int getId()const noexcept{return this->getid();} //nota 10 daca te prinzi ce afiseaza
    void setTip(char P_tip){this->tip=P_tip;} //setter de schimbarea tipului armurii (sincer n-are niciun folos, dar am nevoie pt cerinta) incapsulare
    void setProtectie(int P_protectie){if(P_protectie>0){ //asta e folositor, daca fac chestii gen upgradeuri de arma,incapsulare
        this->protectie=P_protectie;}}
    void setGreutate(float P_greutate){ //schimba greuattea, de asemenea, bun daca fac upgradeuri, si e si errorproof, mai e si incapsulare
        if (P_greutate>0){this->greutate=P_greutate;}}

    Armura& operator=(const Armura& altul)=default; //te pastrez si pe tine bebe nu te mai scap//iara ma iara operatori de intrare iesire //o sa mearga la un fel de looting, gen sabia mea=sabie mort
    friend std::ostream& operator<<(std::ostream& out,const Armura& a); //out, absolut toate proprietatile
    friend std::istream& operator>>(std::istream& in,Armura& a); //in, maestru fierar (practic cheating, arma cu 9999 damage si 0 weight)
    //experimental, sa fie macar putin diferita de arma
    int bigabsorbtion(int damage_primit)const{
        int damage_ramas=damage_primit-this->protectie;
        if (damage_ramas<0){
            return rand()%3+1;} //tre sa isi ia macar putin damage
        return damage_ramas;}
    //
    int operator[](int i)const;//indexu e gen al catelea atribut al armei
    Armura& operator++(); //momentan nu e implementat, va veni si asta, dar cand o sa am un currency primit dupa lupte voi putea upgrada arme cu asta
    Armura operator+(int armor_bonus)const; //ig potiuni pentru buffuri?
    friend Armura operator+(int armor_bonus,const Armura&a); //ai vrut comutativitate la 5
    int operator-(int folosire)const{return this->protectie-folosire; }
    bool operator==(const Armura& alta) const; //comparare de arme
    bool operator<(const Armura& alta) const;}; //tot comparare

#endif //UNTITLED1_AMURA_H