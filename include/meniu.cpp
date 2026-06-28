//
// Created by andre on 5/10/2026.
//

#include "meniu.h"
#include "personajesicaractere.h"
#include "arma.h"
#include "armura.h"
#include <iostream>
#include "ceva_abstractidk.h"
#include "inventar_template.h"
#include "logger.h"
using namespace std;
int Menu::optiune=-1;
//am facut fabrica abstracta separat de clasele arma/armura pentru ca fierarul face efecte broken care n-ar trebui sa compromita integritatea obiectelor de baza (ti-a plkt exprimarea??? m simt dstpt)
void dai_test(const fabrricadefer&rejele,Arma&arma_reala,Armura&armura_reala){
    // Cerem arme de la fierarul primit prin parametru
    interfetearme* micunealta=rejele.faArma();
    interfetearmuri* ramasita_din_ghiozdan=rejele.faArmura();
    cout << "\n iesi in fata fierariei sa dai la sac cu ce ti-oi lot \n";
    micunealta->ataca();
    ramasita_din_ghiozdan->apara();
    if(dynamic_cast<const fierariebigD*>(&rejele)){
        cout<<"\n ZAMOLXIS BUFF: Fierarul dacic s-a uitat la tine, a dat din cap si a zis o rugaciune  +5dmg +5def\n";
        ++arma_reala;
        ++armura_reala;logger::getinstance().log("varu de joaca stie ce face si sio luat echipament dacic");}else if(dynamic_cast<const fierarieewww*>(&rejele)){
        cout<<"\n fierarul roman e atat de slab ca instant cum a pus mana pe echipament s-a transformat in praf, mai bine esti cu pumnii goi acum decat cu adunatura de praf \n";
            arma_reala.setDamage(1);
            armura_reala.setProtectie(1);logger::getinstance().log("cine la kemat ba pe asta sa joace sa dus la romani");}
    delete micunealta; //curatam ca suntem baieti cu bun simt
    delete ramasita_din_ghiozdan;}
