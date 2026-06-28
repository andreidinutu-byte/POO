//
// Created by andre on 5/17/2026.
//

#ifndef UNTITLED1_EXCEPTII_H
#define UNTITLED1_EXCEPTII_H
#include<exception>
#include<string>
using namespace std;
class exceptiipegladiatori:public std::exception{
protected:
    std::string mesaj;
public:
    exceptiipegladiatori(const std::string& msg):mesaj(msg){}
    const char* what() const noexcept override{return mesaj.c_str();}};
class ceerr:public exceptiipegladiatori{
    private:
        int greseala1;
    public:
        ceerr(int val,const std::string&constanta_necesara):exceptiipegladiatori("ai bagat valoare care nu merge "+std::to_string(val)+" pentru "+constanta_necesara),greseala1(val){}
        int getgreseala1()const{return greseala1;}};

class gldtrngst:public exceptiipegladiatori{
private:
    std::string numecautat;
public:
    gldtrngst(const std::string&nume):exceptiipegladiatori("ce fel de nume mai e si "+nume+", n-am auzit de el"),numecautat(nume){}
    const std::string& getnumecautat() const{return numecautat;}};

class errmeniu:public exceptiipegladiatori{
    private:
    std::string inputgresit;
    public:
    errmeniu(const std::string&input):exceptiipegladiatori("ce optiune e asta varule? n-am auzit de " + input),inputgresit(input){}
    const std::string&getinputgresit()const{return inputgresit;}};
class aigrjlaindex:public exceptiipegladiatori{
private:
    int greseala2;
public:
    aigrjlaindex(int plss):exceptiipegladiatori("ba pls nu mai incerca indexul "+std::to_string(plss)+" care nu exista fullbeg plsss "),greseala2(plss){}
    int getindex() const{return greseala2;}};
#endif //UNTITLED1_EXCEPTII_H