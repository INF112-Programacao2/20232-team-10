#include "actor.h"

#include <string>

Actor::Actor(std::string name, int hp_max) : _name(name), _hp_max(hp_max), _hp(hp_max){};

void Actor::heal(int x) {
    _hp += x;
    if (_hp > _hp_max) {
        _hp = _hp_max;
    }
}

void Actor::heal(int x) {
    _hp += x;
    if (_hp > _hp_max) {
        _hp = _hp_max;
    }
}

void Actor::damage(int x) {
    _hp -= x;
    if (_hp <= 0) {
        die();
    }
}

void Actor::die() {
}
