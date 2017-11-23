#ifndef POLIGON_H
#define POLIGON_H
#include "vector2d.h"
#include <SFML/Graphics.hpp>

using namespace sf;

typedef unsigned int uint;

class poligon{
protected:
    VertexArray line;
    vector2d *points;
    uint length;
    Color fillColor = Color::Black;
    Color outlineColor = Color::White;
    double outlineThickness = 1;
    PrimitiveType type = LinesStrip;
    bool isVisible = false;
public:
    poligon();
    poligon(uint length);
    poligon(const poligon &copy);
    ~poligon();
    
    vector2d &operator [](uint index) const;
    void operator =(const poligon &copy);
    uint size() const;
    void draw(RenderWindow &rw,bool isVisible);
    
    void setFillColor(Color c);
    void setOutlineColor(Color c);
    void setOutlineThickness(double thickness);
};

#endif // POLIGON_H
