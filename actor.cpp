#include "actor.h"

#include <string>

Actor::Actor(std::string name, int hp_max) : name(name), hp_max(hp_max), hp(hp_max){};

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