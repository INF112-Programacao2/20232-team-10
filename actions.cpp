#include "actions.h"
#include "dice.h"

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

tgui::String Action::getDescription(){
    return "Action";
}

tgui::String TargetedAction::getDescription(){
    return "Targeted Action";
}

tgui::String WorkOnProjectAction::getDescription(){
    return "Trabalhar no projeto";
}

tgui::String StudyAction::getDescription(){
    return "Estudar";
}

tgui::String DamageAction::getDescription(){
    return "Atacar alvo";
}

tgui::String HealAction::getDescription(){
    return "Curar alvo";
}



//Funcoes de execucao para as respectivas acoes
void DamageAction::execute() {              
    target->damage();                                                                                //Chama a funcao de causar dano da classe Actor
}

void WorkOnProjectAction::execute() {
    int work = actor->skillRoll(LOGIC, 30);
    actor->workOnProject(work);                       //Chama a funcao de trabalhor no projeto da classe Actor, com os pontos de INT do jogador como parametro
}

void StudyAction::execute() {
    int study = actor->skillRoll(COMMUNICATION, 30);
    actor->study(study);                           //Chama a funcao de estudar da classe Actor, com os pontos de WIS do jogador como parametro
}

void HealAction::execute() {
    if (actor->skillCheck(FIRST_AID, 60)){
        target->heal();                                           //Chama a funcao de curar da classe Actor, com os pontos de WIS do jogador como parametro
        actorText = "Você curou alguns ferimentos de " + target->getName();
        targetText = actor->getName() + " curou alguns dos seus ferimentos";
    }
    else{
        actorText = "Você não consegui curar os ferimentos de " + target->getName();
        targetText = actor->getName() + " tentou curar alguns dos seus ferimentos, mas falhou";
    }
}

void Action::instantiate_actions(){
    for (int i = 0; i < ACTION_NUM; i++){
        game_actions.push_back(ActionByID(i));
    }
}

Action* Action::ActionByID(int id, Actor *actor, Actor *target){
    if(id == 0){
        return new WorkOnProjectAction(actor);
    }
    if(id == 1){
        return new DamageAction(actor, target);
    }
    if(id == 2){
        return new StudyAction(actor);
    }
    if(id == 3){
        return new HealAction(actor, target);
    }
    return nullptr;
}