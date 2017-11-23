#ifndef WORLD_H
#define WORLD_H
#include "pnode.h"
#include "cube.h"
#include "sensor.h"

class world{
    pnode *start = 0;
    pnode *end = start;
    bool isVisible = false;
public:
    world();
    ~world();
    
    void add(poligon &insert);
    void del(poligon &del);
    uint size() const;
    poligon &operator [](uint index) const;
    
    void update(RenderWindow &rw,bool isVisible);
};

#endif // WORLD_H
