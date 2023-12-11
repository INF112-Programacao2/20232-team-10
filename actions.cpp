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
    this->id = ACTION_WORK_ON_PROJECT;
    this->description = "Trabalhar no projeto";
}

StartFightAction::StartFightAction(Actor *actor, Actor *target): TargetedAction(actor, target){
    this->id = ACTION_START_FIGHT;
    this->description = "Atacar alvo";
}

StudyAction::StudyAction(Actor *actor): Action(actor){
    this->id = ACTION_STUDY;
    this->description = "Estudar";
}

HealAction::HealAction(Actor *actor, Actor *target) : TargetedAction(actor, target) {
    this->id = ACTION_HEAL;
    this->description = "Curar alvo";
}

LunchAction::LunchAction(Actor *actor): Action(actor){
    this->id = ACTION_LUNCH;
    this->description = "Almoçar";
}

VideogamesAction::VideogamesAction(Actor *actor): Action(actor){
    this->id = ACTION_VIDEOGAMES;
    this->description = "Jogar videogames";
}

RitarAction::RitarAction(Actor *actor): Action(actor){
    this->id = ACTION_RITA;
    this->description = "Ritar";
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
    if (actor->isKiller()){
        actor->setCostumed(true);
    }  
    Fight fight;
    int result;
    fight.addFighter(actor, (actor->isKiller() ? ALIGNMENT_KILLER : ALIGNMENT_AGRESSOR));
    fight.addFighter(target, ALIGNMENT_VICTIM);
    this->resultsText = actor->getName() + " atacou " + target->getName() + "!\n\n";
    result = fight.simulateFight();
    this->resultsText += fight.getLog();
    if (result == RESULT_TIME_OUT){
        this->resultsText += "\n" + actor->getName() + " foge enquanto a ajuda chega";
    }
    if (result == RESULT_VICTIM_DEAD || result == RESULT_AGRESSOR_ESCAPED){
        this->resultsText += "\n" + actor->getName() + " foge";
    }
    actor->setCostumed(false);
}

void WorkOnProjectAction::execute() {
    int work = actor->skillRoll(LOGIC, 30 + actor->getPlace()->getBonus(id));
    actor->workOnProject(work);                       //Chama a funcao de trabalhor no projeto da classe Actor, com os pontos de INT do jogador como parametro
    resultsText = "Você trabalhou no seu projeto final";
}

void StudyAction::execute() {
    int study = actor->skillRoll(COMMUNICATION, 30 + actor->getPlace()->getBonus(id));
    actor->study(study);                           //Chama a funcao de estudar da classe Actor, com os pontos de WIS do jogador como parametro
    resultsText = "Você estudou para as provas";
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

void LunchAction::execute() {
    actor->setNeed(NEED_HUNGER, 5);                           //Preenche a necessidade de comida
    resultsText = "Você almoçou";
}

void VideogamesAction::execute() {
    actor->addNeed(NEED_FUN, 3);                           //Melhora a necessidade de diversão (sem limite máximo)
    resultsText = "Você jogou videogames";
}

void RitarAction::execute() {
    actor->setNeed(NEED_FUN, 5);                           //Preenche a necessidade de diversão
    resultsText = "Você ritou";
}

bool LunchAction::possible(){
    return actor->getPlace()->getName() == "RU";
}

bool RitarAction::possible(){
    return actor->getPlace()->getName() == "Rita";
}

void Action::instantiateActions(){
    for (int i = 0; i < ACTIONS_NUM; i++){
        game_actions.push_back(ActionByID(i));
    }
}

Action* Action::ActionByID(int id, Actor *actor, Actor *target){
    if(id == ACTION_WORK_ON_PROJECT){
        return new WorkOnProjectAction(actor);
    }
    if(id == ACTION_START_FIGHT){
        return new StartFightAction(actor, target);
    }
    if(id == ACTION_STUDY){
        return new StudyAction(actor);
    }
    if(id == ACTION_HEAL){
        return new HealAction(actor, target);
    }
    if(id == ACTION_LUNCH){
        return new LunchAction(actor);
    }
    if(id == ACTION_VIDEOGAMES){
        return new VideogamesAction(actor);
    }
    if(id == ACTION_RITA){
        return new RitarAction(actor);
    }
    
    return nullptr;
}