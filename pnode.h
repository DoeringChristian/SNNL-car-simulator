#ifndef PNODE_H
#define PNODE_H
#include "poligon.h"

struct pnode{
    pnode *next = 0;
    pnode *befor = 0;
    poligon *p = 0;
    ~pnode();
};

#endif // PNODE_H
