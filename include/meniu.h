//
// Created by andre on 5/10/2026.
//

#ifndef UNTITLED1_MENIU_H
#define UNTITLED1_MENIU_H
#include "arena.h"
#include "personajesicaractere.h"
#include "exceptii.h"
#include "logger.h"
void fierarie();
class Menu {
private:
  static int optiune;
public:
  static void showMenu(Arena& arena_curenta) {
    //punem arena cu ampersand ca sa o putem schimba in timp real
    cout<<"===================== Gestionare Gladiatori ==================="<<endl;
    cout<<"1.)Recruteaza gladiator"<<endl;
    cout<<"2.)Vezi gloata de gladiatori"<<endl;
    cout<<"3.)Vezi fisa gladiatorului"<<endl;
    cout<<"4.)Cloneaza gladiator"<<endl;
    cout<<"5.)Executa gladiator"<<endl;
    cout<<"6.)Antreneaza un gladiator"<<endl; //momentan se poate face la infinit, dupa o sa implementez si aia cu banii
    cout<<"7.)Editeaza arena curenta"<<endl;
    cout<<"8.)Mergi la fierarie"<<endl;
    cout<<"9.)Mergi in taverna"<<endl;
    cout<<"10.)Joaca-te pe bune"<<endl;
    cout<<"11.)Citeste jurnalu de barfe"<<endl;
    cout<<"============================================================="<<endl;
    cout<<"Alege una dintre optiunile disponibile (introdu 0 pentru a iesi din program): ";
    try{
      if(!(cin>>optiune)){
        cin.clear();
        cin.ignore(10000,'\n');
        throw errmeniu("nu_merge");}
      switch (optiune){
        case 0:{cout<<"Ne revedem in Sovengarde"<<endl; break;}
        case 1:{Gladiator::creategladiator();logger::getinstance().log("so lot un gladiator nou");optiune=-1;break;}
        case 2:{Gladiator::readgladiator();optiune=-1;break;}
        case 3:{Gladiator::inspectgladiator();optiune=-1;break;}
        case 4:{Gladiator::clonegladiator();optiune=-1;break;}
        case 5:{Gladiator::deletegladiator();logger::getinstance().log("ia dat in cap unuia");optiune=-1;break;}
        case 6:{Gladiator::traingladiator();optiune=-1;break;}
        case 7:{antreprenoriat_arena(arena_curenta);optiune=-1;break;}
        case 8:{fierarie();optiune=-1;break;}
        case 9:{Gladiator::taverngladiator(); optiune=-1;break;}
        case 10:{Gladiator::startarena();logger::getinstance().log("sa bagat pe harta");optiune=-1;break;}
        case 11:{std::ifstream file("jurnal_dragoste.txt");
          if (file.is_open()){std::string card;cout<<"\njurnalul siropos al generalului\n";
            while (std::getline(file,card))cout<<card<<"\n";
            file.close();}else{
            cout<<"\n cineva a rupt paginile si a fugit cu ele\n";}optiune = -1;break;}
        case 67:{throw 404;} //uite ce face ultimu catch
        default:{throw errmeniu(std::to_string(optiune));}}}
    catch (const ceerr&e){
      cout<<"\n ti-o dat blue screen \n"<<e.what()<<"\n";optiune=-1;}//what what duhhh
    catch (const gldtrngst&e){
      cout<<"\n ti-o dat blue screen \n"<<e.what()<<"\n";optiune=-1;}
    catch (const errmeniu&e){
      cout<<"\n ti-o dat blue screen \n"<<e.what()<<"\n";optiune=-1;}
    catch (const exceptiipegladiatori&e){
      cout<<"\n te-o dat mega eroare pe gladiatori frt \n"<<e.what()<<"\n";optiune=-1;}
    catch (const std::exception&e){
      cout<<"\n nuj ce ai facut sper ca stie compileru \n"<<e.what()<<"\n";optiune=-1;}
    catch (...){
      cout<<"\n vereeeee face boom calculatoru ce ai bagat acolo /del s32?????????????????????????????????????????????????????????????????????????? \n"<<"\n";optiune=-1;}}
    static int getoptiune(){return optiune;}};


#endif //UNTITLED1_MENIU_H