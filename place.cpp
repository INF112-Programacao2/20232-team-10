#include "place.h"

int Place::next_id = 0;

//Inicialização do construtor
Place::Place(tgui::String name, tgui::String picture) : name(name), picture(picture){
    id = next_id;
    next_id++;
}

tgui::String Place::getName(){
    return name;
}

tgui::String Place::getPicture(){
    return picture;
}

void Place::setBonus(int key, int value){
    actionBonus[key] = value;
}

int Place::getBonus(int key){
    if (actionBonus.find(key) == actionBonus.end()){
        return 0;
    }
    else{
        return actionBonus[key];
    }
}