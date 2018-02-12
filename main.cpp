#include <iostream>
#include <SFML/Graphics.hpp>
#include "simulation.h"
#include "network.h"

using namespace std;
using namespace sf;

RenderWindow window(VideoMode(1000,600),"SFML");

void draw_network(const Network &n, RenderWindow &rw);

int main(){
    srand(time(0));
    bool isVisible = true;
    vector2d car_prev;
    double score = 0;
    double max_score = 0;
    
    //set max generation
    int maxgen = -1;
    string in;
    cout << "max generations (-1 for infinit):" << endl;
    cin >> in;
    maxgen = atoi(in.c_str());
    
    
    uint generation = 0;
    uint fTC = 0;
    uint a[4] = {5,4,3,2};
    world w;
    car c(w,vector2d(50,50),5,0.02);
    c[0] = sensor(vector2d(0,0),1);
    c[1] = sensor(vector2d(0,0),-1);
    c[2] = sensor(vector2d(0,0),0.15);
    c[3] = sensor(vector2d(0,0),-0.15);
    c[4] = sensor(vector2d(0,0),0);
    
    w.LoadFile("test.sim");
    
    Network n(a,4,false);
    if(!n.LoadFile("test.snn"))
        n.randomize(1,2);
    Trainer tr(n,1,SOF_First_Second,10);
    n = tr.current();
    //n.randomize(1);
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
        }
        
        for(uint i = 0;i < n.sizeAt(0);i++)
            n.setInput(i,c[i].getDistance()/MAX_DOUBLE-0.5);
        n.update();
        
        c.setRotspeed((n.getOutput()[0]-0.5));
        c.setSpeed(n.getOutput()[1]);
        score += (c.getPosition()-car_prev).length();
        car_prev = c.getPosition();
        
        //cout <<  n.getOutput()[0]-0.5 << "|" << n.getOutput()[1] << "|" << generation << "|" << tr.currentNet << "|" << fTC << "|" << c.getPosition().x << endl;
        
        if(c.isColliding() || fTC > 10000 || (fTC > 1000 && score < 10)){
            cout << "network: " << tr.currentNet << endl;
            if(tr.currentNet == tr.size()-1){
                cout << "generation: " << generation << " networks: ";
                for(uint i = 0;i < tr.size();i++)
                    cout << tr[i].getFitness() << "|";
                cout << endl;
                generation++;
            }
            if(tr.currentNet == 0){
                ofstream log;
                log.open("log.txt",ofstream::out | ofstream::app);
                log << "score: " << score << " generation: " << generation << endl;
                log.close();
            }
            if(score > max_score)
                max_score = score;
            
            n = tr.update(-(score),0.1,10/max_score);
            c.setPosition(vector2d(50,50));
            c.setRotation(1.5);
            car_prev = c.getPosition();
            score = 0;
            fTC = 0;
            tr[0].SavetoFile("test.snn");
            //max generation exeption
            if(generation >= maxgen && maxgen != -1)
                break;
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
#if 1
        if(Keyboard::isKeyPressed(Keyboard::K)){
            fTC = 10000;
            while(Keyboard::isKeyPressed(Keyboard::K)){}
        }
#endif
        
        window.clear(Color::Black);
        w.update(window,isVisible,vector2d(-c.getPosition().x+window.getSize().x/2,-c.getPosition().y+window.getSize().y/2));
        c.upate(window,isVisible,vector2d(-c.getPosition().x+window.getSize().x/2,-c.getPosition().y+window.getSize().y/2));
        draw_network(n,window);
        window.display();
    }
    tr[0].SavetoFile("test.snn");
    return 0;
}

void draw_network(const Network &n,RenderWindow &rw){
    const double d = 50;
    for(uint i = 0;i < n.size();i++){
        for(uint j = 0;j < n.sizeAt(i);j++){
            CircleShape s(10);
            s.setPosition(Vector2f(10+i*d,j*d+d/2*(n.sizeAt(0)-n.sizeAt(i))+d));
            s.setFillColor(Color(0,0,(Uint8)(sqrt(pow(n(i)[j],2))*128+128)));
            s.setOutlineThickness(2);
            if(i != 0)
                s.setOutlineColor(Color((Uint8)(-(n.getbias(i-1)[j]*255)),(Uint8)((n.getbias(i-1)[j]*255)),0));
            rw.draw(s);
            if(i != 0){
                for(uint k = 0;k < n(i-1).size();k++){
                    VertexArray ver(LinesStrip,2);
                    ver[0].position = Vector2f(20+i*d,j*d+d/2*(n.sizeAt(0)-n.sizeAt(i))+d+10);
                    ver[0].color = Color((Uint8)(-n[i-1][k][j]*255),(Uint8)(n[i-1][k][j]*255),0);
                    ver[1].position = Vector2f(20+(i-1)*d,k*d+d/2*(n.sizeAt(0)-n.sizeAt(i-1))+d+10);
                    ver[1].color = Color((Uint8)(-n[i-1][k][j]*255),(Uint8)(n[i-1][k][j]*255),0);
                    rw.draw(ver);
                }
            }
        }
    }
}
