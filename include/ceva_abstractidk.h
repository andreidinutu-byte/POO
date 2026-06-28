//
// Created by andre on 5/18/2026.
//

#ifndef UNTITLED1_CEVA_ABSTRACTIDK_H
#define UNTITLED1_CEVA_ABSTRACTIDK_H
#include "iostream"
using namespace std;

//interfetele produselor "abstracte"
class interfetearme{
public:
    virtual void ataca() const=0;
    virtual ~interfetearme()=default;}; //destructor facut de compilator g
class interfetearmuri{
public:
    virtual void apara() const=0;
    virtual ~interfetearmuri()=default;};

//produsele mele reale puse la vanzare
// hai cu echipamentu dacic ///la urmatoru update o sa gasim laseru din carpati pana atunci avem doar armurile OP
class sabiebigD:public interfetearme{
public:
    void ataca() const override{
        cout<<" hit mega puternic cu sabia dacica, ea nu stie de armura sau de scut \n";}};
class scutbigD:public interfetearmuri{
public:
    void apara() const override{
        cout<<" scutul dacic e imbuibat cu puterile lui zamolxis si nu te poate atinge nimeni \n";}};
//hai cu ala roman
class sabieewww:public interfetearme{
public:
    void ataca() const override{
        cout<<"nu dai damage cu chestia asta nu stiu de ce ai luat-o\n";}};
class scutewww:public interfetearmuri{
public:
    void apara() const override{
        cout<<"patrunde drept prin tine si o pietricica cu scutu asta \n";}};

//fabrica aia de care zici au fost prietenii pe care i-am facut pe drumul pana la cerinta 7
class fabrricadefer{
public:
    virtual interfetearme* faArma()const=0;
    virtual interfetearmuri* faArmura()const=0;
    virtual ~fabrricadefer()=default;};
//si fabricile alea in sine aici tb sa fie
class fierariebigD:public fabrricadefer{
public:
    interfetearme*faArma()const override{return new sabiebigD();}
    interfetearmuri*faArmura()const override{return new scutbigD();}};
class fierarieewww:public fabrricadefer{
public:
    interfetearme*faArma()const override{return new sabieewww();}
    interfetearmuri*faArmura()const override{return new scutewww();}};
#endif //UNTITLED1_CEVA_ABSTRACTIDK_H