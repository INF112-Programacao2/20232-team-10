#include "player.h"

unsigned int Player::player_count = 0;

Player::Player(std::string name, int atributes[6]) : Actor(name, atributes) {
    id = player_count;
    player_count++;
}

void Player::workOnProject(int x) {
    project_bar += 5 + x;
}

void Player::study(int x) {
    study_bar += 5 + x;
}

unsigned int Player::getProjectBar(){
    return project_bar;
}


unsigned int Player::getStudyBar(){
    return study_bar;
}