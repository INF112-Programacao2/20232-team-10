#include "actions.h"
#include "dice.h"
#include "fight.h"

//Construtores para as classes de acoes

std::vector<Action*> Action::game_actions;

Action::Action(Actor *actor): actor(actor){
    this->id = -2;
    this->targeted = false;
    this->description = "Action";
}

Actor* Action::getActor(){
    return actor;
}

tgui::String Action::getResultsText(){
    return resultsText;
}

void Action::updateResultsText(){
    this->actor->resultsText += resultsText + "\n";
}

TargetedAction::TargetedAction(Actor *actor, Actor *target): Action(actor), target(target){
    this->id = -1;
    this->targeted = true;
    this->description = "Targeted Action";
}

Actor* TargetedAction::getTarget(){
    return target;
}

void TargetedAction::updateResultsText(){
    this->actor->resultsText += resultsText + "\n";
    this->target->resultsText += resultsText + "\n";
}

WorkOnProjectAction::WorkOnProjectAction(Actor *actor): Action(actor){
    this->id = 0;
    this->description = "Trabalhar no projeto";
}

StartFightAction::StartFightAction(Actor *actor, Actor *target): TargetedAction(actor, target){
    this->id = 1;
    this->description = "Atacar alvo";
}

StudyAction::StudyAction(Actor *actor): Action(actor){
    this->id = 2;
    this->description = "Estudar";
}

HealAction::HealAction(Actor *actor, Actor *target) : TargetedAction(actor, target) {
    this->id = 3;
    this->description = "Curar alvo";
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
    return description;
}

//Funcoes de execucao para as respectivas acoes
void StartFightAction::execute() {              
    Fight fight;
    fight.addFighter(actor, 1);
    fight.addFighter(target, 0);
    fight.simulateFight();
    this->resultsText = fight.getLog();
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
        resultsText = actor->getName() + " curou alguns ferimentos de " + target->getName();
    }
    else{
        resultsText = actor->getName() + " não conseguiu curar os ferimentos de " + target->getName();
    }
}

void Action::instantiateActions(){
    for (int i = 0; i < ACTION_NUM; i++){
        game_actions.push_back(ActionByID(i));
    }
}

Action* Action::ActionByID(int id, Actor *actor, Actor *target){
    if(id == 0){
        return new WorkOnProjectAction(actor);
    }
    if(id == 1){
        return new StartFightAction(actor, target);
    }
    if(id == 2){
        return new StudyAction(actor);
    }
    if(id == 3){
        return new HealAction(actor, target);
    }
    return nullptr;
}