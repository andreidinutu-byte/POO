//
// Created by andre on 5/10/2026.
//

#include "personajesicaractere.h"
#include "arma.h"
#include "armura.h"
#include "exceptii.h"
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include "harta_map.h"
#include <memory>
#include <SFML/Graphics.hpp>
using namespace std;


void Personaj::miscare(const std::string& directie){ //neironic regele Paun, m-a invatat asta cand aveam nevoie de ea cel mai mult
    if (directie=="W")this->y-=1; //putem trece la string, nu mai tb sa folosim strcmp
    else if (directie=="S")this->y+=1;
    else if (directie=="A")this->x-=1;
    else if (directie=="D")this->x+=1;} //joc de coordonate
//int Gladiator::numargladiatori=0; ///dedeferentiere????????? // nu e am grst //this s-ar putea sa fie solutia
std::vector<Personaj*> Gladiator::adunatura;
//clasa gladiator are date membre directe arma si armura. ele sunt initializate in lista de initializare a constructorului gazdei (adk Gladiator):ordinea va fi vazuta in consola ca mai intai se fac armele si armura, iar mai apoi gladiator
Gladiator::Gladiator():Luptator(),arma_assigned(),armura_assigned() {
    //comanda boss care ii da nr de id. //MAMA CE BATAIE DE CAP MI-A DAT ++ ALA INAINTE, NU MERGE DOAR CU +1, DEVIN TOTI PERVERTICUS
    cout<<"construiesc gazda gladiator\n...";
    const char* piscina[10] = {"Spartu", "Perverticus", "Gunoierium", "Cocalarassen", "Rejele", "Sclavissimo", "TheLegend47", "Arrowtotheknee420", "GigelSpaimaColloseumuluiisimos", "Al-Du-In"};
    int zaru=rand()%10;
    //if(this->nume!=NULL){delete[]this->nume;}
    //this->nume=new char[strlen(piscina[zaru])+1]; //alocare memorie
    //strcpy(this->nume, piscina[zaru]); //e nevoie de asta pt ca altfel se joaca doar cu adresa, nu si cu stringu in sine, eara face salau copi
    this->nume=piscina[zaru];
    this->hp=rand()%50+50;
    this->rang='S';
    this->critrate=15.0f; //f=float
    this->viusausall=true;
    //this->stats=new int[3];
    //this->stats[0]=rand()%10+10; //Str
    // this->stats[1]=rand()%10+10; //Agl
    // this->stats[2]=rand()%10+10; //End
    this->stats={rand()%10+10,rand()%10+10,rand()%10+10};} //asta da smecherie, am facut din constructoru asta de 20 de linii doar vreo 8}
Gladiator::~Gladiator() noexcept{
    //demolisherul sterge doar chestiile facute de mine cu new, adica pointerii practic
    //if (this->nume!=NULL){
    //    delete[] this->nume;} //facut cu new
    // SA VEZI FAZA AICI CA AM FACUT DUBLU DESTRUCTOR SI DADEA CRASH (unu la personaj si altu aici)
    cout<<"distrug gazda gladiator";}
    //if (this->stats!=NULL){ //facut cu un vector de new
        //delete[] this->stats;}}
///Character Creatorul, se introduce nume+rang iar apoi se atribuie automat restu propietatilor
Gladiator::Gladiator(const std::string&P_nume, char P_rang):Luptator(P_nume,50,100),arma_assigned(),armura_assigned(){
    cout<<"construiesc gazda gladiator cu date complexe";
    //if(this->nume!=NULL){delete[]this->nume;}
    //this->nume = new char[strlen(P_nume)+1]; //nu uita de +1 vtm
    //strcpy(this->nume,P_nume);
    this->nume=P_nume;
    this->rang=P_rang; //SE VA ALEGE DINTRE S,G,P,R. momentan nu va influenta cu absolut nimic jocul, deoarece n-am timp sa implementez
    this->hp=50;
    this->critrate=25.0f;
    this->viusausall=true;
    // this->stats=new int[3];
    //this->stats[0]=10;
    //this->stats[1]=10;
    //this->stats[2]=10;}
    this->stats={10,10,10};}
///Constructor cu toti parametrii (nu are un rol inca, maxim boss creator sau cv)
Gladiator::Gladiator(const std::string& P_nume, int P_hp,const std::vector<int>& P_stats, char P_rang, float P_critrate, bool P_viusausall){
    cout<<"construiesc gazda gladiator cu date complexe";
    //if(this->nume!=NULL){delete[]this->nume;}
    //this->nume = new char[strlen(P_nume)+1];
    //strcpy(this->nume,P_nume);
    this->nume=P_nume;
    this->rang=P_rang;
    this->hp=P_hp;
    this->critrate=P_critrate;
    this->viusausall=P_viusausall;
    this->stats=P_stats;}
    //asta cu statsurile o sa fie ciudata
    //this->stats=new int[3]; //standard
    //for (int i=0;i<3;i=i+1){  //parcurgere a vectorului, 0 salau copi
       // this->stats[i]=P_stats[i];} //assignment
       // }
