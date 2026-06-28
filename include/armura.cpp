//
// Created by andre on 5/10/2026.
//
#include "armura.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "exceptii.h"
#include <stdexcept>
using namespace std;
//int Armura::numararmuri=0; //identic ca la gladiator, nu e nicio diferenta
Armura::Armura():obiecti(){
        cout<<"construiesc componenta armura: armura random de la 0\n";
        const char* piscina[4]={"zici ca esti din filmele matrix","armura tigaile de la mamaie" , "caloriferu","caroserie de matiz"};
        int barbut=rand()%4;
        //this->nume=new char[strlen(piscina[barbut])+1];
        //strcpy(this->nume,piscina[barbut]); //evitam shallow copy
        this->nume=piscina[barbut];
        char tipuri_posibile[2]={'U','G'}; //facem randomizer pt ce armura are
        this->tip=tipuri_posibile[rand()%2];
        if (this->tip=='G'){ //grea
            this->protectie=rand()%10+20;
            this->greutate=20.7f+(rand()%3);}
        else if (this->tip=='U'){//usoara
            this->protectie=rand()%10+10;
            this->greutate=10.5f+(rand()%3);}}
Armura::~Armura()noexcept{
    cout<<"distrug componenta armura \n";}
std::string Armura::toString() const{
    return "Armura id: "+std::to_string(getId())+"Nume: "+nume+"\nTip: "+std::string(1,tip)+"Protection: "+std::to_string(protectie)+"Greutate"+std::to_string(greutate)+" kg";}
//if (this->nume!=NULL){
//    delete[] this->nume;}
Armura::Armura(const std::string&P_nume,char P_tip,int P_protectie,float P_greutate):obiecti(){
    cout<<"construiesc componenta armura: armura cu date foarte specifice\n";
    //this->nume=new char[strlen(P_nume)+1];
    //strcpy(this->nume,P_nume); //evita salau copi
    this->nume=P_nume;
    this->tip=P_tip;
    this->protectie=P_protectie;
    this->greutate=P_greutate;}
Armura::Armura(const std::string& P_nume,char P_tip):obiecti(){
    cout<<"construiesc componenta armura: armura cu date foarte specifice\n";
    //this->nume=new char[strlen(P_nume) + 1];
    //strcpy(this->nume,P_nume);
    this->nume=P_nume;
    this->tip=P_tip;
    if (this->tip=='G'){ //grea
        this->protectie=rand()%10+20;
        this->greutate=20.7f+(rand()%3);}
    else if (this->tip=='U'){//usoara
        this->protectie=rand()%10+10;
        this->greutate=10.5f+(rand()%3);}}
//Armura::Armura(const Armura& altul):id(++numararmuri){ //asta tine cont de armele noi create, e constructoru de clone (trebuie sa aibe o baza care exista deja)
 //   cout<<"construiesc componenta armura: face o clona curata\n";
    //this->nume=new char[strlen(altul.nume)+1];
    //strcpy(this->nume,altul.nume);
   // this->nume=altul.nume;
    //this->tip=altul.tip;
 //   this->protectie=altul.protectie;
  //  this->greutate=altul.greutate;}
//Armura& Armura::operator=(const Armura& altul){ //ciordeala de arme
  //  if (this!=&altul){ //safety reasons sa nu fie acelasi nume
        //if (this->nume!=NULL){ //eliberare de memorie
          //  delete[] this->nume;}
          //this->nume=new char[strlen(altul.nume)+1]; //deep copy la nume ca e const
        //strcpy(this->nume,altul.nume);
    //    this->nume=altul.nume;
     //   this->tip=altul.tip;
    //    this->protectie=altul.protectie;
    //    this->greutate=altul.greutate;} //doar copiem atributele noi
  //  return *this;} //ewwwww
//////////////////////////// ma ia ameteala fara asta sorry
std::ostream& operator<<(std::ostream& out,const Armura& a){
    //out<<"Armura; ID: "<<a.id<<"Nume: "<<a.nume;
   // out<<"\nTip: "<<a.tip<<"Protection: "<<a.protectie<<"Greutate: "<<a.greutate<<" kg";
    out<<a.toString();return out;}
std::istream& operator>>(std::istream& in,Armura& a){
    //char gunoi[250]; //te rog io nu tasta mai mult de 250 de caractere aici te implor
    std::string gunoi;
    in>>ws>>gunoi;
    char b_tip;
    int b_prot;
    float b_greutt;
    if (!(in>>b_tip>>b_prot>>b_greutt)) {
        in.clear();
        in.ignore(10000,'\n');
        throw errmeniu("te implor asa mult sa nu ma mai bagi in erori");}
    a.nume=gunoi;
    //if (a.nume!=NULL){ //sa nu lase gol
     //   delete[] a.nume;}
   // a.nume=new char[strlen(gunoi)+1]; //the usual
   // strcpy(a.nume,gunoi);
    //in>>a.tip>>a.protectie>>a.greutate; redundant
    a.setTip(b_tip);
    a.setProtectie(b_prot);
    a.setGreutate(b_greutt);
    return in;}
int Armura::operator[](int index) const {
    //te prinzi ce face, e usoara, ia atributele
    if(index==0)return this->protectie;
    if(index==1)return (int)this->greutate;
    //throw std::out_of_range("0 pt protectie si 1 pt grreutate nu-i asa greu am incredere ca poti \n");} iarasi e outdated
    throw aigrjlaindex(index);}
Armura& Armura::operator++(){ //macar asta a fost usoara
    this->protectie += 5;
    return *this;} // :ccc
Armura Armura::operator+(int armor_bonus)const {
    return Armura(this->nume,this->tip,this->protectie+armor_bonus,this->greutate);} //sincer nu functioneaza f bine, nefiind cu Arma& nu se salveaza, e doar pentru urmatorul atac, si atat, dar e greu de implementat in punctul asta o functie care il lasa pentru tot restul rundei
Armura operator+(int armor_bonus,const Armura& a){ //comutativitate, functia prieten
    return a+armor_bonus;}
bool Armura::operator==(const Armura& alta)const{ //operatorii de comparatie,asta e de egalitate
    return this->protectie==alta.protectie;}
bool Armura::operator<(const Armura& alta) const{ //asta e de mai mic
    return this->protectie<alta.protectie;}