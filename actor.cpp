#include "actor.h"

#include <string>

Actor::Actor(std::string name){                 //Construtor
    this->name = name;
    this->alive = true;             
    for (int i = 0; i < SKILL_NUM; i++){    //Inicializacao do valores das skills com 0
        this->skill[i] = 0;
    }
    this->hp_max = 10 + this->skill[ENDURANCE];     //Maximo de vida = 10 + pontos de CON
    this->hp = this->hp_max;                    //Inicializando a vida do jogador como maximo
}

Actor::Actor(std::string name, int atributes[6]) {
    this->name = name;
    this->alive = true;
    for (int i = 0; i < SKILL_NUM; i++){    //Atualiza os valores da skills para a quantidade de pontos escolhida pelo jogador
        this->skill[i] = atributes[i];
    }
};

void Actor::heal(int x) {               //Funcao para curar
    this->hp += x;                      //Vida do jogador += a quantidade de cura
    if (this->hp > this->hp_max) {      //Se essa cura vai ultrapassar a quantidade de vida maximo
        this->hp = this->hp_max;        //A vida do jogador vai ser igual a quantiadade de vida maxima
    }
}

void Actor::damage(int x) {             //Funcao para sofrer dano
    if (x > 0){                         //Se a quantidade de dano nao for negativo
        this->hp -= x;                  //Vida do jogador -+ a quantidade de dano
        if (this->hp <= 0) {            //Se sofrendo esse dano vai zerar a quantidade de vida do jogador
            die();                      //O jogador morre
        }
    }
}

std::string Actor::getName(){
    return this->name;
}

void Actor::die() {         //Funcao para morte do jogador
    this->alive = false;    //Booleano de estado de vida vira falso
}

int Actor::getSkill(unsigned int s){
    return this->skill[s];
}

int Actor::get_hp(){
    return hp;
}