#include "poligon.h"

poligon::poligon(){ 
    points = 0;
    length = 0;
}
poligon::poligon(uint length){
    this->length = length;
    this->points = new vector2d[length];
}
poligon::poligon(const poligon &copy){
    delete [] points;
    this->length = copy.length;
    this->points = new vector2d[length];
    for(uint i = 0;i < length;i++)
        this->points[i] = copy[i];
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
}

vector2d &poligon::operator [](uint index) const{
    return this->points[index];
}

uint poligon::size() const{
    return this->length;
}

void poligon::draw(RenderWindow &rw){
    VertexArray line(type,length+1);
    for(int i = 0;i < length;i++){
        line[i].position = Vector2f(points[i].x,points[i].y);
        line[i].color = this->outlineColor;
    }
    line[length].position = Vector2f(points[0].x,points[0].y);
    rw.draw(line);
}

void poligon::setFillColor(Color c){
    this->fillColor = c;
}
void poligon::setOutlineColor(Color c){
    this->outlineColor = c;
}
void poligon::setOutlineThickness(double thickness){
    this->outlineThickness = thickness;
}















