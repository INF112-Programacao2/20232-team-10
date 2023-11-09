#include "actor.h"

#include <string>

Actor::Actor(std::string name, int atributes[6]) {
    this->name = name;
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
    this->hp -= x;
    if (this->hp <= 0) {
        die();
    }
}

void Actor::die() {
}

int Actor::getSkill(std::string s){
    return this->skill[s];
}