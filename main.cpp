#include <iostream>
#include <SFML/Graphics.hpp>
#include "simulation.h"
#include "network.h"

using namespace std;
using namespace sf;

RenderWindow window(VideoMode(1000,600),"SFML");

int main(){
    double xq = 50;
    bool isVisible = true;
    uint fTC = 0;
    uint a[4] = {5,4,3,2};
    world w;
    car c(w,vector2d(50,50),5);
    c[0] = sensor(vector2d(0,0),1);
    c[1] = sensor(vector2d(0,0),-1);
    c[2] = sensor(vector2d(0,0),0.15);
    c[3] = sensor(vector2d(0,0),-0.15);
    c[4] = sensor(vector2d(0,0),0);
    
    
    w.LoadFile("test.sim");
    
    Network n(a,4);
    n.LoadFile("test.snn");
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
        
        for(uint i = 0;i < n2.sizeAt(0);i++)
            n2.setInput(i,c[i].getDistance()/MAX_DOUBLE-0.5);
        n2.update();
        
        c.setRotspeed((n2.getOutput()[0]-0.5));
        c.setSpeed(n2.getOutput()[1]);
        
        cout <<  n2.getOutput()[0] << "|" << n2.getOutput()[1] << "|" << tr.currentNet << "|" << fTC << "|" << c.getPosition().x << endl;
        
        if(c.getPosition().x < 0 || c.getPosition().x > 10000 || c.isColliding() || fTC > 10000){
            xq /= fTC;
            n2 = tr.update(-(c.getPosition().x-xq/fTC),-((pow(c.getPosition().x,2)*0.01)/(pow(c.getPosition().x,2)*10)+0.01));//0.1/(c.getPosition().x-xq/fTC));//0.001);
            c.setPosition(vector2d(50,50));
            c.setRotation(1.5);
            xq = 50;
            fTC = 0;
            tr[0].SavetoFile("test.snn");
        }
        fTC ++;
        xq += sqrt(pow(c.getPosition().y-50,2));
        
        srand(time(0));
        
        if(Keyboard::isKeyPressed(Keyboard::S)){
            tr[0].SavetoFile("backup01.snn");
            while(Keyboard::isKeyPressed(Keyboard::S)){}
        }
        if(Keyboard::isKeyPressed(Keyboard::V)){
            isVisible = !isVisible;
            while(Keyboard::isKeyPressed(Keyboard::V)){}
        }
        
        window.clear(Color::Black);
        w.update(window,isVisible,vector2d(-c.getPosition().x+window.getSize().x/2,-c.getPosition().y+window.getSize().y/2));
        c.upate(window,isVisible,vector2d(-c.getPosition().x+window.getSize().x/2,-c.getPosition().y+window.getSize().y/2));
        window.display();
    }
    tr[0].SavetoFile("test.snn");
    return 0;
}
