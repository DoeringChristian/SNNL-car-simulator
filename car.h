#ifndef CAR_H
#define CAR_H
#include "vector2d.h"
#include "world.h"

class sensor;

class car{
    ConvexShape c;
    vector2d pos;
    double rotation = 0;
    double rotspeed = 0;
    double sensorangel = 0.1;
    double speed;
    world *w;
    vector2d size;
    bool isVisible = false;
public:
    sensor left;
    sensor right;
    car();
    car(world &w,vector2d pos,double rotation = 0);
    void upate(RenderWindow &rw,bool isVisible);
    void setRotspeed(double rotspeed);
    void setSpeed(double speed);
    vector2d getPosition() const;
    void setPosition(vector2d pos);
    void setRotation(double rotation);
    
};

#endif // CAR_H
