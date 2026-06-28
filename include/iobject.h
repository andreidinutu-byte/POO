//
// Created by andre on 5/20/2026.
//

#ifndef IOBJECT_H
#define IOBJECT_H
#include<string>
#include<iostream>

class obiecti{
protected:
    inline static int id2=0;//ms c++17 k il initializezi singur
    const int id_unicat;
public:
    obiecti():id_unicat(++id2){}
    virtual ~obiecti()=default;
    virtual std::string toString()const=0;
    int getid()const noexcept{return id_unicat;}
    bool operator==(const obiecti&other)const{
        return this->getid()==other.getid();}
    obiecti& operator=(const obiecti& valeoo){
        if(this!=&valeoo){}
        return *this;}
    friend std::ostream& operator<<(std::ostream& os,const obiecti&obj){
        os<<obj.toString();
        return os;}};
#endif