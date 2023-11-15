#include "actor.h"

#include <string>

Actor::Actor(std::string name){
    this->name = name;
    this->alive = true;
    this->skill["STR"] = 0;
    this->skill["DEX"] = 0;
    this->skill["CON"] = 0;
    this->skill["INT"] = 0;
    this->skill["WIS"] = 0;
    this->skill["CHA"] = 0;
    this->hp_max = 10 + this->skill["CON"];
    this->hp = this->hp_max;
}

Actor::Actor(std::string name, int atributes[6]) {
    this->name = name;
    this->alive = true;
    this->skill["STR"] = atributes[0];
    this->skill["DEX"] = atributes[1];
    this->skill["CON"] = atributes[2];
    this->skill["INT"] = atributes[3];
    this->skill["WIS"] = atributes[4];
    this->skill["CHA"] = atributes[5];
};

void Actor::heal(int x) {
    this->hp += x;
    if (this->hp > this->hp_max) {
        this->hp = this->hp_max;
    }
}

void Actor::damage(int x) {
    if (x > 0){
        this->hp -= x;
        if (this->hp <= 0) {
            die();
        }
    }
}

std::string Actor::getName(){
    return this->name;
}

void Actor::die() {
    this->alive = false;
}

int Actor::getSkill(std::string s){
    return this->skill[s];
}