#include "../include/player.h"

unsigned int Player::player_count = 0;

Player::Player(tgui::String name, int atributes[6]) : Actor(name, atributes) {
    id = player_count;
    this->project_bar = 0;
    this->study_bar = 0;
    player_count++;
}

void Player::workOnProject(int x) {
    project_bar += 5 + x;
}

void Player::study(int x) {
    study_bar += 5 + x;
}

int Player::get_id(){
    return this->id;
}

unsigned int Player::getProjectBar(){
    return project_bar;
}

unsigned int Player::getStudyBar(){
    return study_bar;
}
