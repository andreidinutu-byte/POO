//
// Created by andre on 5/10/2026.
//

#ifndef UNTITLED1_PERSONAJESICARACTERE_H
#define UNTITLED1_PERSONAJESICARACTERE_H
#include <iostream>
#include <cstring>
#include "arma.h"
#include "armura.h"
#include "iobject.h"
#include <sstream>
using namespace std;
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <SFML/Graphics.hpp>

class Personaj:public obiecti{
//folosim protected si nu private pentru ca atributele precum nume, hp trebuie sa fie accesibile din interiorul claselor derivate (precum luptator), dar sa nu fie vizibile de catre functia main
protected: //sunt accesibili in derivate astia protected
    std::string nume;
    int hp,x,y;
    bool viusausall;
public:
    Personaj():nume("random"),hp(100),x(0),y(0),viusausall(true){
        //initialiizare a membrilor ewwww
        cout<<"Construiesc baza la personaj...";}
        //this->nume=new char[strlen("random")+1];
        //strcpy(this->nume,"random");}
    Personaj(const std::string& p_nume,int p_hp):hp(p_hp),viusausall(p_hp>0) {
        //constructor cu parametri
        cout<<"Construiesc baza la personaj...";}
        //this->nume=new char[strlen(p_nume)+1];
        //strcpy(this->nume,p_nume);}
    Personaj(const Personaj& altul):nume(altul.nume),hp(altul.hp),x(altul.x),y(altul.y),viusausall(altul.viusausall) {
        cout<<"Copiez baza personaj...";}
        //if (altul.nume!=NULL){
           //this->nume=new char[strlen(altul.nume)+1];
          //  strcpy(this->nume,altul.nume);}else{this->nume = NULL;}}
    virtual ~Personaj() noexcept{//destructor virtual
        cout<<"Distrug baza la personaj...";}
        //if (this->nume!=NULL){
         //   delete[] this->nume;}}//functie pur virtuala pentru domnul Paun => personaj e clasa abstracta
    virtual int gethp() const{return this->hp;}
    int getX() const{return x;} //trebuie cu X mare ca innebunesc daca las getx
    int getY() const{return y;}
    void setX(int nou_x){x=nou_x;}
    void setY(int nou_y){y=nou_y;}
    const std::string& getnume() const{return nume;} //avand nume protected ajuta f mult sa am functia asta in public pentru a folosi std cu functii scurte
    virtual void veziinfo() const{
        cout<<"Nume: "<<this->nume<<" HP: "<<this->hp;}
    virtual void iadamage(int damageluat)=0;
    virtual void miscare(const std::string& directie)=0; //uitasem sa pun referinta aici si iesise mare cacealma
    Personaj& operator=(const Personaj& altul){
        if (this!=&altul){
            //if(this->nume!=NULL){delete[]this->nume;}
           // if (altul.nume!=NULL){
            //    this->nume=new char[strlen(altul.nume)+1];
             //   strcpy(this->nume,altul.nume);}else{this->nume=NULL;}
            this->nume=altul.nume; //stie std sa faca singur deep copy
            this->hp=altul.hp;
            this->x=altul.x;
            this->y=altul.y;
            this->viusausall=altul.viusausall;}return *this;}};