///In cerinta la 2d zice si "constructor de copiere", sper ca asta e ce se doreste, in joc nu cred ca il folosesc???
Gladiator::Gladiator(const Gladiator& OG):Luptator(OG),arma_assigned(OG.arma_assigned),armura_assigned(OG.armura_assigned){
    //deci asta e pt o clona care NU exista deja a unui personaj
    cout<<"clonez gazda gladiator in baza altui gladiator";
    this->rang=OG.rang;
    this->critrate=OG.critrate;
    this->stats=OG.stats;}
    //this->stats=new int[3];
    //for (int i=0;i< 3;i=i+1){ //iarasi for :c
    //    this->stats[i]=OG.stats[i];}}
///2f pt operator de atribuire (ms sync.ro pt info)
Gladiator& Gladiator::operator=(const Gladiator& OG) { //aici ideea e altfel, asta e clonarea a unui personaj pe un personaj care DEJA EXISTA
    if (this!=&OG){//daca pui acelasi nume pe ambele parti a egalului... exploding_cat.gif (am incercat neironic a dat crash codeblocksu)
        Luptator::operator=(OG);
        //if (this->stats!=NULL){delete[] this->stats;}
        //this->stats=new int[3];
        this->stats=OG.stats; //se ocupa singur std de delete si auto assignment ggen foru ala
        //for (int i=0;i<3;i++){ //deja m-am obisnuit
        //    this->stats[i]=OG.stats[i];} //dippy copy
        //this->id=OG.id //nu se face
        this->rang=OG.rang;
        this->critrate=OG.critrate;
        this->arma_assigned=OG.arma_assigned;
        this->armura_assigned=OG.armura_assigned;}
    return* this;//bleurgh
}
/// ce urmeaza acum ma face sa vreau sa ma las de programare
ostream& operator<<(ostream& out, const Gladiator& g) { //ce am scris si in public, in loc de cout poti scrie out, poti scoate oriunde, nu doar pe ecran datele, le poti scrie si in memoria cache daca vrei
    //out<<"\n   Character Stats    ";
    //out<<"\nID:"<<g.id<<"; Name:"<<g.nume;
    //out<<"\nRank:"<<g.rang<<"; HP:"<<g.hp;
   // out<<"\nCritical Chance:"<<g.critrate<<"%";
   // if (g.stats.size()>=3){
   //     out<<"\nStats:"<<g.stats[0]<<" Str/"<<g.stats[1]<<" Agl/"<<g.stats[2]<<" End";} //e ocazie perfecta de siguranta cu try catch sau cv
    //out<<"\nDead or Alive:"<<(g.viusausall);
    //out<<"\narmat cu: "<<g.arma_assigned.getNume()<<" (Dmg: "<<g.arma_assigned.getDamage()<<")";
    //out<<"\nascuns de: "<<g.armura_assigned.getNume()<<" (Def: "<<g.armura_assigned.getProtectie()<<")";
    out<<g.toString();
    return out;}
istream& operator>>(istream& in, Gladiator& g){ //neironic cea mai importanta functie stand-alone, te lasa sa iei sclavu din crackhouse si sa-l denumesti cum vrei tu
    std::string gunoi;
    int b_hp,s0,s1,s2;
    char b_rang;
    float b_crit;
    in>>ws>>gunoi;
    //in>>std::setw(250)>>gunoi;
    //if (g.nume!=NULL){ //chiar daca teoretic o sa fie intotdeauna diferit de null, e bine ca safeguard
    //    delete[] g.nume;}
    //g.nume=new char[strlen(gunoi)+1];
    //strcpy(g.nume,gunoi);
    if (!(in>>b_hp>>b_rang>>b_crit>>s0>>s1>>s2)){
        in.clear();
        in.ignore(10000,'\n');
        throw errmeniu("nici nu mai incerc las-o asa");}
    g.nume=gunoi;g.hp=b_hp;g.rang=b_rang;g.critrate=b_crit;
    g.stats = {s0,s1,s2};
    //in>>g.hp;
    //in>>g.rang;
    //in>>g.critrate;
    //in>>g.stats[0]>>g.stats[1]>>g.stats[2]; nu mai e nevoie de niciuna din astea 4
    //am crezut ca scap de viu, dar nu, daca pun viata -100 el tot apare ca viu, si insta crash... iub inputurile proaste
    if (g.hp>0){g.viusausall=true;}
    else{g.viusausall=false;}
    return in;}
//am obosit
int Gladiator::operator[](int nr) const {
    //kinda useless dar necesar pt cerinta, basically poti scrie int putere si iti da doar puterea gladiatorului, dar doar pirmesti mai putine informatii decat character stats
    //if (this->stats==nullptr) return -1; //nu mai e nevoie de checku asta
    if(nr>=0 && nr<3){ //sa nu puna varu stats[4] ca il tine, basically safeguard
        return this->stats[nr];} //throw std::out_of_range("ai bagat statsuri invalide, cele maxime acceptate sunt intre 0 si max "+std::to_string(this->stats.size()-1));} iara ma iara gresesc
    throw aigrjlaindex(nr);}
Gladiator& Gladiator::operator++(){ //cat poate un singur om sa iubeasca scrisu de genu asta
    this->hp=hp+10;
    if(this->stats.size()>=3) {
        this->stats[0]=stats[0]+3;
        this->stats[1]=stats[1]+1;
        this->stats[2]=stats[2]+2;}
    return *this;} //iarasi chestia asta :c, apare la greu si in ala cu student, ii inteleg functia da nu-mi place steluta
float Gladiator::operator+(float lvlup_crit) const{return this->critrate+lvlup_crit;}
float operator+(float lvlup, const Gladiator& g){ //asta e efectiv comutativitate
    return g.critrate+lvlup;}