void fierarie(){
    int tast1;
    Arma arma_ta;
    Armura armura_ta;
    cout<<"\n === Forge Bar ===\n";
    cout<<"Ia niste gunoaie gasite pe jos\n";
    cout<<arma_ta<<armura_ta;
    do{
        cout<<"\n1.)Fa echipament nou de la zero\n";
        cout<<"\n2.)Imbunatateste-ti echipamentul\n";
        cout<<"\n3.)Cere-i piticului din spate sa sufle pe echipament\n";
        cout<<"\n4.)Cantareste-ti armura\n";
        cout<<"\n5.)Compara-ti echipamentele cu cel mai bun care a existat vreodata\n";
        cout<<"\n6.)Copiaza echipamentele de top\n";
        cout<<"\n7.)Incearca-ti norocu cu diavolul\n";
        cout<<"\n8.)Comanda echipament regesc\n";
        cout<<"\n9.)Comanda tepe de pe olx\n";
        cout<<"\n10.)da check out la ghiozdan\n";
        cout<<"\n0.)Iesi din Forge\n";
        if(!(cin>>tast1)){
            cin.clear();
            cin.ignore(10000,'\n');
            cout<<"\nIntrodu un lucru valid.\n";continue;}
        switch(tast1){
            case 1:{
                cout<<"\n Te-ai pus pe construit, baga asa:nume(da fara spatii),(Tip: S(abie)/T(opor)/B(uzdugan))(Damage)(Greutate):\n>";
                cin>>arma_ta;
                cout<<"\n Te-ai pus pe construit, baga asa:nume(da fara spatii),(Tip: U(soara)/G(grea))(Protectie)(Greutate):\n>";
                cin>>armura_ta;
                cout<<"\nIata ce ai produs\n"<<arma_ta<<armura_ta;break;}
            case 2:{
                ++arma_ta;
                ++armura_ta;
                cout<<"\nTi-ai dat upgrade, bravo ma\n"<<arma_ta<<armura_ta;break;}
            case 3:{
                cout<<"\nA suflat piticania aia si uite ce a scos\n";
                cout<<"Damage nou: "<<arma_ta+15<<"\n";
                cout<<"Protectie noua: "<<20+armura_ta<<"\n";
                cout<<"\nCe sa vezi, mai are varu un as in maneca\n";
                cout<<"Ai crit rate mai mare: " << arma_ta.lovituraCritica()<<"\n";
                cout<<"Daca iti cade o shaorma in cap, armura o absoarbe si mai iei doar: "<<armura_ta.bigabsorbtion(50)<<"-hp\n";break;}
            case 4:{
                cout<<"\nPe langa ca esti gras, cantaru mai zice si ca echipamentul tau are: \n";
                cout<<"Pe arma: " << arma_ta[1]<<" kg\n";
                cout<<"Pe armura: "<< armura_ta[1]<<" kg\n";break;}
            case 5:{
                Arma arma_tuffy("Furculita",'S');
                Armura armura_tuffy("Nokia_3310",'G');
                cout << "\nUite asa arata o arma reala\n"<<arma_tuffy;
                if (arma_ta==arma_tuffy){
                    cout<<"sincer arma ta NU o duce asa rau, e ca asta";}
                else if (arma_ta<arma_tuffy){cout<<"Mai buna e o scobitoare\n";}
                else {cout << "E buna rau ai grija de ea\n";}
                cout<<"\n Si asa arata o armura buna "<<armura_tuffy;
                if (armura_ta==armura_tuffy){cout <<"Nu-i rau, o sa reziste\n";}
                else if(armura_ta<armura_tuffy){cout<<"Gasesti chestii mai rezistente la papetarie\n";}
                else{cout<<"E buna rawwwww\n";}
                break;}
            case 6:{
                Arma arma_tuffy("Nightblade",'S');
                Armura armura_tuffy("Lipie_cu_maioneza",'U');
                cout<<"\n Fura blueprientu "<<arma_tuffy<<armura_tuffy;
                cout<<"\n Se ocupa nenea barman de armele tale copiate \n";
                Arma copie1(arma_tuffy);
                Armura copie2(armura_tuffy);
                cout<<"\nHai baga-le repede in sac pana nu vede cineva ca sunt identice\n";
                arma_ta=copie1;
                armura_ta=copie2;
                cout<<"Acum posezi\n"<<arma_ta<<armura_ta;
                break;}
            case 7:{
                cout<<"\nTe-ai dus drept spre diavol, iti indeamna un ban. Il arunci in aer\n";
                int zar=rand()%2+1;
                if (zar==1){
                    cout<<"\nTe-a fraierit de nici nu te recunosc, ti-a distrus tot echipamentul de sunt la fel de puternice ca niste taitei uzi";
                    arma_ta.setDamage(arma_ta-10);
                    armura_ta.setProtectie(armura_ta-10);
                    cout<<"\nSa nu te prind prin arena cu statsuri ca astea\n"<<arma_ta<<armura_ta;}
                else{
                    cout<<"\nBravo ba te-ai jucat cu diavolul si ai castigat\n";
                    ++arma_ta;
                    ++armura_ta;
                    cout<<"\nUite ma ce straluceste echipamentu, asa da\n"<<arma_ta<<armura_ta;}break;}
            case 8:{fierariebigD atelierdacic;
                dai_test(atelierdacic,arma_ta,armura_ta);break;}
            case 9:{fierarieewww atelierRoman;
                dai_test(atelierRoman,arma_ta,armura_ta);break;}
            case 10:{
                cout<<"\n meniu de templateuri \n";
                cout<<"1.)indeasa pana nu mai incape \n";
                cout<<"2.)baga-ti singur kosoni in pungulita \n";
                cout<<"3.)da un upgrade la echipament (am mai fkt asta de vreo 10 ori pana akm) \n";
                cout<<"Alege ce vrei sa testezi:";
                cout<<"\n da-ti seama ce cerinta am acoperit aici\n";
                int tsttt;
                if(!(cin>>tsttt)){
                    cin.clear();cin.ignore(10000,'\n');
                    cout<<"n-ai bagat bine.\n";break;}
                if (tsttt==1){
                    gheozdan<Arma,2>ghiozdandearme;
                    try{cout<<"\n indeasa arma principala in slot 0\n ";
                        ghiozdandearme.baga_bani(arma_ta);
                        logger::getinstance().log("sa bagat arma principala in gheozdan");
                        Arma arma_secundara("sabiuta_de_rezerva",'S');
                        ghiozdandearme.baga_bani(arma_secundara);
                        cout<<"\n o nu am bagat inca o arma extra ce am facut nuuu\n";
                        ghiozdandearme.baga_bani(arma_ta);}
                    catch(const overflow_error&e){
                        cout<<" bv ma ai prins eroarea "<<e.what()<<"\n";logger::getinstance().log("a dat gheozdanu pe dinafara");}
                    ghiozdandearme.aratagheozdan();}
                else if (tsttt==2){
                    gheozdan<int,5>pungacukosoni;
                    cout<<"\ncati kosoni ai furat azi de la nevasta";
                    int numarkosoni;
                    if(cin>>numarkosoni){
                        try{pungacukosoni.baga_bani(numarkosoni);}catch(const overflow_error&e){cout<<"\n a explodat portofelul "<<e.what()<<"\n";}pungacukosoni.aratagheozdan();}}
                else if (tsttt==3){
                    cout<<"\n n-ai vrea tu sa iti dai echipamentul la upgradat? (e cel putin a 100a oara cand facem asta)";
                    cout<<"\n1.)hai la upgrade cu arma ta principala \n"<<arma_ta.getNume()<<"\n";
                    cout<<"\n2.)da de ce sa nu mergem la upgrade cu armura ta? \n"<<armura_ta.getNume()<<"\n";
                    int alege;
                    cin>>alege;
                    if (alege==1){
                        danitelupgrade(arma_ta);}else if(alege==2){danitelupgrade(armura_ta);}else {
                            cout<<"Ai ratat tastele.\n";}}break;}
                case 0:{
                    cout<<"\nTe ardea prea tare fata\n";break;}
                default:{
                    cout<<"\nNu merge tasta asta\n";break;}}}
        while (tast1!=0);}