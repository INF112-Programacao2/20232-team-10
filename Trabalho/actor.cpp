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

int Actor::get_STR() {
  return _STR;
}

int Actor::get_DEX() {
  return _DEX;
}

int Actor::get_CON() {
  return _CON;
}

int Actor::get_INT() {
  return _INT;
}

int Actor::get_WIS() {
  return _WIS;
}

int Actor::get_CHA() {
  return _CHA;
}