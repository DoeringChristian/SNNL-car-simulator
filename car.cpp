#include "car.h"

car::car(){
    this->size = vector2d(10,20);
    this->pos = vector2d(0,0);
    c = ConvexShape(3);
    rotation = 0;
    rotspeed = 0;
    sensorangel = 0.15;
    isVisible = false;
}
car::car(world &w,vector2d pos, double rotation){
    this->pos = pos;
    this->rotation = rotation;
    this->w = &w;
    c = ConvexShape(3);
    rotspeed = 0;
    sensorangel = 0.15;
    isVisible = false;
}

void car::upate(RenderWindow &rw, bool isVisible, vector2d offset){
    this->rotation += rotspeed*speed;
    
    this->pos.x += sin(rotation)*speed;
    this->pos.y += cos(rotation)*speed;
    
    left.setPosition(pos);
    right.setPosition(pos);
    this->left.setRotation(rotation-sensorangel);
    this->right.setRotation(rotation+sensorangel);
    left.update(rw,*w,isVisible,offset);
    right.update(rw,*w,isVisible,offset);
    
    if(isVisible){
        c.setFillColor(Color::Red);
        c.setPointCount(4);
        vector2d A = (this->size*0.5).rotate(this->rotation)+this->pos;
        vector2d B = (vector2d(-this->size.x,-this->size.y)*0.5).rotate(this->rotation)+this->pos;
        vector2d C = (vector2d(this->size.x,-this->size.y)*0.5).rotate(this->rotation)+this->pos;
        vector2d D = (vector2d(-this->size.x,this->size.y)*0.5).rotate(this->rotation)+this->pos;
        c.setPoint(0,Vector2f(A.x,A.y));
        c.setPoint(1,Vector2f(C.x,C.y));
        c.setPoint(2,Vector2f(B.x,B.y));
        c.setPoint(3,Vector2f(D.x,D.y));
        c.setPosition(pos.x,pos.y);
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

bool car::isColliding(){
    for(uint i = 0;i < w->size();i++){
        vector2d A = (this->size*0.5).rotate(this->rotation)+this->pos;
        vector2d B = (vector2d(-this->size.x,-this->size.y)*0.5).rotate(this->rotation)+this->pos;
        vector2d C = (vector2d(this->size.x,-this->size.y)*0.5).rotate(this->rotation)+this->pos;
        vector2d D = (vector2d(-this->size.x,this->size.y)*0.5).rotate(this->rotation)+this->pos;
        if((*w)[i].Contains(A) || (*w)[i].Contains(B) || (*w)[i].Contains(C) || (*w)[i].Contains(D))
            return true;
    }
    return false;
}








