#ifndef CAR_H
#define CAR_H
#include "vector2d.h"
#include "sensor.h"

class world;
class sensor;

class car{
    vector2d pos;
    double rotation = 0;
    double rotspeed = 0;
    double sensorangel = 0.1;
    double speed;
    world *w;
    vector2d size;
public:
    sensor left;
    sensor right;
    car();
    car(world &w,vector2d pos,double rotation = 0);
    void upate(RenderWindow &rw, float frameTime);
    void setRotspeed(double rotspeed);
    void setSpeed(double speed);
    
};

#endif // CAR_H
