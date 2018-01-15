#include "car.h"

car::car(){
    this->size = vector2d(10,20);
    this->pos = vector2d(0,0);
    c = ConvexShape(3);
}
car::car(world &w,vector2d pos, double rotation){
    this->pos = pos;
    this->rotation = rotation;
    this->w = &w;
    c = ConvexShape(3);
}

void car::upate(RenderWindow &rw, bool isVisible, vector2d offset){
    this->rotation += rotspeed*speed;
    
    this->pos.x += sin(rotation)*speed;
    this->pos.y += cos(rotation)*speed;
    
    left.setPosition(pos+offset);
    right.setPosition(pos+offset);
    this->left.setRotation(rotation-sensorangel);
    this->right.setRotation(rotation+sensorangel);
    left.update(rw,*w,isVisible);
    right.update(rw,*w,isVisible);
    
    if(isVisible){
        c.setFillColor(Color::Red);
        c.setPoint(0,Vector2f(0,this->size.y/2));
        c.setPoint(1,Vector2f(-this->size.x/2,-this->size.y/2));
        c.setPoint(2,Vector2f(+this->size.x/2,-this->size.y/2));
        c.setPosition(pos.x,pos.y);
        c.rotate(rotation);
        rw.draw(c);
    }
}

void car::setRotspeed(double rotspeed){
    this->rotspeed = rotspeed;
}
void car::setSpeed(double speed){
    this->speed = speed;
}

vector2d car::getPosition() const{
    return this->pos;
}

void car::setPosition(vector2d pos){
    this->pos = pos;
}

void car::setRotation(double rotation){
    this->rotation = rotation;
}








