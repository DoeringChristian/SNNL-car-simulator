#ifndef SENSOR_H
#define SENSOR_H
#include "world.h"

class world;

class sensor{
    VertexArray line;
    double distance = -1;
    vector2d A;
    vector2d E;
    double rotation = 3.1415926535897932384626433832795;
public:
    sensor();
    sensor(vector2d pos);
    void setPosition(const vector2d &pos);
    void setRotation(double rotation);
    double getDistance();
    void update(RenderWindow &rw, world &w, bool isVisible);
};

#endif // SENSOR_H
