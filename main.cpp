#include <iostream>
#include <SFML/Graphics.hpp>
#include "simulation.h"
#include "network.h"

using namespace std;
using namespace sf;

RenderWindow window(VideoMode(800,600),"SFML");

int main(){
    bool isVisible = false;
    uint fTC = 0;
    uint a[3] = {2,3,2};
    world w;
    car c(w,vector2d(50,50));
    
    poligon p1(2);
    p1[0] = vector2d(0,0);
    p1[1] = vector2d(800,0);
    poligon p2(2);
    p2[0] = vector2d(0,0);
    p2[1] = vector2d(0,100);
    poligon p3(2);
    p3[0] = vector2d(0,100);
    p3[1] = vector2d(800,100);
    w.add(p1);
    w.add(p2);
    w.add(p3);
    
    Network n(a,3);
    Trainer tr(n,0.1,5);
    Network n2 = n;
    n.randomize(1);
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
        }
        
        n2.setInput(0,c.left.getDistance());
        n2.setInput(1,c.right.getDistance());
        n2.update();
        c.setRotspeed(n2.getOutput()[0]-n2.getOutput()[1]);
        c.setSpeed((n2.getOutput()[0]+n2.getOutput()[1])/2);
        
        cout <<  n2.output[0] << "|" << n2.getOutput()[1] << "|" << tr.currentNet << endl;
        
        if(c.getPosition().x < 0 || c.getPosition().x > 800 || c.getPosition().y < 0 || c.getPosition().y > 100 || fTC > 10000){
            n2 = tr.update(-c.getPosition().x,0.01);
            c.setPosition(vector2d(50,50));
            c.setRotation(-1.5);
            fTC = 0;
        }
        fTC ++;
        
        
        if(Keyboard::isKeyPressed(Keyboard::S)){
            tr[0].SavetoFile("backup01.snn");
            while(Keyboard::isKeyPressed(Keyboard::S)){}
        }
        if(Keyboard::isKeyPressed(Keyboard::V)){
            isVisible = !isVisible;
            while(Keyboard::isKeyPressed(Keyboard::V)){}
        }
        
        window.clear(Color::Black);
        c.upate(window,isVisible);
        w.update(window,isVisible);
        window.display();
    }
    tr[0].SavetoFile("test.snn");
    return 0;
}
