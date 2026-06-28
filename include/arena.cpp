//
// Created by andre on 5/10/2026.
//

#include "arena.h"
#include <cstring>
#include <cstdlib>
#include "exceptii.h"
#include <iomanip>
using namespace std;
//int Arena::numar_arene = 0;
Arena::Arena():obiecti(),incasari(0){
    cout<<"construiesc arena (asta n-are nmk special de data asta";
    const char* piscina[2]={"In fata la Maxbet", "Socului la 3 dimineata"};
    int barbut=rand()%2;
    //this->nume=new char[strlen(piscina[barbut])+1];
    //    strcpy(this->nume,piscina[barbut]); //evitam shallow copy
    this->pret=15;
    this->nume=piscina[barbut];
    this->premiu=5000;
    this->locuri=500;}
Arena::Arena(const std::string& P_nume,int P_pret,long long P_premiu,int P_locuri):obiecti(),incasari(0){
    cout<<"construiesc arena (asta n-are nmk special de data asta";
    //this->nume=new char[strlen(P_nume)+1];
    //strcpy(this->nume,P_nume);
    this->nume=P_nume;
    this->setPret(P_pret);
    this->setPremiu(P_premiu);
    this->setLocuri(P_locuri);}
//Arena::Arena(const Arena&altul):obiecti(){
   // cout<<"construiesc arena (asta n-are nmk special de data asta";
    //this->nume=new char[strlen(altul.nume)+1];
    //    strcpy(this->nume,altul.nume);
   // this->nume=altul.nume;
   // this->pret=altul.pret;
   // this->premiu=altul.premiu;
   // this->locuri=altul.locuri;
  //  this->incasari=altul.incasari;
   // this->istoric_evenimente=altul.istoric_evenimente;
   // this->bilete=altul.bilete;}
Arena::Arena(const std::string& P_nume):obiecti(),incasari(0){
    cout<<"construiesc arena (asta n-are nmk special de data asta";
    //this->nume=new char[strlen(P_nume)+1];
    //strcpy(this->nume,P_nume);
    this->nume=P_nume;
    this->pret=20;
    this->premiu=1000;
    this->locuri=100;}
Arena::~Arena()noexcept{
    cout<<"si aici distrug arena";}
    //if(this->nume!=NULL)
    //    delete[] this->nume;}
//Arena& Arena::operator=(const Arena&altul){
  //  if(this!=&altul){
        //if(this->nume!=NULL){
        //    delete[] this->nume; }
       // this->nume=new char[strlen(altul.nume)+1];
        //strcpy(this->nume,altul.nume);
     //   this->nume=altul.nume;
     //   this->pret=altul.pret;
     //   this->premiu=altul.premiu;
     //   this->locuri=altul.locuri;
     //   this->incasari=altul.incasari;
     //   this->istoric_evenimente=altul.istoric_evenimente;
      //  this->bilete=altul.bilete;}return*this;}
std::string Arena::toString() const {
    return "Arena ID: "+std::to_string(getid())+" Nume: "+nume +
           "\nPret Bilet: "+std::to_string(pret)+" lei Locuri: "+std::to_string(locuri) +
           "\nPremiul cel mare: "+std::to_string(premiu)+" lei";}
ostream& operator<<(ostream& out,const Arena& a) {
    // out<<"Arena; ID: "<<a.id<<"Nume: "<<a.nume;
    // out<<"\nPret Bilet: "<<a.pret<<" lei Locuri: "<<a.locuri;
    // out<<"\n Premiul cel mare: "<<a.premiu<<" lei";return out;}
    out<<a.toString();
    return out;}
istream& operator>>(istream& in, Arena& a){
    //char gunoi[250];
    std::string gunoi;
    int b_pret,b_locuri;
    long long b_premiu;
    in>>ws;
    in>>gunoi;
    //if (a.nume!=NULL){
    //    delete[] a.nume;}
    //a.nume=new char[strlen(gunoi)+1];
    //strcpy(a.nume,gunoi);
   if (!(in>>b_pret>>b_premiu>>b_locuri)) {
       in.clear();
       in.ignore(10000, '\n');
       throw errmeniu("n-ai bagat corect ve voiam la chestiile astea, te implor umil sa fii mai atent");}
    //in>>b_pret>>b_premiu>>b_locuri; redundant
    a.nume=gunoi;
    a.setPret(b_pret);a.setPremiu(b_premiu);a.setLocuri(b_locuri);
    return in;}
void Arena::adaugaeveniment(const std::string&eveniment){
    istoric_evenimente.push_back(eveniment);}//O(1), atat are list push back
void Arena::vindebilete(const std::string& cumparator,int cantitate){ //O(logN) datorita lu map insert
    if (cantitate>this->locuri){
        throw std::overflow_error("n-ai capacitete, tu vrei "+std::to_string(cantitate)+" bilete, dar mai e doar "+std::to_string(this->locuri)+" locuri");}
    auto[salut,succes]=bilete.insert({cumparator,cantitate});
    if(!succes){salut->second+=cantitate;}
    this->locuri-=cantitate;
    this->incasari+=(cantitate*this->pret);}
void Arena::statsuri()const{
    cout<<"\n astea sunt statsurile arenei "<<this->nume<<"\n"<<this->locuri<<"\n"<<this->incasari<<"\n"<<"evenimente recente: \n";
    if (istoric_evenimente.empty())cout<<" n-ai evenimente varule\n";
    for (const auto& ev:istoric_evenimente){
        cout<<"lol"<<ev<<"\n";}
    cout<<"\nuite cate bilete ai vandut: \n";
    if (bilete.empty())cout<<" na venit nimeni sati ia bilete\n";
    for (const auto&[var,cantitate]:bilete){
        cout<<var<<" a lot "<<cantitate<<" bilete \n";}}
