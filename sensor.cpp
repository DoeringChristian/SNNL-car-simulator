#include "sensor.h"
#include <iostream>

sensor::sensor(){
    line = VertexArray(Lines,2);
}
sensor::sensor(vector2d pos){
    this->A = pos;
}

double sensor::getDistance(){
    return distance;
}

void sensor::update(RenderWindow &rw, world &w, bool isVisible){
    distance = MAX_DOUBLE;
    vector2d B(A.x+sin(rotation),A.y+cos(rotation));
    vector2d cross;
    vector2d C;
    vector2d D;
    for(uint i = 0;i < w.size();i++)
        for(uint j = 0;j < w[i].size();j++){
            C.x = w[i][j].x;
            C.y = w[i][j].y;
            if(j == w[i].size()-1){
                D.x = w[i][0].x;   
                D.y = w[i][0].y;
            }
            else{
                D.x = w[i][j+1].x;
                D.y = w[i][j+1].y;
            }
            //formula to detemine intersection point of two lines
            double div =           (A.x-B.x)*(C.y-D.y)-(A.y-B.y)*(C.x-D.x);
            double xtop = ((A.x*B.y-A.y*B.x)*(C.x-D.x)-(A.x-B.x)*(C.x*D.y-D.x*C.y));
            double ytop = ((A.x*B.y-A.y*B.x)*(C.y-D.y)-(A.y-B.y)*(C.x*D.y-D.x*C.y));
            if(div != 0){
                cross.x = xtop/div;
                cross.y = ytop/div;
            }
            double dall = sqrt(pow(C.x-D.x,2)+pow(C.y-D.y,2));
            double dboth = sqrt(pow(C.x-cross.x,2)+pow(C.y-cross.y,2))+sqrt(pow(cross.x-D.x,2)+pow(cross.y-D.y,2));
            if(dall >= dboth){
                if((A-cross).length() > (B-cross).length())
                        if((A-cross).length() < distance){
                            distance = (A-cross).length();
                            E = cross;
                            //E.y = cross.y;
                        }
            }
            
        }
    if(distance == MAX_DOUBLE)
        E = A+(B-A)*sqrt(pow(rw.getSize().x,2)+pow(rw.getSize().y,2));
    if(isVisible){
        line[0].color = Color::Green;
        line[0].position = Vector2f(E.x,E.y);
        line[1].color = Color::Green;
        line[1].position = Vector2f(A.x,A.y);
        rw.draw(line);
    }
}

void sensor::setPosition(const vector2d &pos){
    this->A = pos;
}

void sensor::setRotation(double rotation){
    this->rotation = rotation;
}













