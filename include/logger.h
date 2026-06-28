//
// Created by andre on 5/20/2026.
//

#ifndef UNTITLED1_LOGGER_H
#define UNTITLED1_LOGGER_H
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class logger{
private:
    ofstream file;
    logger(){ //constructoru privat
        file.open("jurnal_dragoste.txt",ios::app); //aplicatie ios (glm e input output append)
        if(file.is_open()) file<<"\n gaming sesh nou \n";}
    ~logger(){
        if(file.is_open()){
            file<<" log off \n";
            file.close();}}
public:
    logger(const logger&)=delete;
    logger&operator=(const logger&)=delete;
    static logger&getinstance(){
        static logger ni;
        return ni;}
    void log(const string& msj){
        if(file.is_open()&&!msj.empty()){
            file<<"\nde la sefu: "<<msj<<endl;}}};



#endif //UNTITLED1_LOGGER_H