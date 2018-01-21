#include "pnode.h"

pnode::pnode(){
    befor = 0;
    next = 0;
    p = 0;
}

pnode::~pnode(){
    delete p;
}
