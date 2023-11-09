#include "player.h"

void Player::workOnProject(int x) {
    project_bar += 5 + x;
}

void Player::study(int x) {
    study_bar += 5 + x;
}