class Sponsor:public Personaj{
private:
    int buget;
public:
    Sponsor(const std::string& s_nume,int s_hp,int s_buget):Personaj(s_nume, s_hp) {
        cout<<"construiesc derivata sponsor, un sponsor direct peste fundatia pusa de personaj";
        this->buget=s_buget;}
    virtual ~Sponsor() noexcept{
        cout<<"distrug sponsor de personaj";
        cout<<"\n"<<this->nume<<" a dat faliment si a plecat acasa...\n";}
    std::string toString()const override{
        return " ID "+std::to_string(getid())+" Sponsor: "+this->nume+" Bani "+std::to_string(this->buget)+" lei";}
    void iadamage(int damageluat) override { //trebuie sa aibe functia asta chiar daca nu se bate
        if(damageluat<0){throw std::invalid_argument("trg nu baga numere negative ca iti dai heal");}
        if (this->buget>=damageluat*100){
            this->buget-=damageluat*100;
            cout<<"\n"<<this->nume<<" a scos teancul si a platit "<<damageluat * 100<<" ca sa scape de lovitura. i-au mai ramas "<<this->buget<<" lei.\n";}else{
                this->hp -= damageluat;
                cout<<"\n"<<this->nume<<" a ramas fara bani si si-a luat "<<damageluat<<" damage fizic, mai are "<<this->hp<<" HP.\n";
                if (this->hp<=0){
                    this->hp=0;
                    this->viusausall=false;
                    cout<<"\n"<<this->nume<<" a fost inmormantat chiar in aceasi zi\n";}}}
    void miscare(const std::string& directie) override{
        Personaj::miscare(directie);
        cout<<"\n"<<this->nume<<" se da jos din Brabus si se plimba arogant spre"<<directie<<"\n";}};

class Luptator:public Personaj{
private:
    int datoriilacamatari;
protected:
    int energie;
public:
    Luptator():Personaj(),datoriilacamatari(rand()%100),energie(100){cout<<"cosntruiesc derivata luptator peste fundatia pusa de personaj";}//constructor implicit
    Luptator(const std::string& p_nume,int p_hp,int p_energie):Personaj(p_nume,p_hp),datoriilacamatari(0),energie(p_energie){cout<<"cosntruiesc derivata luptator peste fundatia pusa de personaj";} //constructor parametri
    Luptator(const Luptator& altul):Personaj(altul),datoriilacamatari(altul.datoriilacamatari),energie(altul.energie){cout<<"Copiez derivata luptator...";}
    virtual ~Luptator() noexcept{cout<<"distrug derivata luptator";}
    virtual void ataca()=0;
    int getdatorii() const{return datoriilacamatari;}
    void setdatorii(int P_datorii) {this->datoriilacamatari=P_datorii;}
    Luptator& operator=(const Luptator& altul){
        if(this!=&altul){
            Personaj::operator=(altul); // Apelează atribuirea din baza de mai sus!
            this->energie=altul.energie;
            this->datoriilacamatari=altul.datoriilacamatari;}return *this;}
    //   void veziinfo() const override{ //override e ca un fel de security check, verifica daca exista deja functia care trebuie inlocuita
    //       Personaj::veziinfo(); //luam veziinfo si ii punem alt nume
    //       //      cout<< " Stamina: "<<this->energie;}                // NU STIU DACA MAI ARE ROST SA BAG ASTA CA MOSTENIRE DE FUNCTIE SAU CUM SE CHEAMA
};

class Gladiator final:public Luptator{ //ierarhia e personaj->luptator->gladiator, cel din urma fiind deja gandit pe subclase in cadrul lui, este in forma sa finala, nu mai am unde sa-l extind. este foarte complex si specific, ar fi o povara sa mostenesc ceva de la el
private:
    //const int id; //asta rezulta ca sunt obligat sa initializez cu : dupa ce fac clasa (se vede mai jos clar)
    std::vector<int> stats; //se potriveste
    char rang;
    float critrate;
   // static int numargladiatori;
    ///
    static std::vector<Personaj*> adunatura; //am rezolvat
   // static Personaj** adunatura; //s-a ajuns aici foarte tarziu, as fi renuntat la static intu ala daca stiam ca fac asta si urmatoarea //in partea a 2a proiectului asta e polimorfismul
    //static int nrrezidenti; nu mai folosesc din cauza lu std
    ///
    Arma arma_assigned;
    Armura armura_assigned;
public:
    Gladiator();
    Gladiator(const std::string& P_nume, char P_rang); //pentru user sa isi faca caracterul (restul statsurilor sunt randomized), shaorma cu carne cartofi si maioneza
    Gladiator (const std::string& P_nume, int P_hp,const std::vector<int>& P_stats, char P_rang, float P_critrate, bool P_viusausall); // constructorul cu toti parametri, pentru "god mode" sau character creator", shaorma cu de toate imo
    Gladiator(const Gladiator& altul);
    ~Gladiator() noexcept; //asa se face destructor????
    friend ostream& operator<<(ostream& out,const Gladiator& g); // le-am luat drept din ala cu student, a trebuit sa pun out si g ca variabile (e mai usor)
    friend istream& operator>>(istream&, Gladiator& g);
    Gladiator& operator=(const Gladiator& altul); //evita shallow copy, legea celor 3 maimute: creezi modifici si stergi

