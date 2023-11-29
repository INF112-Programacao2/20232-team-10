#include "actor.h"
#include "dice.h"

Actor::Actor(tgui::String name){                 //Construtor
    this->name = name;
    this->alive = true;             
    for (int i = 0; i < SKILL_NUM; i++){    //Inicializacao do valores das skills com 0
        this->skill[i] = 0;
    }
    this->injuries = 0;     //Zera a quantidade de dano
}

Actor::Actor(tgui::String name, int atributes[6]) {
    this->name = name;
    this->alive = true;
    for (int i = 0; i < SKILL_NUM; i++){    //Atualiza os valores da skills para a quantidade de pontos escolhida pelo jogador
        this->skill[i] = atributes[i];
    }
    this->injuries = 0;     //Zera a quantidade de dano
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

tgui::String Actor::getName(){
    return this->name;
}

void Actor::die() {         //Funcao para morte do jogador
    this->alive = false;    //Booleano de estado de vida vira falso
}

int Actor::getSkill(unsigned int s){
    return this->skill[s];
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