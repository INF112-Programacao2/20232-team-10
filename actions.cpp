#include "actions.h"
#include <iostream>

//Construtores para as classes de acoes
Action::Action(Actor *actor): actor(actor){}

bool Action::possible(){
    return true;
}

TargetedAction::TargetedAction(Actor *actor, Actor *target): Action(actor), target(target){
    resultsText = actor->getName() + " atacou " + target->getName() + "\n";
}

WorkOnProjectAction::WorkOnProjectAction(Actor *actor): Action(actor){}

DamageAction::DamageAction(Actor *actor, Actor *target): TargetedAction(actor, target){}

StudyAction::StudyAction(Actor *actor): Action(actor){}

HealAction::HealAction(Actor *actor, Actor *target) : TargetedAction(actor, target) {}

//Funcoes de execucao para as respectivas acoes
void DamageAction::execute() {              
    int damagequant = actor->getSkill("STR") - target->getSkill("CON");                                         //Quantidade de dano = pontos de STR do actor - pontos de CON do alvo
    target->damage(damagequant);                                                                                //Chama a funcao de causar dano da classe Actor
    std::cout << actor->getName() << " deu " << damagequant << " de dano em " << target->getName() << "\n";     
}

bool DamageAction::possible(){
    return true;
}

void WorkOnProjectAction::execute() {
    actor->workOnProject(actor->getSkill("INT"));                       //Chama a funcao de trabalhor no projeto da classe Actor, com os pontos de INT do jogador como parametro
    std::cout << actor->getName() << " trabalhou no seu projeto.\n";    
}

bool WorkOnProjectAction::possible(){
    return true;
}

void StudyAction::execute() {
    actor->study(actor->getSkill("WIS"));                           //Chama a funcao de estudar da classe Actor, com os pontos de WIS do jogador como parametro
    std::cout << actor->getName() << " estudou para a prova.\n";
}

void HealAction::execute() {
    target->heal(actor->getSkill("WIS"));                                           //Chama a funcao de curar da classe Actor, com os pontos de WIS do jogador como parametro
    std::cout << actor->getName() << " curou " << target->getName() << "\n";
}