    const std::string& getNume() const{return nume;}//aiurea da la toate astea cu get ai nev de 2 const, imi dadea eroare altfel, krd k unu pt output si altu pt gladiator in sine
    int gethp() const{return hp;}
    bool getded() const{return viusausall;}
    char getrang() const{return rang;}
    std::string toString()const override{
        std::ostringstream ss;
        ss<<"\n   Character Stats    ";
        ss<<"\nID:"<<this->getid()<<"; Name:"<<this->nume;
        ss<<"\nRank:"<<this->rang<<"; HP:"<<this->hp;
        ss<<"\nCritical Chance:"<<this->critrate<<"%";
        if(this->stats.size()>=3){
            ss<<"\nStats:"<<this->stats[0]<<" Str/"<<this->stats[1]<<" Agl/"<<this->stats[2]<<" End";} //e ocazie perfecta de siguranta cu try catch sau cv
        ss<<"\nDead or Alive:"<<(this->viusausall);
        ss<<"\narmat cu: "<<this->arma_assigned.getNume()<<" (Dmg: "<<this->arma_assigned.getDamage()<<")";
        ss<<"\nascuns de: "<<this->armura_assigned.getNume()<<" (Def: "<<this->armura_assigned.getProtectie()<<")";return ss.str();}
    void afisare() const;
    void sethp(int P_hp){  /// iti place incapsularea ma nbnle
        this->hp = P_hp;
        if(this->hp<=0){
            this->viusausall=false;
            this->hp=0;}}
    void beabere(){ //reviveu cu bere, tot incapsulare
        this->hp+=50;
        this->viusausall=true;}
    //aici vin armele grele, supraincarcarea operatorilor (mi-a explicat Domnul Paun <3)
    int operator[](int index) const;
    Gladiator& operator++(); //o sa facem level up din asta
    float operator+(float lvlup_crit) const;
    int operator-(int dmg_lot)const{return this->hp-dmg_lot;}
    friend float operator+(float lvlup,const Gladiator& g); // comutativitate???
    bool operator==(const Gladiator& rezerva) const; //comparare personaje, ajuta la matchmaking cum ar veni
    bool operator<(const Gladiator& rezerva) const; //tot comparare, dar aici pot verifica o chestie daia gen "nu esti destul de puternic pentru a te bate cu barosozaurus"
    /// acum o sa fac crudu aici
    static void creategladiator();
    static void readgladiator();
    static void deletegladiator();
    static void emptygladiator();
    static void traingladiator();
    static void inspectgladiator();
    static void clonegladiator();
    static void taverngladiator();
    static void startarena();
    ///
    ///
    ///
    void setnume(const std::string& numenou){
        this->nume=numenou;}
        //if (numenou!=NULL){
            // legea celor 3 maimuțe
            //if (this->nume!=NULL){
                //delete[] this->nume;}
            //this->nume = new char[strlen(numenou) + 1];
            //strcpy(this->nume, numenou);}}
    ///
    //////
    ///
    ///
    ///
    ///
    void editgladiator() {
        int tast;
        cout<<"\n=== Modificare Gladiator: "<<this->nume<<" ==="<<endl;
        cout<<"1.)Porecla"<<endl;
        cout<<"2.)Schimba HP"<<endl;
        cout<<"3.)Schimba Rang"<<endl;
        cout<<"4.)Schimba Stats(S/A/E)"<<endl;
        cout<<"0.)Renunță"<<endl;
        cout<<"Alege stat-ul: ";
        if(!(cin>>tast)){
            cin.clear();
            cin.ignore(10000, '\n'); return;}
        switch(tast){
            case 1:{
                std::string buffer;
                cout<<"Nume nou: ";cin>>buffer;
                this->setnume(buffer);break;}
            case 2:{
                int hpnou;
                cout<<"HP nou: ";cin>>hpnou;
                this->sethp(hpnou);
                break;}
            case 3:{
                char rangnou;
                cout<<"Rang nou (S/G/P/R): ";cin>>rangnou;
                this->rang=rangnou;break;}
            case 4:{
                cout<<"Introdu noile stats (Str Agl End): ";
                if (this->stats.size()<3) this->stats.resize(3); //e safety measure pentru a ma asigura ca merge vectoru bine
                cin>>this->stats[0]>>this->stats[1]>>this->stats[2];break;} case 0: break;
            default: cout<<"Opțiune invalidă!";}}
    void iadamage(int damageluat) override{
        if(damageluat<0){
            throw std::invalid_argument("trg nu baga numere negative ca iti dai heal");}
        this->hp-=damageluat;
        cout<<"\n"<<this->getNume()<<" a luat "<<damageluat<<" damage \n";
        if (this->hp<=0){
            this->hp=0;
            this->viusausall=false;
            cout<<this->getNume()<<" s-a dus...\n";}}
    void miscare(const std::string& directie) override{
        Personaj::miscare(directie);
        cout<<"\n"<<this->getNume()<<" se duce in directia"<<directie<<"!\n";}
    void ataca() override{
        cout<<" \n"<<this->getNume()<<" da o lovitura cu"<<this->arma_assigned.getNume()<<" si da "<<this->arma_assigned.getDamage()<<" damage!\n";}
    void veziinfo() const override{
        Personaj::veziinfo(); // extinderea unei metode din baza
        cout<<" Rang: "<<this->rang<<" Crit: "<<this->critrate<<"%\n";}};
