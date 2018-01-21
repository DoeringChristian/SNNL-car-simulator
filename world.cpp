#include "world.h"

world::world(){
}
world::~world(){
    if(start != 0){
        pnode *n = start;
        while(n != end){
            n = n->next;
            delete n->befor;
        }
        delete n;
    }
}

void world::add(poligon &insert){
    if(start == 0){
        start = new pnode;
        start->p = &insert;
        end = start;
    }
    else{
        end->next = new pnode;
        end->next->p = &insert;
        end->next->befor = end;
        end = end->next;
    }
}

void world::del(poligon &del){
    pnode *n = start;
    if(start != 0){
        while(n != 0){
            if(n->p == &del){
                if(n->next != 0)
                    n->next->befor = n->befor;
                else
                    end = n->befor;
                if(n->befor != 0)
                    n->befor->next = n->next;
                else
                    start = n->next;
                delete n;
                break;
            }
            n = n->next;
        }
    }
}

void world::update(RenderWindow &rw, bool isVisible, vector2d offset){
    this->isVisible = isVisible;
    pnode *n = start;
    if(start != 0){
        while(n != 0){
            n->p->draw(rw,isVisible,offset);
            n = n->next;
        }
    }
}

uint world::size() const{
    uint i = 0;
    pnode *n = start;
    while(n != 0){
        i++;
        n = n->next;
    }
    return i;
}

poligon &world::operator [](uint index) const{
    pnode *n = start;
    uint i = 0;
    while(index > i && n != 0){
        i++;
        n = n->next;
    }
    return *(n->p);
}

bool world::LoadFile(string file){
    ifstream in(file);
    if(in.good()){
        char test = ' ';
        while(test != ';'){
            test = in.get();
        };
        string line;
        while(line != "end;"){
            line = "";
            char c = in.get();
            while(c != ';'){
                c = in.get();
                line.append(string(1,c));
            }
            line.erase(remove(line.begin(),line.end(),'\n'),line.end());
            //add poligons
            if(line != "end;"){
                string coords = line.substr(line.find_first_of(':')+1,line.find_last_of(';')-line.find_first_of(':')-1);
                uint length = 0;
                for(uint i = 0;i < coords.length();i++)
                    if(coords[i] == '|')
                        length++;
                length++;
                poligon *p = new poligon(length);
                cout << "test" << endl;
                string splited[length];
                uint j = 0;
                for(uint i = 0;i < coords.length();i++){
                    if(coords[i] == '|')
                        j++;
                    else
                        splited[j] += coords[i];
                }
                for(uint i = 0;i < length;i++){
                    (*p)[i] = vector2d(stod(splited[i].substr(0,splited[i].find_first_of(','))),
                                       stod(splited[i].substr(splited[i].find_first_of(',')+1,splited[i].length()-splited[i].find_first_of(','))));
                }
                this->add(*p);
            }
        }
        
    }
    else
        return false;
}










