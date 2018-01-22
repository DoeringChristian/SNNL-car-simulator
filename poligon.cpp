#include "poligon.h"
#include "iostream"

using namespace std;

poligon::poligon(){ 
    points = 0;
    length = 0;
    line = VertexArray(LinesStrip,length+1);
    this->isVisible = false;
}
poligon::poligon(uint length){
    this->length = length;
    this->points = new vector2d[length];
    line = VertexArray(LinesStrip,length+1);
    this->isVisible = false;
}
poligon::poligon(const poligon &copy){
    delete [] points;
    this->length = copy.length;
    this->points = new vector2d[length];
    for(uint i = 0;i < length;i++)
        this->points[i] = copy[i];
    this->isVisible = false;
}

poligon::~poligon(){
    delete [] points;
}

void poligon::operator =(const poligon &copy){
    delete [] points;
    this->length = copy.length;
    this->points = new vector2d[length];
    for(uint i = 0;i < length;i++)
        this->points[i] = copy[i];
    line = VertexArray(LinesStrip,length+1);
}

vector2d &poligon::operator [](uint index) const{
    return this->points[index];
}

uint poligon::size() const{
    return this->length;
}

void poligon::draw(RenderWindow &rw, bool isVisible, vector2d offset){
    this->isVisible = isVisible;
    if(isVisible){
        for(uint i = 0;i < length;i++){
            line[i].position = Vector2f(points[i].x+offset.x,points[i].y+offset.y);
            line[i].color = Color::White;
        }
        line[length].position = Vector2f(points[0].x+offset.x,points[0].y+offset.y);
        rw.draw(line);
    }
}

bool poligon::Contains(const vector2d &inside) const{
    //test: on edge
    for(uint i = 0;i < this->size();i++){
        uint i2;
        if(i != 0)
            i2 = i-1;
        else 
            i2 = size()-1;
        if((points[i]-points[i2]).length()+0.001 >= (inside-points[i]).length()+(inside-points[i2]).length())
            return true;
    }
    //test: inside
    bool odd = false;
    int j = size()-1;
    for(uint i = 0;i < this->size();i++){
        if((points[i].y < inside.y && points[j].y > inside.y) 
                || (points[i].y > inside.y && points[j].y < inside.y))
            if(points[i].x+(inside.y-points[i].y)/(points[j].y-points[i].y)*(points[j].x-points[i].x) < inside.x)
                odd = !odd;
        j = i;
    }
    return odd;
}















