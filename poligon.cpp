#include "poligon.h"

poligon::poligon(){ 
    points = 0;
    length = 0;
    line = VertexArray(type,length+1);
}
poligon::poligon(uint length){
    this->length = length;
    this->points = new vector2d[length];
    line = VertexArray(type,length+1);
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
    line = VertexArray(type,length+1);
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
        for(int i = 0;i < length;i++){
            line[i].position = Vector2f(points[i].x+offset.x,points[i].y+offset.y);
            line[i].color = this->outlineColor;
        }
        line[length].position = Vector2f(points[0].x+offset.x,points[0].y+offset.y);
        rw.draw(line);
    }
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















