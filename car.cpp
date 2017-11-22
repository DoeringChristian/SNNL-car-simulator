#include "car.h"

car::car(){
    this->size = vector2d(10,20);
    this->pos = vector2d(0,0);
}
car::car(world &w,vector2d pos, double rotation){
    this->pos = pos;
    this->rotation = rotation;
    this->w = &w;
}

void car::upate(RenderWindow &rw, float frameTime){
    this->rotation += rotspeed*frameTime*speed;
    
    this->pos.x += sin(rotation)*speed*frameTime;
    this->pos.y += cos(rotation)*speed*frameTime;
    
    left.setPosition(pos);
    right.setPosition(pos);
    this->left.setRotation(rotation-sensorangel);
    this->right.setRotation(rotation+sensorangel);
    left.update(rw,*w);
    right.update(rw,*w);
    
    ConvexShape c(3);
    c.setFillColor(Color::Red);
    c.setPoint(0,Vector2f(0,this->size.y/2));
    c.setPoint(1,Vector2f(-this->size.x/2,-this->size.y/2));
    c.setPoint(2,Vector2f(+this->size.x/2,-this->size.y/2));
    c.setPosition(pos.x,pos.y);
    c.rotate(rotation);
    rw.draw(c);
}

void car::setRotspeed(double rotspeed){
    this->rotspeed = rotspeed;
}
void car::setSpeed(double speed){
    this->speed = speed;
}










