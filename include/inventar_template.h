//
// Created by andre on 5/19/2026.
//

#ifndef UNTITLED1_INVENTAR_TEMPLATE_H
#define UNTITLED1_INVENTAR_TEMPLATE_H
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "arma.h"
using namespace std;
template<typename T,int spatiu_max>
class gheozdan{
private:
    T elemente[spatiu_max];
    int dimcurenta;
public:
    gheozdan():dimcurenta(0){}
    void baga_bani(const T& obiect){
        //aici fac exceptiile standard
        if(dimcurenta>=spatiu_max) {
            throw overflow_error("ma baiatule nu vezi ca e plin");} //overflow error
            elemente[dimcurenta++]=obiect;
            cout<<"ai indesat obiectu in locul"<<dimcurenta-1<<".\n";}
        void aratagheozdan()const{
            if(dimcurenta==0){
                cout<<"a iesit o musculita da altceva nu vezi in ghiozdan\n";return;}
            cout<<" ocupi momentan"<<dimcurenta<<"/"<<spatiu_max<<"\n";
            for(int i=0;i<dimcurenta;++i){
                cout<<" in locul "<<elemente[i]<<"\n";}}
        int getmarime()const{return dimcurenta;}
        T getelement(int idx)const{return elemente[idx];}

//template in clasa template ia de aici
    template <typename U,int altcv>
    void furadingheozdane(const gheozdan<U,altcv>& altul){
        cout<<"\n furi marfa ilegala dintr-un ghiozdan de l-ai furat de la un baiat de 12 ani pe bicicleta\n";
        int trbcopiat=min(spatiu_max,altul.getmarime());
        for (int i=0;i<trbcopiat;++i){
            this->elemente[i]=altul.getelement(i);}
        this->dimcurenta=trbcopiat;
        cout<<"ai bagat in propriul sac"<<trbcopiat<<" elemente!\n";}};

//fac aici un money counter, care doar tb sa adauge la o suma, n-am nevoie sa fac locuri, ci doar un upper limit
template <int spatiu_max>
class gheozdan<int,spatiu_max>{
private:
    int kosoni;
    int limitakosoni;
public:
    gheozdan():kosoni(0),limitakosoni(spatiu_max*2000){}
    void baga_bani(int maimultikosoni){
        if(kosoni+maimultikosoni>limitakosoni){
            throw overflow_error("trg nu mai baga deja ai gen 300kg de aur dupa tn");}
        kosoni+=maimultikosoni;
        cout<<"a venit puya si a bagat "<<maimultikosoni<<" kosoni furati de la nevastasa\n";}
    void aratagheozdan()const{
        cout<<"\n monede dacice "<<kosoni<<"/"<<limitakosoni<<"\n";}};
//
template<typename T>

int cautasiveigasi(const vector<T>& colectie,const T&decautat) {
    for(size_t i=0;i<colectie.size();++i){ //nu merge cu int c apoate fi si negativ, tb size_t
        if(colectie[i]==decautat){
            return static_cast<int>(i);}}return -1;}
template <typename T>
void danitelupgrade(T&obiectJoc){
    cout<<"\n cum arata inainte \n"<<obiectJoc<<"\n";++obiectJoc;
    cout<<" cum arata acum \n"<<obiectJoc<<"\n";}
template<>
inline void danitelupgrade<Arma>(Arma& obiectJoc){
    cout<<"\n *se upgradeaza, cum arata inainte: \n"<<obiectJoc<<"\n";
    ++obiectJoc;
    cout<<" cum arata acum: \n"<<obiectJoc<<"\n";}
#endif //UNTITLED1_INVENTAR_TEMPLATE_H