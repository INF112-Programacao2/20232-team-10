#include "actions.h"
#include <iostream>

//Construtores para as classes de acoes

std::vector<Action*> Action::game_actions;

Action::Action(Actor *actor): actor(actor){
    this->id = 0;
    this->targeted = false;
}

TargetedAction::TargetedAction(Actor *actor, Actor *target): Action(actor), target(target){
    this->id = 1;
    this->targeted = true;
}

WorkOnProjectAction::WorkOnProjectAction(Actor *actor): Action(actor){
    this->id = 2;
}

DamageAction::DamageAction(Actor *actor, Actor *target): TargetedAction(actor, target){
    this->id = 3;
}

StudyAction::StudyAction(Actor *actor): Action(actor){
    this->id = 4;
}

HealAction::HealAction(Actor *actor, Actor *target) : TargetedAction(actor, target) {
    this->id = 5;
}

bool Action::possible(){
    return true;
}

int Action::get_id(){
    return id;
}

bool Action::isTargeted(){
    return this->targeted;
}

std::string Action::getDescription(){
    return "Action";
}

std::string TargetedAction::getDescription(){
    return "Targeted Action";
}

std::string WorkOnProjectAction::getDescription(){
    return "Trabalhar no projeto";
}

std::string StudyAction::getDescription(){
    return "Estudar";
}

std::string DamageAction::getDescription(){
    return "Atacar alvo";
}

std::string HealAction::getDescription(){
    return "Curar alvo";
}



//Funcoes de execucao para as respectivas acoes
void DamageAction::execute() {              
    int damagequant = actor->getSkill(FITNESS) - target->getSkill(ENDURANCE);                                         //Quantidade de dano = pontos de STR do actor - pontos de CON do alvo
    target->damage(damagequant);                                                                                //Chama a funcao de causar dano da classe Actor
}

void WorkOnProjectAction::execute() {
    actor->workOnProject(actor->getSkill(THINKING));                       //Chama a funcao de trabalhor no projeto da classe Actor, com os pontos de INT do jogador como parametro
}

void StudyAction::execute() {
    actor->study(actor->getSkill(CHARISMA));                           //Chama a funcao de estudar da classe Actor, com os pontos de WIS do jogador como parametro
}

void HealAction::execute() {
    target->heal(actor->getSkill(FIRST_AID));                                           //Chama a funcao de curar da classe Actor, com os pontos de WIS do jogador como parametro
}

void Action::instantiate_actions(){
    for (int i = 0; i < ACTION_NUM; i++){
        game_actions.push_back(ActionByID(i));
    }
}

Action* Action::ActionByID(int id, Actor *actor, Actor *target){
    if(id == 0){
        WorkOnProjectAction* work_on_project_action = new WorkOnProjectAction(actor);
        return work_on_project_action;
    }
    if(id == 1){
        DamageAction* damage_action = new DamageAction(actor, target);
        return damage_action;
    }
    if(id == 2){
        StudyAction* study_action = new StudyAction(actor);
        return study_action;
    }
    if(id == 3){
        HealAction* heal_action = new HealAction(actor, target);
        return heal_action;
    }
    return nullptr;
}