long long Arena::operator[](int i)const{ //sa cauti proprietatea arenei dupa ce i pui in "vector"
    if(i==0)return this->premiu;
    if(i==1)return(long long)this->locuri;throw std::out_of_range("nu ai bagat indexu bine");}
Arena& Arena::operator++(){
    this->locuri+=100;//cum ar veni upgradam arena la nr de locuri
    this->adaugaeveniment("arena primeste locuri");
    return *this;}

long long Arena::operator+(long long bonus_premiu)const{
    return this->premiu+bonus_premiu;}
long long operator+(long long bonus_premiu,const Arena& a) {
    return a.premiu+bonus_premiu;} //e comutativa

bool Arena::operator==(const Arena& alta)const{ //comparare de arene
    return this->locuri==alta.locuri;}
bool Arena::operator<(const Arena& alta)const{ //tot comparare, basically useless
    return this->locuri<alta.locuri;}
///antreprenoriatu arenei
void antreprenoriat_arena(Arena& arena_curenta){
    int tast1;
    do{
        cout<<"\n=== Gladiatori_HQ ===\n";
        cout<<"\nArena ta e asta:\n"<<arena_curenta;
        cout<<"\n1.)Renoveaza de la zero\n";
        cout<<"\n2.)Mai pune niste tabureti prin arena\n";
        cout<<"\n3.)Calculeaza profitu\n";
        cout<<"\n4.)Mergi la intalnirea cu sponsorii\n";
        cout<<"\n5.)Mergi la auditia ANAF\n";
        cout<<"\n6.)Cauta in dosare dupa statistici\n";
        cout<<"\n7.)Compara cu alte arene\n";
        cout<<"\n8.)Te-ai plictisit de tirania lui Becali si vrei sa o iei de la 0\n";
        cout<<"\n9.)Vezi carei treaba cu casa de bilete\n";
        cout<<"\n10.)Te uiti si la ce vrea anafu sai arati?\n";
        cout<<"\n0.)Intoarce-te la gladiatori\n> ";
        if(!(cin>>tast1)){
            cin.clear();
            cin.ignore(10000,'\n');
            cout<<"\nIntrodu un lucru valid.\n";continue;}
        switch(tast1){
            case 1:{cout<<"\nBaga datele noi: Nume(fara_spatii) pret_per_bilet premiu locuri\n>";cin>>arena_curenta;break;}
            case 2:{++arena_curenta;cout<<"\nAi luat taburetii de la mamaie din curte(+100 locuri)\n";break;}
            case 3:{cout<<"\nDaca se umple stadionu, o sa faci: "<<arena_curenta.calculeazaProfit()<<" lei\n";break;}
            case 4:{cout<<"\nLa sedinta era Becali, a zis ca face noua steaua din arena ta\n";cout<<"Cifra de afaceri arata asa"<<arena_curenta+10000LL<<" lei\n";break;}
            case 5:{
                cout<<"\nAi belit-o, e anafu la usa, n-ai nici pe unde sa fugi, trebuie sa platesti taxe din premiu\n";
                cout<<"Premiu ramas: "<<arena_curenta-2000LL<<" lei\n";break;}
            case 6:{
                cout<<"\nTi-a cerut anafu niste informatii precise, le scrii pe masa \n";
                cout<<"Valoarea premiului "<<arena_curenta[0]<<" lei\n";
                cout<<"Numar locuri "<<arena_curenta[1]<<" locuri\n";break;}
            case 7:{
                Arena arena_vaslui("Colosseum_Vaslui",20,8000,600);
                cout<<"\nHai sa ne comparam cu Vasluiu "<<arena_vaslui;
                if (arena_curenta==arena_vaslui){cout<<"E la fel de mare...\n";}
                else if (arena_curenta<arena_vaslui){cout<<"Inchide-ti arena, pana si aia din Vaslui e mai mare...\n";}
                else{cout<<"Se vede ca ti-a facut Becali o vizita, e mare rau arena ta\n";}break;}
            case 8:{
                std::string ferentari;
                cout<<"Ai plecat de la Arena Nationala si te-ai dus in ferentari, ce nume ii pui arenei?\n> ";
                cin>>ferentari;
                if(ferentari.size()<3||ferentari.find("steaua")!=std::string::npos){
                    cout<<"numele pe care lai bagat fie e prea scurt (si te iert) fie ai incercat cuvantul interzis (nu te iert)!\n";break;}
                Arena arena_noua(ferentari);
                arena_curenta=arena_noua; // Suprascriem arena
                //delete[] ferentari;
                cout<<"\nAi dat restart la cariera. Noua ta arena:\n"<<arena_curenta;break;}
            case 9: {
                cout<<"\n baga numele spectatorului intr-un singur cuv";std::string var2;cin>>var2;
                cout<<"cate bilete o loa?";int cantitate;cin>>cantitate;
                try{
                    arena_curenta.vindebilete(var2,cantitate);
                    arena_curenta.adaugaeveniment(var2+" a lot "+std::to_string(cantitate)+ " bilete");
                    cout<<"\n bv ma ai fakut bani\n";}
                catch(const std::overflow_error&e){
                    cout<<"\noopsie "<<e.what()<<"\n";}
                cout<<"\n s-a salvat sa poti sai arati si anafului\n";
                arena_curenta.statsuri();
                break;}
                case 10:{
                    arena_curenta.statsuri();
                    break;}
            case 0:{cout<<"\nAi iesit din HQ\n";break;}
            default:{cout<<"\nTe rog scrie un numar din lista\n";break;}}}while(tast1!=0);}