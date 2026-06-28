//
// Created by andre on 5/10/2026.
//

#ifndef UNTITLED1_ARENA_H
#define UNTITLED1_ARENA_H
#include "exceptii.h"
#include<string>
#include<map>
#include<list>
#include <iostream>
#include <stdexcept>
#include "iobject.h"
using namespace std;
class Arena:public obiecti{
private:
    //const int id;
    std::string nume;
    int pret;
    long long premiu;
    int locuri,incasari;
    //static int numar_arene; //trebuie neaparat si aici ca sa tinem cont de id
    std::list<std::string>istoric_evenimente; //il folosesc pentru ca ma lasa sa inserez si sa sterg elemente la capete in complexitate O(1), iar la adaugare de evnimente este optim acest lucru
    std::map<std::string,int>bilete; //asta ma ajuta mult pentru ca face asocieri cheie-valoare, iar cand vreau sa ma joc cu biletele el imi permite sa gasesc un spectator dupa nume in O(logN)
public:
    Arena();
    Arena(const std::string& P_nume,int P_pret,long long P_premiu,int P_locuri);
    Arena(const Arena& altul)=default; //constructor de copiere (la o arena deja existenta)
    ~Arena()noexcept;
    Arena(const std::string& P_nume);//constructor cu un parametru
    Arena& operator=(const Arena& altul)=default;
    friend std::ostream& operator<<(std::ostream& out,const Arena& a);
    friend std::istream& operator>>(std::istream& in,Arena& a);
    std::string toString()const override;
    const std::string&getNume()const{return nume;}
    int getPret()const{return pret;}
    long long getPremiu()const{return premiu;}
    int getLocuri()const{return locuri;}
    int getId()const{return this->getid();}

    //void setPret(int P_pret){if(P_pret>=0)this->pret=P_pret;}
    //void setPremiu(long long P_premiu){if(P_premiu>=0)this->premiu=P_premiu;} punem throw
    void setPret(int P_pret){
        if(P_pret<0) throw ceerr(P_pret,"Pret Bilet");
        this->pret=P_pret;}
    void setPremiu(long long P_premiu){
        if(P_premiu<0)throw ceerr((int)P_premiu,"Premiu");
        this->premiu=P_premiu;}
    void setLocuri(int P_locuri){if(P_locuri<=0){throw ceerr(P_locuri," nr locuri in arena");}this->locuri=P_locuri;}
    long long calculeazaProfit()const{
        return(long long)this->pret*this->locuri;}
    void vindebilete(const std::string&cumparator,int cantitate);
    void adaugaeveniment(const std::string&ceeveniment);
    void statsuri()const;
    long long operator[](int i)const;
    Arena& operator++();
    long long operator+(long long bonus_premiu)const;
    friend long long operator+(long long bonus_premiu,const Arena& a);
    long long operator-(long long anaf) const{return this->premiu-anaf;}
    bool operator==(const Arena& alta)const;
    bool operator<(const Arena& alta)const;};
void antreprenoriat_arena(Arena& arena_curenta);

#endif //UNTITLED1_ARENA_H