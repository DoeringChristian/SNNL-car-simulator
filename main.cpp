#include <iostream>
#include <SFML/Graphics.hpp>
#include "simulation.h"
#include "network.h"

using namespace std;
using namespace sf;

RenderWindow window(VideoMode(1000,600),"SFML");

void draw_network(const Network &n, RenderWindow &rw);

int main(){
    bool isVisible = true;
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
    Trainer tr(n,10);
    
    car agents[tr.size()];
    for(uint i = 0;i < tr.size();i++)
        agents[i] = c;
    vector2d car_prev[tr.size()];
    bool isAlive[tr.size()];
    for(uint i = 0;i < tr.size();i++)
        isAlive[i] = true;
    
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
        }
        
        for(uint i = 0;i < tr.size();i++){
            for(uint j = 0;j < tr[i].sizeAt(0);j++)
                tr[i].setInput(j,agents[i][j].getDistance()/MAX_DOUBLE-0.5);
            tr[i].update();
            agents[i].setRotspeed(tr[i].getOutput()[0]-0.5);
            agents[i].setSpeed(tr[i].getOutput()[1]);
            tr[i].setFitness(tr[i].getFitness()-(agents[i].getPosition()-car_prev[i]).length());
            car_prev[i] = agents[i].getPosition();
            if(-tr[i].getFitness() > max_score)
                max_score = -tr[i].getFitness();
        }
        bool crash = true;
        for(uint i = 0;i < tr.size();i++){
            if(!agents[i].isColliding())
                crash = false;
            isAlive[i] = !agents[i].isColliding();
        }
        if(fTC > 1000)
            for(uint i = 0;i < tr.size();i++)
                if(tr[i].getFitness() > -10)
                    isAlive[i] = false;
        
        if(crash || fTC > 10000){
            tr.update(0.1,10/max_score);
            for(uint i = 0;i < tr.size();i++){
                agents[i] = c;
                isAlive[i] = true;
            }
            generation++;
            cout << "generation: " << generation << " best: " << tr[tr.best()].getFitness() << endl;
            fTC = 0;
            tr.resetFitness();
            //logging:
            ofstream log;
            log.open("log.txt",ofstream::out | ofstream::app);
            log << "score: " << tr[tr.best()].getFitness() << " generation: " << generation << endl;
            log.close();
            tr[tr.best()].SavetoFile("test.snn");
            if(maxgen > -1 && generation > maxgen)
                break;
        }
#if 0
        uint best = 0;
        for(uint i = 0;i < tr.size();i++)
            if(isAlive[i] && tr[i].getFitness() < tr[best].getFitness())
                best = i;
#endif
        window.clear(Color::Black);
        w.update(window,isVisible,vector2d(-agents[tr.best()].getPosition().x+window.getSize().x/2,
                 -agents[tr.best()].getPosition().y+window.getSize().y/2));
        for(uint i = 0;i < tr.size();i++){
            if(isAlive[i])
                agents[i].update(window,isVisible,vector2d(-agents[tr.best()].getPosition().x+window.getSize().x/2,
                                 -agents[tr.best()].getPosition().y+window.getSize().y/2));
        }
        
        //c.upate(window,isVisible,vector2d(-c.getPosition().x+window.getSize().x/2,-c.getPosition().y+window.getSize().y/2));
        draw_network(tr[tr.best()],window);
        window.display();
        fTC++;
    }
    tr[tr.best()].SavetoFile("test.snn");
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
