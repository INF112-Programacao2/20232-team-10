#include "player.h"

void Player::work_on_project(int x) {
    _project += 5 + x;
}

void Player::study(int x) {
    _study += 5 + x;
}