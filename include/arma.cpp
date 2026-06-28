//
// Created by andre on 5/10/2026.
//

#include "arma.h"
//#include <cstring> inlocuita de ceva mai nou
#include <cstdlib>
using namespace std;
#include "exceptii.h"
#include <stdexcept>
//int Arma::numararme=0; //identic ca la gladiator, nu e nicio diferenta
Arma::Arma():obiecti(){
        cout<<"Construiesc componenta arma: e random, de la 0...\n";
        const char* piscina[6]={"Cutitul macelarului","Sabia lui Zorro" , "Taietor de capete","Nicu de la Cazanesti" , "Batator de carne","Daniel Buzdugan"};
        int barbut=rand()%6;
        //this->nume=new char[strlen(piscina[barbut])+1];
        //strcpy(this->nume,piscina[barbut]); //evitam shallow copy
        //nu mai e nevoie de astea 2 ca le face automat stdu
        this->nume=piscina[barbut];
        char tipuri_posibile[3]={'S','T','B'}; //facem randomizer pt ce arma are
        this->tip=tipuri_posibile[rand()%3];
        if (this->tip=='B'){ //buzdugan
        this->damage=rand()%10+20;
        this->greutate=5.5f+(rand()%3);}
    else if (this->tip=='T'){//topor
        this->damage=rand()%10+15;
        this->greutate=3.5f+(rand()%3);}
    else  //sabie
        {this->damage=rand()%10+5;
        this->greutate=1.5f+(rand()%3);}}
Arma::~Arma()noexcept{
    //modificari aici pentru a fi in concordanta cu std
    cout<<"distrug componenta arma: \n";}
std::string Arma::toString()const{
    return "Arma, cu id: "+std::to_string(getid())+" Nume: "+nume+"\nTip: "+std::string(1,tip)+" Dmg: "+std::to_string(damage)+" greutate: "+std::to_string(greutate)+" kg";}
//if (this->nume !=NULL){
  //  delete[] this->nume;} nu mai avem nevoie de stergere manuala
Arma::Arma(const std::string& P_nume,char P_tip,int P_damage,float P_greutate):obiecti(){
    cout<<"construiesc componenta arma: e cu date foarte specifice...\n";
    //this->nume=new char[strlen(P_nume)+1];
    // facem atribuire directa strcpy(this->nume, P_nume); //evita salau copi
    this->nume=P_nume;
    this->tip=P_tip;
    this->damage=P_damage;
    this->greutate=P_greutate;}
Arma::Arma(const std::string& P_nume,char P_tip):obiecti(){
    cout<<"construiesc componenta arma: e cu date foarte specifice...\n";
    //this->nume=new char[strlen(P_nume) + 1];
    //strcpy(this->nume,P_nume);
    this->nume=P_nume;
    this->tip=P_tip;
    if (this->tip=='B'){ //buzdugan
        this->damage=rand()%10+20;
        this->greutate=5.5f+(rand()%3);}
    else if (this->tip=='T'){//topor
        this->damage=rand()%10+15;
        this->greutate=3.5f+(rand()%3);}
    else  //sabie
        {this->damage=rand()%10+5;
        this->greutate=1.5f+(rand()%3);}}
//Arma::Arma(const Arma& altul):id(++numararme){ //asta tine cont de armele noi create, e constructoru de clone (trebuie sa aibe o baza care exista deja)
    //cout<<"construiesc componenta arma: face o clona curata\n";
    //this->nume=new char[strlen(altul.nume)+1];
    //strcpy(this->nume,altul.nume);
    //this->nume=altul.nume;
   // this->tip=altul.tip;
    //this->damage=altul.damage;
    //this->greutate=altul.greutate;} //l-am lasat default
//Arma& Arma::operator=(const Arma& altul){ //ciordeala de arme
    //if (this!=&altul){ //safety reasons sa nu fie acelasi nume
       // if (this->nume!=NULL){ //eliberare de memorie
          //  delete[] this->nume;}
        //this->nume=new char[strlen(altul.nume)+1]; //deep copy la nume ca e const
        //strcpy(this->nume,altul.nume);
      //  this->nume=altul.nume;
      //  this->tip=altul.tip;
       // this->damage=altul.damage;
       // this->greutate=altul.greutate;} //doar copiem atributele noi
    //return *this;} //ewwwww // si asta a ramas default
// NEIRONIC TOT CE AM STERS AICI NU MAI AVEM NEVOIE, STD STRING SE OCUPA SINGUR DE STERGERE SI COPIERE, CONSTRUCTORII ASTIA SUNT PUR SI SIMPLU REDUNDANTI //retrag tot, variabila const id imi necesita acesti constructori si operatori (regula celor 3 simplified)
//////////////////////////// ma ia ameteala fara asta sorry
std::ostream& operator<<(std::ostream& out, const Arma& a){
    //out<<"Arma;  ID: "<<a.id<<" Nume: "<<a.nume; //std string stie deja sa lucreze cu operatoru asta
    //out<<"\nTip: "<<a.tip<<" Dmg: "<<a.damage<<" Greutate: "<<a.greutate<<" kg";
    out<<a.toString();
    return out;}
istream& operator>>(istream& in,Arma& a){ //la fel si cu asta
   // char gunoi[250]; //te rog io nu tasta mai mult de 250 de caractere aici te implor
    string temp; //citirea se face intr-un string local si temporar
    char b_tip;
    int b_dmg;
    float b_greutt;
    in>>ws>>temp;
    //if (a.nume!=NULL){ //sa nu lase gol
    //    delete[] a.nume;} nu mai e nevoie de asta, doar trebuie atribuita valoarea lui
    //a.nume=new char[strlen(gunoi)+1]; //the usual
    if (!(in>>b_tip>>b_dmg>>b_greutt)){
        in.clear();
        in.ignore(10000,'\n');
        throw errmeniu("ce faci ma nene ca imi da crash de fiecare data cand scrii ceva, bine ca e programarea preventiva daca tu nu");}
    a.nume=temp;
    a.setTip(b_tip);
    a.setDamage(b_dmg);
    a.setGreutate(b_greutt);
    //strcpy(a.nume,gunoi); 0 need
    //in>>a.tip>>a.damage>>a.greutate;
    return in;}
int Arma::operator[](int index) const {
    //te prinzi ce face, e usoara, ia atributele
    if(index==0)return this->damage;
    if(index==1)return (int)this->greutate;
    //throw std::out_of_range(" 0 damage sau 1 greutate, chiar nu-i mai greu de atat");} l-am inlocuit
    throw aigrjlaindex(index);}
Arma& Arma::operator++(){ //macar asta a fost usoara
    this->damage += 5;
    return *this;} // :ccc
Arma Arma::operator+(int dmg_bonus)const{
    return Arma(this->nume,this->tip,this->damage+dmg_bonus,this->greutate);} //sincer nu functioneaza f bine, nefiind cu Arma& nu se salveaza, e doar pentru urmatorul atac, si atat, dar e greu de implementat in punctul asta o functie care il lasa pentru tot restul rundei
Arma operator+(int dmg_bonus,const Arma&a){
    return a+dmg_bonus;}
//int operator+(int dmg_bonus,const Arma& a){ //comutativitate, functia prieten
//    return a.damage+dmg_bonus;}
bool Arma::operator==(const Arma& alta)const{ //operatorii de comparatie,asta e de egalitate
    return this->damage==alta.damage;}
bool Arma::operator<(const Arma& alta) const{ //asta e de mai mic
    return this->damage<alta.damage;}
