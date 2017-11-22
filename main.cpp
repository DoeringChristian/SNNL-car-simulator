#include <iostream>
#include <SFML/Graphics.hpp>
#include "world.h"
#include "car.h"

using namespace std;
using namespace sf;

RenderWindow window(VideoMode(800,600),"SFML");

int main(){
    car c;
    world w(c);
    Clock frameClock;
    float frameTime;
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
        }
        frameTime = frameClock.getElapsedTime().asMilliseconds();
        frameClock.restart();
        window.clear(Color::Black);
        w.update(window,frameTime);
        window.display();
    }
    return 0;
}
