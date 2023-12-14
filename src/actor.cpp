#include "../include/actor.h"
#include "../include/dice.h"

Actor::Actor(tgui::String name){                 //Construtor
    this->name = name;
    this->alive = true;             
    for (int i = 0; i < SKILL_NUM; i++){    //Inicializacao do valores das skills com 0
        this->skill[i] = 3;
    }
    for (int i = 0; i < NEEDS_NUM; i++){
        this->need[i] = 5;
    }
    this->injuries = 0;     //Zera a quantidade de dano
}

Actor::Actor(tgui::String name, int atributes[6]) {
    this->name = name;
    this->alive = true;
    for (int i = 0; i < SKILL_NUM; i++){    //Atualiza os valores da skills para a quantidade de pontos escolhida pelo jogador
        this->skill[i] = atributes[i];
    }
    for (int i = 0; i < NEEDS_NUM; i++){
        this->need[i] = 5;
    }
    this->injuries = 0;     //Zera a quantidade de dano
    this->killer = false;
};

void Actor::heal(int x) {               //Funcao para curar
    injuries -= x;
    if (injuries < 0){
        injuries = 0;
    }
}

bool Actor::damage(int x) {             //Funcao para sofrer dano
    injuries += x;
    if (injuries > skill[ENDURANCE] + 3) {
        die();
        return true;
    }
    return false;
}

tgui::String Actor::getName(bool use_alias){
    if (use_alias && costumed){
        return this->costume;
    }
    else{
        return this->name;
    }
}

void Actor::die() {         //Funcao para morte do jogador
    this->alive = false;    //Booleano de estado de vida vira falso
}

int Actor::getSkill(int skill_name){
    return this->skill[skill_name];
}

bool Actor::skillCheck(int skill_name, int challenge){
    return skillRoll(skill_name, 100) > challenge;
}

int Actor::skillRoll(int skill_name, int range){
    if (skill[skill_name]-2 > 0){
        return Dice::dice(range, skill[skill_name]-2, '>');
    }
    else{
        return Dice::dice(range, (skill[skill_name]-3)*-1, '<');
    }
}

bool Actor::isAlive(){
    return alive;
}

int Actor::getDamageLevel(){
    return this->injuries;
}

tgui::String Actor::getHealth(){
    if (this->injuries == 0){
        return "Você não tem nenhum ferimento";
    }
    else if (this->injuries == vitality){
        return "Você está à beira da morte";
    }
    else if (this->injuries == 1){
        return "Você tem ferimentos leves";
    }
    else if (this->injuries >= vitality-1){
        return "Você tem ferimentos graves";
    }
    else if (this->injuries == vitality-2){
        return "Você tem ferimentos sérios";
    }
    else{
        return "Você tem ferimentos moderados";
    }
}

bool Actor::isKiller(){
    return killer;
}

void Actor::travelTo(Place* destination){
    current_place = destination;
}

Place* Actor::getPlace(){
    return current_place;
}

void Actor::setKiller(){
    this->killer = true;
}

void Actor::setCostumed(bool wear){
    this->costumed = wear;
}

bool Actor::isCostumed(){
    return costumed;
}

int Actor::getNeed(int need_name){
    return need[need_name];
}

void Actor::setNeed(int need_name, int x){
    need[need_name] = x;
}

void Actor::addNeed(int need_name, int x){
    need[need_name] += x;
}

void Actor::randomSkillLoss(int x){
    int chosen = Dice::single_die(SKILL_NUM) - 1;
    skill[chosen] -= x;
    if (skill[chosen] <= 0){
        skill[chosen] = 1;
    }
}
