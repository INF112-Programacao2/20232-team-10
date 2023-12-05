#include "actor.h"
#include "dice.h"

Actor::Actor(tgui::String name){                 //Construtor
    this->name = name;
    this->alive = true;             
    for (int i = 0; i < SKILL_NUM; i++){    //Inicializacao do valores das skills com 0
        this->skill[i] = 3;
    }
    this->injuries = 0;     //Zera a quantidade de dano
    this->killer = false;
}

Actor::Actor(tgui::String name, int atributes[6]) {
    this->name = name;
    this->alive = true;
    for (int i = 0; i < SKILL_NUM; i++){    //Atualiza os valores da skills para a quantidade de pontos escolhida pelo jogador
        this->skill[i] = atributes[i];
    }
    this->injuries = 0;     //Zera a quantidade de dano
    this->killer = false;
};

void Actor::heal(int x) {               //Funcao para curar
    if (injuries >= 1) injuries--;
}

void Actor::damage(int x) {             //Funcao para sofrer dano
    injuries++;
    if (injuries > skill[ENDURANCE] + 3) {
        die();
    }
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