bool Gladiator::operator==(const Gladiator& rezerva)const{
return (this->stats[0]==rezerva.stats[0]);}
bool Gladiator::operator<(const Gladiator& rezerva)const{
return this->stats[0]<rezerva.stats[0];}
///ma ocup de crud

//Personaj** Gladiator::adunatura=NULL; // std isi gestioneaza singur dimensiunea, nu mai am nevoie sa vad eu cate are si chestii dastea, fac adunatura.size() si se rezolva tot
//int Gladiator::nrrezidenti=0; nu cred ca mai e nevoie de asta, practic am initializat-o la inceput

void Gladiator::creategladiator(){
    int tast1;
    Personaj* p_nou=NULL;
    cout<<"\n Apasa 1 sa creezi un gladiator de la 0";
    cout<<"\n Apasa 2 pentru creare rapida";
    cout<<"\n Apasa 3 pentru creare complet aleatorie: \n";
    cout<<"\n Apasa 4 pentru a crea bossul suprem\n";
    cout<<"\n Apasa 5 pentru a aduce un sugar daddy\n";
    cout<<"\n Apasa 6 pentru a elibera un monstru\n";
    if(!(cin>>tast1)){
        cin.clear();
        cin.ignore(10000,'\n');
        cout<<"\nIntrodu un lucru valid.\n";return;}
    if(tast1==1){
        //Gladiator* g_temp=new Gladiator(); //am facut ceva modificai aici sa ma feresc de crash cu g_temp
        auto g_temp=std::make_unique<Gladiator>();
        cout<<"Creaza gladiator";
        cout<<"Introdu cu spatiu intre ele (numele sa fie un singur cuvant): Nume HP Rang(doar Sclav,Gunoier,Print,Rege) CritRate Str Agl End:\n";
        cout<<"Exemplu: Gigel_Frone 100 Sclav 15.5 10 10 10\n> ";
        cin>>*g_temp;
        //if(!cin){
        //    delete g_temp;
        //    return;}
    p_nou=g_temp.release();}// trebuie pointer pentru ca new face un loc liber
    else if(tast1==2){
        std::string nume_temp;
        char rang_temp;
        cout<<"\n Introdu doar nume si rang (EX:Tzanca_Uraganu, enter si apoi Rege)\n";
        cin>>nume_temp>>rang_temp;
        p_nou=new Gladiator(nume_temp,rang_temp);}
    else if(tast1==3){
        p_nou=new Gladiator();}
    else if(tast1==4){
        std::vector<int>stats_morosanu={99,99,99};
        //int stats_morosanu[3]={99,99,99};
        p_nou=new Gladiator("Morosanu",1000,stats_morosanu,'R',99.9f,true);
        cout<<"\n e grav cu monstru asta\n";}
    else if(tast1==5){
        std::string nume_sponsor;
        int hp_s,buget;
        cout<<"\n cum vrei sa fie sponsoru(nume hp buget):\n ";
        cin>>nume_sponsor>>hp_s>>buget;
        p_nou=new Sponsor(nume_sponsor,hp_s,buget);}
    else if(tast1==6){
        std::string nume_m;
        int hp_m,dmg_m;
        char tip_m;
        cout<<"\nIntrodu datele monstrului (Nume HP Tip(D/L/T) Damage):\n> ";
        cin>>nume_m>>hp_m>>tip_m>>dmg_m;
        p_nou=new Monstru(nume_m,hp_m,tip_m,dmg_m);}
    else {cout<<"\n O tasta nu esti in stare sa apesi corect...";return;}
    //alocare dinamica de aici in jos //PARTEA A 3A A PROIECTULUI FTWWWWW
    //Personaj** gunoi=new Personaj*[nrrezidenti+1];  //adaugare dinamica
    //for(int i=0;i<nrrezidenti;i++){
    //    gunoi[i]=adunatura[i];}
    //gunoi[nrrezidenti]=p_nou; //aici intervine polimorfismu
    //if (adunatura!=NULL)delete[] adunatura;
    //adunatura=gunoi;
    //nrrezidenti++;
    adunatura.push_back(p_nou); //joaca comanda asta ca nici aia de la nasa nu stiu sa scrie cod ca asta
    cout<<"\nPersonaj recrutat cu succes >:)";}
