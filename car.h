#ifndef CAR_H
#define CAR_H
#include "vector2d.h"
#include "world.h"

class sensor;

class car{
    ConvexShape c;
    vector2d pos;
    double rotation;
    
    double speed;
    world *w;
    vector2d size;
    bool isVisible;
    sensor *s;
    uint length;
    double max_angle;
    double rotspeed;
public:
    car();
    car(world &w, vector2d pos, uint sensors, double max_angle = 0.01, double rotation = 0);
    ~car();
    void upate(RenderWindow &rw,bool isVisible,vector2d offset);
    void setRotspeed(double rotspeed);
    void setSpeed(double speed);
    vector2d getPosition() const;
    void setPosition(vector2d pos);
    void setRotation(double rotation);
    bool isColliding();
    uint getLength() const;
    sensor &operator [](const unsigned int i) const;
    
};

#endif // CAR_H
