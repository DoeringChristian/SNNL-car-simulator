#ifndef SENSOR_H
#define SENSOR_H
#include "world.h"
#define MAX_DOUBLE 10005

class world;

class sensor{
    VertexArray line;
    double distance;
    vector2d A;
    vector2d E;
    double rotation;
public:
    sensor();
    sensor(vector2d pos);
    void setPosition(const vector2d &pos);
    void setRotation(double rotation);
    void update(RenderWindow &rw, world &w, bool isVisible, vector2d offset);
    double getDistance();
};

#endif // SENSOR_H