class Monstru:public Luptator {
private:
    char tipmonstru; //d dragon, l lup, t troll
    int damage;
public:
    Monstru(const std::string& m_nume, int m_hp, char m_tip, int m_dmg):Luptator(m_nume,m_hp,100){
        cout<<"construiesc derivata monstru peste fundatia pusa de luptator";
        this->tipmonstru=m_tip;
        this->damage=m_dmg;}
    std::string toString()const override{
        std::string bblbbbblbltrbyby(1,tipmonstru);
        return" id "+std::to_string(getid())+" Monstru "+this->nume+" HP "+std::to_string(this->hp)+" Tip "+bblbbbblbltrbyby;}
    Monstru():Luptator("insane_spawn",100,100) {
        cout<<"construiesc derivata monstru peste fundatia pusa de luptator";
        const char* piscina[4]={"vampir_insetat","Varcolac","Troll","Al'du'in"}; //pastram charu aici
        int zaru=rand()%4;
        //if(this->nume!=NULL)delete[]this->nume;
        //this->nume=new char[strlen(piscina[zaru])+1];
        //strcpy(this->nume,piscina[zaru]);
        this->nume=piscina[zaru];
        char tipuri[4] = {'V','L','T','D'};
        this->tipmonstru=tipuri[zaru];
        this->damage=rand()%20+5;}
    virtual ~Monstru() noexcept{
        cout<<"distrug derivata monstru";
        cout<<"\n si-a murit "<<this->nume;}
    void ataca() override {
        cout<<"\n"<<this->nume<<"vine spre tine si iti da"<<this->damage<<"damage\n";}
    void iadamage(int damageluat) override{
        if(damageluat<0){
            throw std::invalid_argument("trg nu baga numere negative ca iti dai heal");}
        this->hp-=damageluat;
        cout<<"\nMonstrul "<<this->nume<<" e lovit, o luat "<<damageluat<<" damage. HP actual: "<<this->hp<<"\n";
        if (this->hp<=0){
            this->hp=0;
            this->viusausall=false;
            cout<<"Monstrul a murit!\n";}}
    void miscare(const std::string& directie) override{
        Personaj::miscare(directie);
        cout<<"\n"<<this->nume<<" se muta in directia "<<directie<<"\n";}};


#endif //UNTITLED1_PERSONAJESICARACTERE_H