void Gladiator::readgladiator(){
    if(adunatura.empty()){ //nu stiam dastea inainte de laboratoru vranceanu
        cout<<"\nN-ai gladiatori disponibili\n";return;}
    int in_viata=std::count_if(adunatura.begin(),adunatura.end(),[](Personaj*p){
        //Gladiator* g=dynamic_cast<Gladiator*>(p);
        return p!=nullptr&&p->gethp()>0;});
    cout<<"\n mai sunt: "<<in_viata<<" gladiatori in viata, dintr-un numar total de: "<<adunatura.size();
    std::sort(adunatura.begin(),adunatura.end(),[](Personaj* a,Personaj* b){ //asta e gen functie de sortare dupa hp value
        //Gladiator*ga=dynamic_cast<Gladiator*>(a);
        //Gladiator*gb=dynamic_cast<Gladiator*>(b);
        int idA=a?a->getid():0;
        int idB=b?b->getid():0;
        return idA<idB;});
    //for(int i=0;i<adunatura.size();i++){
    //    cout<<"\n Acesta este al "<<i<<" -lea gladiator\n";
    ///    Gladiator* gladiatorcurent=dynamic_cast<Gladiator*>(adunatura[i]);
    //    if (gladiatorcurent!=NULL) {
     //       cout<<*gladiatorcurent;}
     //   else{adunatura[i]->veziinfo();}}
    //INLOCUIM TOATA ASTA CU IOBJECT SI FUNCTIA falstring
    for(int i=0;i<adunatura.size();i++){
        cout<<"\n Locul "<<i<<" in gloata\n";
        cout<<*adunatura[i]<<"\n";}
    cout<<"\n Daca vrei sa editezi un gladiator apasa 1, daca nu iesi cu 0 ";  //aici incepe partea de makeover
    char tst;
    cin>>tst;
    if (tst=='1') {
        int tst2;
        cout<<"\n hai da-mi numaru gladiatorului";
        cin>>tst2;
        if (cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\npune un gladiator care exista\n";return;}
        else if (tst2>=0&&tst2<adunatura.size()){
                Gladiator* gedit=dynamic_cast<Gladiator*>(adunatura[tst2]);
        if (gedit!=NULL) {
            gedit->editgladiator();}} else{
                    cout<<"\nn-ai nimerit, incearca alt numar\n";}}
        else if (tst=='0'){
            cout<<"\ninapoi acasa\n";}
        else {cout<<"\nhai ma, aveai de ales doar 0 sau 1\n";}}

void Gladiator::deletegladiator(){ //asta e o arma grea
    if(adunatura.empty()){cout<<"\nN-ai gladiatori de dat afara\n"; return;}
    int tst67;
    cout<<"\n1.) Daca ii stii numele doar da-l afara ";
    cout<<"\n2.) Da cu matura prin cimitir si scapa de ramasitele alea de la gladiatorii morti";
    cout<<"\n alege din astea 2: ";
    if(!(cin>>tst67)){
        cin.clear();cin.ignore(10000,'\n');
        cout<<"\n nu merge \n";return;}
    if(tst67==1) {
        std::string ce_cauti;
        cout<<"\ndeci scrie numele gladiatorului PERFECT: ";
        cin>>ce_cauti;
        auto varu=std::find_if(adunatura.begin(),adunatura.end(),[&](Personaj*p){return p->getnume()==ce_cauti;});
        if (varu!=adunatura.end()){
            cout<<"\neai dat kick lu: "<<(*varu)->getnume()<<"!\n";
            delete*varu; //trebuie sters din heap
            adunatura.erase(varu); // si aici e mai ciudat ca trebuie sters din vectorul de pe heap
        }else {
            //hai sa dovedesc si "stack unwinding"u asta
            Arma smek_raw("nu-ti_zic_nmk",'S');
            throw gldtrngst(ce_cauti);}return;}
            //cout<<"\nverificati jurnalu ca nai un gladiator cu numele asta: \n";}} redundant acum
    else if (tst67==2){
        //auto vericu=std::stable_partition(adunatura.begin(),adunatura.end(),[](Personaj*p) {
        //    return p!=nullptr&&p->gethp()>0;});
        //int cadavre=std::distance(vericu, adunatura.end()); //luam si eliberam memoria de la final
        //std::for_each(vericu,adunatura.end(),[](Personaj* p) {
         //   delete p;});
            //Gladiator*g=dynamic_cast<Gladiator*>(p);
            //if(g!=nullptr&&g->gethp()<=0){ //glad+0hp
              //  delete p; // old school legea celor 3
              //  return true;}return false;});
       // int cadavre=std::distance(vericu,adunatura.end()); e identic mai sus
        //adunatura.erase(vericu,adunatura.end());

        //aici numar cadavrele inainte de stergere
        int cadavre=std::count_if(adunatura.begin(),adunatura.end(),[](Personaj*p){return p!=nullptr&&p->gethp()<=0;});
        adunatura.erase(std::remove_if(adunatura.begin(),adunatura.end(),[](Personaj*p){
            if (p!=nullptr&&p->gethp()<=0){delete p; //sper ca iti place erase ifu
                return true;}return false;}),adunatura.end());
        cout<<"\nAu fost indepartate "<<cadavre<<" cadavre din baza de date!\n";return;}

        //aici e un cimitir de cod iarta-l te rog

    else{cout<<"\nOptiune invalida.\n";return;}
    int index;
    cout<<"\n Ce gladiator vrei sa dai afara?\n";
    if(!(cin>>index)){
        cin.clear();
        cin.ignore(10000,'\n'); //asta e o smecherie de nu o stiam
        cout<<"\nTrebuie un numar, nu asa ceva\n";
        return;}
    if (index>=0&&index<adunatura.size()){
        //Personaj** gunoi_adunatura=NULL;
        //if(nrrezidenti>1){
        //    gunoi_adunatura=new Personaj*[nrrezidenti - 1];}
       // int contor=0;
        //for(int i=0;i<nrrezidenti;i++){
       //     if (i==index){
        //        delete adunatura[i];} else{
         //       gunoi_adunatura[contor++]=adunatura[i];}}
        //delete[] adunatura;
        //adunatura=gunoi_adunatura;
       // nrrezidenti--;
        delete adunatura[index];
        adunatura.erase(adunatura.begin()+index); //toate magii stl, e regele
        cout<<"\nNu l-ai iertat, i-ai dat cu bata in cap pana ai vazut creier\n";}else{cout<<"\nIndex invalid!\n";}}

void Gladiator::emptygladiator() {
    //if (adunatura!=NULL){
    // for(int i=0;i<nrrezidenti;i++){delete adunatura[i];}
    // delete[] adunatura;
    // adunatura=NULL;
    //nrrezidenti=0;}
    //for (auto*p:adunatura){delete p;}
    std::for_each(adunatura.begin(),adunatura.end(),[](Personaj*p){delete p;});
    adunatura.clear();
    cout<<"\nToti gladiatorii au fost eradiati din centru anaf cu succes de franklin\n";}
void Gladiator::traingladiator(){
    if (adunatura.empty()){cout<<"N-ai gladiator de antrenat\n";return;}
    int index; //nu pot scapa de el :c
    cout<<"\n Ce gladiatori vrei sa antrenezi";
    if(!(cin>>index)){
        cin.clear();
        cin.ignore(10000,'\n'); //asta e o smecherie de nu o stiam
        cout<<"\nTrebuie un numar, nu asa ceva\n";return;}
    if (index>=0&&index<adunatura.size()) {
        //punem casting
        Gladiator* gtrain=dynamic_cast<Gladiator*>(adunatura[index]);
        if (gtrain!=NULL) {
            ++(*gtrain);
            cout<<"\nGladiatorul "<<gtrain->getNume()<<" a fost antrenat la stats si hp\n";}
        else{cout<<"\n Nu se poate antrena acest personaj\n";}}
                                                                                                           //++(*adunatura[index]); //ciudat dar merge           //nu mai sterg, doar las ca comentariu
        else{cout<<"\nNu exista acest gladiator\n";}}

void Gladiator::inspectgladiator(){
    if (adunatura.empty()){cout << "\nN-ai gladiator de inspectat";return;}
    int index;
    cout<<"Ce gladiator vrei sa inspectezi";
    if(!(cin>>index)){
        cin.clear();cin.ignore(10000,'\n'); //asta e o smecherie de nu o stiam
        cout<<"\nTrebuie un numar, nu asa ceva\n";return;}
    if (index>=0&&index<adunatura.size()){
        //castingu obligatoriu
        Gladiator* ginspect=dynamic_cast<Gladiator*>(adunatura[index]);
        if (ginspect!=NULL){
            cout<<"\nFoaie gladiator";
            cout<<*ginspect;}else{
            adunatura[index]->veziinfo();}} else{cout<<"\nNu exista gladiatorul";}}
void Gladiator::clonegladiator(){
    if (adunatura.empty()){cout<<"\n-ai pe cine clona frate\n";return;}
    int index;
    cout<<"\n Ce gladiator vrei sa clonezi pentru macelarie?";
    if(!(cin>>index)){
        cin.clear();
        cin.ignore(10000,'\n'); //asta e o smecherie de nu o stiam
        cout<<"\nTrebuie un numar, nu asa ceva\n";
        return;}
    if(index>=0&&index<adunatura.size()){
        Gladiator* goriginal=dynamic_cast<Gladiator*>(adunatura[index]);
        if (goriginal!=NULL){
            Gladiator* clona=new Gladiator(*goriginal); //adica se face dupa templateu gladiator
            //  Gladiator* clona=new Gladiator(*adunatura[index]);
            //Personaj** gunoi=new Personaj*[nrrezidenti+1];
            adunatura.push_back(clona);
            // Gladiator** gunoi=new Gladiator*[nrrezidenti+1]; //alocare dinamica
            //for(int i=0;i<nrrezidenti;i++){
            //    gunoi[i]=adunatura[i];}
            //gunoi[nrrezidenti]=clona;
            //if (adunatura!=NULL) delete[]adunatura;
            //adunatura=gunoi;
            //nrrezidenti++;
            cout<<"\n zici ca sunt in lanu de grau la cum seamana\n";}
        else{ cout<<"\n nu poti clona ca gladiator acest personaj\n";}}
        else{
            cout<<"\n Pls data viitoare baga un gladiator valid\n";return;}}

void Gladiator::taverngladiator(){
     if (adunatura.empty()){
                cout<<"\nDegeaba ai mers ca n-ai prieteni\n";return;}
        int indx;
        cout<<"\nCu ce gladiator mergi la taverna?\n";
        if(!(cin>>indx)){
            cin.clear();cin.ignore(10000,'\n'); //asta e o smecherie de nu o stiam
            cout<<"\nTrebuie un numar, nu asa ceva\n";return;}
        if (indx>=0&&indx<adunatura.size()){
            //aici apare dynamic_cast in loc de static_cast pentru siguranta la runtime, iar daca in vectorul "adunatura" se afla un monstru, dynamic_cast va returna NULL, permitand sa tratez eroarea pe "if (baiatumio==NULL)" si sa evit crash
            Gladiator* baiatumio=dynamic_cast<Gladiator*>(adunatura[indx]);
            if (baiatumio==NULL){cout<<"\n doar gladiatori in taverna, fara monstrii\n"; return;}
            int tast2;
            do{
                cout<<"\n === Wicked Bar ===\n";
                cout<<"\n1.)Baga o Harghita rece\n";
                cout<<"\n2.)Arata-ti barbatia cu un skanderberg cu un strain\n";
                cout<<"\n3.)Baga potiune\n";
                cout<<"\n4.)Sparge-te in figuri\n";
                cout<<"\n5.)Fura buletine\n";
                cout<<"\n0.)Te-ai speriat ca sunt prea multi emolai\n";
                if(!(cin>>tast2)){
                    cin.clear();
                    cin.ignore(10000,'\n');
                    cout<<"\nBaga si tu ceva valid\n";
                    continue;}
                switch(tast2){
                    case 1:{
                        baiatumio->beabere();
                        cout<<"\n Te simti mai fresh\n";break;}
                    case 2:{
                        cout<<"\n Te duci la un biker sa faceti skanderberg\n";
                        Gladiator aleator;
                        cout<<"Bikerul e: "<<aleator;
                        cout<<"\n Va luati de mana\n";
                        if(*baiatumio==aleator){
                            cout<<"\n va bateti la nesfarsit pana lesinati amandoi pe masa, nu castiga nimeni, dar va fura spectatorii berea\n";}
                        else if(*baiatumio<aleator){
                            cout<<"\nTe-a rupt pletosu de ai plecat plangand, ai mai pierdut si 20 de hp\n";
                            baiatumio->sethp(baiatumio->gethp()-20);}
                        else{
                            cout<<"\nTe-a lasat tatuatu sa castigi, da tot fraier esti\n";}break;}
                    case 3:{
                        cout<<"\nTi-a dat baba de pe Strada Spatarului potiune, ai noroc de data asta, ti-a facut bine\n";
                        cout<<"\nCritRateul nou e: "<<*baiatumio+15.5f;break;}
                    case 4:{
                        int stat_indx;
                        cout<<"\n Cu ce te flexezi, cu 1.)Muschii,2.)Un sprint invatat de cand fugeai de papuc,3.)Concurs de baut?\n";
                        cin>>stat_indx;
                        if(stat_indx>=1&&stat_indx<=3){
                            cout<<"Te-au dat afara cand le-ai aratat cat de slab esti"<<(*baiatumio)[stat_indx-1]<<"\n";}
                            else{cout<<"\n Esti atat de beat ca ai dat pe langa si cu flexatu\n";}break;}
                    case 5:{
                        if (adunatura.size()<2){
                            cout<<"\nEsti singur in wicked n-ai pe cine sa furi\n";}
                        else{
                            int tast3;
                        cout<<"\nPe care il nenorocesti?\n";
                        cin>>tast3;
                        if (tast3>=0&&tast3<adunatura.size()&&tast3!=indx) {
                            Gladiator* victima=dynamic_cast<Gladiator*>(adunatura[tast3]);
                            if (victima!=NULL){
                                *baiatumio=*victima;
                                cout<<"\nSaracu nu mai exista, acum ai devenit \n"<<baiatumio->getNume()<<"\n"<<baiatumio->gethp()<<"\n"<<baiatumio->getrang()<<"\n";}
                            else{cout<<"\n ai vrut sa furi buletinu, da ai dat de monstru (sau becali care n-are) si te-ai speriat\n";}}
                        else{cout << "\nN-ai reusit nici macar sa furi\n";}}break;}
                        case 0:{
                        cout<<"\nTe-ai suit pe cal si te-ai dus acasa\n";break;}
                    break;
                default:{cout<<"\nIncearca sa apesi o tasta corecta\n";}}
            }while (tast2!=0);
        }else{cout<<"\nNu exista gladiatorul asta\n";}}
///
void Gladiator::startarena(){
    //functia de initializat programu grafic
    if (adunatura.empty()){
        cout<<"\n E nevoie de un gladiator pentru a veni aici \n";return;}
    const int catdemareeviatamea=16; // fiecare patratel are 50x50 pixeli
    Map dungeon(50,37);
    dungeon.generate(8,12);

    const int viewwidthtiles=20;
    const int viewheighttiles=15;
    sf::RenderWindow window(sf::VideoMode({1280u,720}),"Domeniile Becali");
    window.setFramerateLimit(60); //imi ardea placa video fara asta
    //
    Personaj* cinearjucamaasaceva=adunatura[0];
    auto[spawnX,spawnY]=dungeon.getrandomfloortile();
    cinearjucamaasaceva->setX(spawnX);
    cinearjucamaasaceva->setY(spawnY);
    //Sponsor* becali=new Sponsor("Gigi_Becali_Regele",1000,500000); e risc de memory leak sa fac cu pointer
    auto becali=std::make_unique<Sponsor>("Gigi_Becali_Regele",1000,500000);
    auto[bx,by]=dungeon.getrandomfloortile();
    becali->setX(bx);
    becali->setY(by);

    //Monstru* monstri[3]; si asta e risc de mem leak
    std::vector<std::unique_ptr<Monstru>> monstri;
    for(int i=0;i<3;i++){
        //monstri[i]=new Monstru(); //constructor yippiee
        monstri.push_back(std::make_unique<Monstru>());
        auto[mx,my]=dungeon.getrandomfloortile();
        monstri[i]->setX(mx);
        monstri[i]->setY(my);}
    //de aici incepe ceva chineza, pentru spriteuri si texturi
    sf::Texture secaradreapta,secarastanga,mergeinsus,mergeinjos;
    (void)secaradreapta.loadFromFile("assets/mers_dreapta.png");
    (void)secarastanga.loadFromFile("assets/mers_stanga.png");
    (void)mergeinsus.loadFromFile("assets/mers_sus.png");
    (void)mergeinjos.loadFromFile("assets/mers_jos.png");
    sf::Sprite fatfrumos(mergeinjos);
    //aici chiar e chineza raww dtt, tot pentru imaginile aferente playerului
    auto texsize=mergeinjos.getSize();
    float scalex=static_cast<float>(catdemareeviatamea)/static_cast<float>(texsize.x);
    float scaley=static_cast<float>(catdemareeviatamea)/static_cast<float>(texsize.y);
    fatfrumos.setScale({scalex,scaley});
    fatfrumos.setPosition({static_cast<float>(cinearjucamaasaceva->getX()*catdemareeviatamea),static_cast<float>(cinearjucamaasaceva->getY()*catdemareeviatamea)});
    //restul prezentelor din joc (npcuri cum ar veni)
    sf::Texture texmonstru,texbecali;
    (void)texmonstru.loadFromFile("monstru.png");
    (void)texbecali.loadFromFile("becali.png");
    sf::Sprite heheboi(texmonstru);
    sf::Sprite printulmeu(texbecali);
    //scaling
    heheboi.setScale({static_cast<float>(catdemareeviatamea)/texmonstru.getSize().x,static_cast<float>(catdemareeviatamea)/texmonstru.getSize().y});
    printulmeu.setScale({static_cast<float>(catdemareeviatamea)/texbecali.getSize().x,static_cast<float>(catdemareeviatamea)/texbecali.getSize().y});
    //tileurile
    sf::Texture texfloor,texwall,texdoor,texobstacle;
    const bool hasfloor=texfloor.loadFromFile("assets/tiles/Tile_2.png");
    // const bool haswall=texwall.loadFromFile("assets/tiles/Tile_3.png"); //nu e cazu
    const bool hasdoor=texdoor.loadFromFile("assets/tiles/Tile_1.png");
    const bool hasobstacle=texobstacle.loadFromFile("assets/tiles/obstacle_3.png");
    auto scaletotile=[&](sf::Sprite& spr,const sf::Texture& tex){ //functie lambda, scarboasa rau de tot, capteaza prin referinta
        auto sz=tex.getSize();
        spr.setScale({static_cast<float>(catdemareeviatamea)/static_cast<float>(sz.x),static_cast<float>(catdemareeviatamea)/static_cast<float>(sz.y)});};
    std::optional<sf::Sprite>tffypodea,tffyperete,tffypoarta,tffypeatra;
    if(hasfloor){tffypodea.emplace(texfloor);scaletotile(*tffypodea,texfloor);}
    //if(haswall){tffyperete.emplace(tffyperete);scaletotile(*tffyperete,tffyperete);} //iarasi, nu-i nevoie
    if(hasdoor){tffypoarta.emplace(texdoor);scaletotile(*tffypoarta,texdoor);}
    if(hasobstacle){tffypeatra.emplace(texobstacle);scaletotile(*tffypeatra,texobstacle);}
    sf::RectangleShape tileShape(sf::Vector2f(static_cast<float>(catdemareeviatamea),static_cast<float>(catdemareeviatamea)));
    // aici lucram cu hudu, gen hp si energie
    //incepem cu hp
    sf::Font hudfont;
    (void)hudfont.openFromFile("C:/Windows/Fonts/arial.ttf");
    const float panaundeduce=200.f;
    const float hpbarh=20.f;
    const float hudpad=6.f;
    const float hudX=16.f;
    const float hudY=16.f;
    sf::RectangleShape hpbg({panaundeduce+hudpad*2,hpbarh+hudpad*2});
    hpbg.setFillColor(sf::Color(0,0,0,180));
    hpbg.setOutlineColor(sf::Color(160,30,30));
    hpbg.setOutlineThickness(2.f);
    hpbg.setPosition({hudX,hudY});
    sf::RectangleShape bararosiesilunga({panaundeduce,hpbarh});
    bararosiesilunga.setFillColor(sf::Color(200,30,30));
    bararosiesilunga.setPosition({hudX+hudpad,hudY+hudpad});
    sf::Text hptext(hudfont,"",20);
    hptext.setFillColor(sf::Color::White);
    //aici facem energia
    const float energybarY=hudY+hpbarh+hudpad*2+4.f;
    sf::RectangleShape regelepealergat({panaundeduce+hudpad*2,hpbarh+hudpad*2});
    regelepealergat.setFillColor(sf::Color(0,0,0,180));
    regelepealergat.setOutlineColor(sf::Color(30,160,30));
    regelepealergat.setOutlineThickness(2.f);
    regelepealergat.setPosition({hudX,energybarY});
    sf::RectangleShape energybar({panaundeduce,hpbarh});
    energybar.setFillColor(sf::Color(50,200,50));
    energybar.setPosition({hudX+hudpad,energybarY+hudpad});
    sf::Text energyText(hudfont,"",20);
    energyText.setFillColor(sf::Color::White);
    //hai cu camera aia care trebuie sa se miste dupa personaj
    sf::View camera(sf::FloatRect({0.f,0.f},
        {static_cast<float>(viewwidthtiles*catdemareeviatamea),
         static_cast<float>(viewheighttiles* catdemareeviatamea)}));
    float jumatatew=static_cast<float>(viewwidthtiles*catdemareeviatamea)/2.f;
    float jumatateh=static_cast<float>(viewheighttiles*catdemareeviatamea)/2.f;
    float mapw=static_cast<float>(dungeon.getwidth()*catdemareeviatamea);
    float maph=static_cast<float>(dungeon.getheight()*catdemareeviatamea);
    auto facamera=[&](){
        float cx=static_cast<float>(cinearjucamaasaceva->getX()*catdemareeviatamea)+catdemareeviatamea/2.f;
        float cy=static_cast<float>(cinearjucamaasaceva->getY()*catdemareeviatamea)+catdemareeviatamea/2.f;
        if(cx<jumatatew) cx=jumatatew;
        if(cy<jumatateh) cy=jumatateh;
        if(cx>mapw-jumatatew) cx=mapw-jumatatew;
        if (cy>maph-jumatateh)cy=maph-jumatateh;
        camera.setCenter({cx, cy});
        window.setView(camera);};
    facamera();
    /////////////////////////// aici se intampla magia cu fereastra, pana acum nu se vedea nmk
    while(window.isOpen()){
        while(auto event=window.pollEvent()){
            if(event->is<sf::Event::Closed>()) {
                window.close();}
            if (auto*apasapetasta=event->getIf<sf::Event::KeyPressed>()){
                if (apasapetasta->code==sf::Keyboard::Key::Escape) {window.close();}
                int mergipex=0,mergipey=0;
                std::string ceapasa="";
                if(apasapetasta->code==sf::Keyboard::Key::W){mergipey=-1;ceapasa="W";fatfrumos.setTexture(mergeinsus);}
                else if(apasapetasta->code==sf::Keyboard::Key::S){mergipey=1;ceapasa="S";fatfrumos.setTexture(mergeinjos);}
                else if(apasapetasta->code==sf::Keyboard::Key::A){mergipex=-1;ceapasa="A";fatfrumos.setTexture(secarastanga);}
                else if(apasapetasta->code==sf::Keyboard::Key::D){mergipex=1;ceapasa="D";fatfrumos.setTexture(secaradreapta);}
                if(mergipex!=0||mergipey!=0){
                    int sptnoux=cinearjucamaasaceva->getX()+mergipex; //ce setter pus la munca mi-a folosit f mult (pacat ca nu pot transmite ironia prin text)
                    int sptnouy=cinearjucamaasaceva->getY()+mergipey;
                    if(dungeon.iswalkable(sptnoux,sptnouy)){ //aici chiar e functie tare o iub
                        cinearjucamaasaceva->miscare(ceapasa);
                        fatfrumos.setPosition({static_cast<float>(sptnoux*catdemareeviatamea),static_cast<float>(sptnouy*catdemareeviatamea)});facamera();}}}}

        /////////////////////// aici generez efectiv harta, pana acum am facut doar movementu
        window.clear(sf::Color::Black);
        for(int row=0;row<dungeon.getheight();++row){
            for (int col=0;col<dungeon.getwidth();++col){
                const sf::Vector2f pos={static_cast<float>(col*catdemareeviatamea),static_cast<float>(row*catdemareeviatamea)}; //am innebunit cu cat am scris prostia asta de variabila
                const tiletype tile=dungeon.gettile(col,row);
                std::optional<sf::Sprite>*desenmegatffy=nullptr;
                switch (tile){
                    case tiletype::FLOOR:desenmegatffy=&tffypodea;break;
                    case tiletype::WALL:desenmegatffy=&tffyperete;break;
                    case tiletype::DOOR:desenmegatffy=&tffypoarta;break;
                    case tiletype::OBSTACLE:desenmegatffy=&tffypeatra;break;
                    default:break;}
                if (desenmegatffy && desenmegatffy->has_value()){
                    (*desenmegatffy)->setPosition(pos);
                    window.draw(**desenmegatffy);}else{tileShape.setPosition(pos);tileShape.setFillColor(dungeon.gettilecolor(col, row));window.draw(tileShape);}}}
        //desenez npcuri hooray
        for(int i=0;i<3;i++){
            heheboi.setPosition({static_cast<float>(monstri[i]->getX()*catdemareeviatamea),static_cast<float>(monstri[i]->getY()*catdemareeviatamea)});window.draw(heheboi);}
        printulmeu.setPosition({static_cast<float>(becali->getX()*catdemareeviatamea),static_cast<float>(becali->getY()*catdemareeviatamea)});//pls stop
        window.draw(printulmeu);
        //acum si jucatorul si hudu
        window.draw(fatfrumos);
        window.setView(window.getDefaultView());
        Gladiator* glad=dynamic_cast<Gladiator*>(cinearjucamaasaceva);
        if (glad){
            float impartire=static_cast<float>(glad->gethp())/150.f; //pun extra hp sa tot aibe
            if(impartire<0.f)impartire=0.f;
            if(impartire>1.f)impartire=1.f;
            bararosiesilunga.setSize({panaundeduce*impartire,hpbarh});
            hptext.setString(std::to_string(glad->gethp())+"/150");
            hptext.setPosition({hudX+panaundeduce+hudpad*2+6.f,hudY});}
        window.draw(hpbg);
        window.draw(bararosiesilunga);
        window.draw(hptext);
        window.draw(regelepealergat);
        window.draw(energybar);
        window.draw(energyText);
        window.setView(camera);
        window.display();}
    //delete becali;
    //for(int i=0;i<3;i++)delete monstri[i]; nenecesare folosind unique_ptr
    cout<<"\nsalut bro\n";}
