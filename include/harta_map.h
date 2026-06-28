//
// Created by andre on 5/10/2026.
//

#ifndef UNTITLED1_HARTA_MAP_H
#define UNTITLED1_HARTA_MAP_H
#include <iostream>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <SFML/Graphics.hpp>

enum class tiletype { WALL, FLOOR, DOOR, OBSTACLE }; //aici am fost ajutat, nu stiam de enum class, dar are sens, ma protejeaza sa nu se incurce variabilele, e un perete de siguranta
class Room {
private:
    int x,y,width,height;
public:
    Room():x(0),y(0),width(0),height(0){}
    Room(int x,int y,int w,int h):x(x),y(y),width(w),height(h){}
    int getX() const{return x;}
    int getY() const{return y;}
    int getwidth() const{return width;}
    int getheight() const{return height;}
    int centerX() const{return x+width/2;}
    int centerY() const{return y+height/2;} //getteri pt tot ce voi avea nevoie sa ma orientez pe harta
    bool intersects(const Room& other,int padding=1)const {
        return (x<=other.x+other.width+padding&&x+width+padding>=other.x&&y<=other.y+other.height+padding&&y+height+padding>=other.y);}}; //safety measure, ma asigur ca nu se suprapun camerele

class Map{
private:
    int width;
    int height;
    std::vector<std::vector<tiletype>>tiles;
    std::vector<Room> camarute;
    //tiletype**tiles;
    //Room* camarute;
    int nrcamerecurente;
    void fillwithwalls(){ //sa para a fi camera inchisa
        for (int y=0;y<height;++y){
            for (int x=0;x<width;++x){
                tiles[y][x]=tiletype::WALL;}}}
    void carveroom(const Room& room){
        for (int y=room.getY();y<room.getY()+room.getheight();++y){
            for (int x=room.getX();x<room.getX()+room.getwidth();++x){
                tiles[y][x]=tiletype::FLOOR;}}}
    void carvehorizontalcorridor(int x1,int x2,int y){
        for (int x=std::min(x1, x2);x<=std::max(x1,x2);++x){
            if (isinbounds(x,y))tiles[y][x]=tiletype::FLOOR;}}
    void carveverticalcorridor(int y1,int y2,int x){
        for (int y=std::min(y1,y2);y<=std::max(y1,y2);++y){
            if (isinbounds(x,y))tiles[y][x]=tiletype::FLOOR;}}
    void connectrooms(const Room& a,const Room& b){ //functie f smechera care se uita unde sunt camerele si genereaza coridoare intre ele
        int x1=a.centerX();
        int y1=a.centerY();
        int x2=b.centerX();
        int y2=b.centerY();
        if (rand()%2==0){
            carvehorizontalcorridor(x1,x2,y1);
            carveverticalcorridor(y1,y2,x2);}else{
            carveverticalcorridor(y1,y2,x1);
            carvehorizontalcorridor(x1,x2,y2);}}
    bool isadjacenttodoor(int x,int y)const{
        if(!isinbounds(x,y))return false;
        if(isinbounds(x+1,y)&&tiles[y][x+1]==tiletype::DOOR)return true;
        if(isinbounds(x-1,y)&&tiles[y][x-1]==tiletype::DOOR)return true;
        if(isinbounds(x,y+1)&&tiles[y+1][x]==tiletype::DOOR)return true;
        if(isinbounds(x,y-1)&&tiles[y-1][x]==tiletype::DOOR)return true;return false;} //verifica daca esti langa usa in toate 4 directiile
    void placedoors(){
        for (int y=1;y<height-1;++y){
            for (int x=1;x<width-1;++x){
                if (tiles[y][x]==tiletype::FLOOR){
                    bool walltopbottom=(tiles[y-1][x]==tiletype::WALL&&tiles[y+1][x]==tiletype::WALL);
                    bool wallleftright=(tiles[y][x-1]==tiletype::WALL&&tiles[y][x+1]==tiletype::WALL);
                    if((walltopbottom&&!wallleftright)||(!walltopbottom&&wallleftright)){if(rand()%100<20){tiles[y][x]=tiletype::DOOR;}}}}}}
    void placeobstacles(int count){
        int placed=0;
        int tries=0;
        while(placed<count&&tries<1000){
            int x=rand()%width;
            int y=rand()%height;
            if (tiles[y][x]==tiletype::FLOOR&&!isadjacenttodoor(x,y)){ //if de verificare ca nu blocam accesul la usi
                tiles[y][x]=tiletype::OBSTACLE;
                placed++;}tries++;}}
//pana aici am avut incapsulare, toate astea se vor face oricand vrei sa faci o harta, n-are nevoie programatorul sa le vada
public:
    Map(const Map&)=delete;
    Map& operator=(const Map&)=delete;
    Map(int width=50,int height=30):width(width),height(height),nrcamerecurente(0) {
        //tiles=new tiletype*[height];
        //for(int i=0;i<height;++i){
        //    tiles[i]=new tiletype[width];
        //    for(int j=0;j<width;++j){tiles[i][j]=tiletype::WALL;}}camarute=nullptr;}
        tiles.resize(height,std::vector<tiletype>(width,tiletype::WALL));}
    //~Map() {for (int i=0;i<height;++i){
    //        delete[] tiles[i];}
    //    delete[] tiles;
    //    if (camarute!=nullptr) {delete[] camarute;}}
    ~Map()=default;
    void generate(int numroomsfinal=6,int obstaclecount=10){fillwithwalls();
        //if(camarute!=nullptr){
        //    delete[] camarute;
        //    camarute=nullptr;}
        camarute.clear();
        nrcamerecurente=0;
        for(int i=0;i<numroomsfinal;++i){
            int rw=rand()%8+5;
            int rh=rand()%8+5;
            int rx=rand()%(width-rw-2)+1;
            int ry=rand()%(height-rh-2)+1;
            Room newroom(rx,ry,rw,rh);
            bool failed=false;
            for (int j=0;j<nrcamerecurente;j++){
                if(newroom.intersects(camarute[j])){
                    failed=true;break;}}
            if(!failed){
                carveroom(newroom);
                if(nrcamerecurente>0){
                    connectrooms(camarute[nrcamerecurente-1],newroom);}
                //Room* temp=new Room[nrcamerecurente+1];
                camarute.push_back(newroom);
                //temp[nrcamerecurente]=newroom;
                //delete[] camarute;
                //camarute=temp;
                nrcamerecurente++;}}
        placedoors();
        placeobstacles(obstaclecount);}
    int getwidth()const{return width;}
    int getheight()const{return height;}
    bool isinbounds(int x,int y)const{return x>=0&&x<width&&y>=0&&y<height;}
    tiletype gettile(int x,int y)const{
        if(!isinbounds(x,y))return tiletype::WALL;
        return tiles[y][x];}
    bool iswalkable(int x,int y)const{
        if(!isinbounds(x,y))return false;
        tiletype type=tiles[y][x];
        return type==tiletype::FLOOR||type==tiletype::DOOR;} //functie tare, nu ma lasa sa pasesc, e o functie mica dar e mult mai importanta pentru functionalitatea jocului dkt te-ai astepta
    std::pair<int,int>getrandomfloortile()const{
        int limitadeincercari=1000;
        while(limitadeincercari-->0){
            int x=rand()%width;
            int y=rand()%height;
            if (tiles[y][x]==tiletype::FLOOR){
                return {x,y};}}return{1,1};}
    sf::Color gettilecolor(int x,int y)const{
        if(!isinbounds(x,y))return sf::Color::Black;
        switch(tiles[y][x]){
            case tiletype::FLOOR:return sf::Color(50, 50, 50);
            case tiletype::WALL:return sf::Color(100, 100, 100);
            case tiletype::DOOR:return sf::Color(139, 69, 19);
            case tiletype::OBSTACLE:return sf::Color(200, 0, 0);
            default:return sf::Color::Magenta;}}};


#endif //UNTITLED1_HARTA_MAP_H