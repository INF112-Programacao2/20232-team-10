#include "actions.h"
#include <iostream>

//Construtores para as classes de acoes

std::vector<Action*> Action::game_actions;

Action::Action(Actor *actor): actor(actor){}

TargetedAction::TargetedAction(Actor *actor, Actor *target): Action(actor), target(target){}

WorkOnProjectAction::WorkOnProjectAction(Actor *actor): Action(actor){}

DamageAction::DamageAction(Actor *actor, Actor *target): TargetedAction(actor, target){}

StudyAction::StudyAction(Actor *actor): Action(actor){}

HealAction::HealAction(Actor *actor, Actor *target) : TargetedAction(actor, target) {}

bool Action::possible(){
    return true;
}

bool Action::isTargeted(){
    return false;
}

bool TargetedAction::isTargeted(){
    return true;
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
    resultsText = actor->getName() + " deu " + std::to_string(damagequant) + " de dano em " + target->getName() + "\n";     
}

bool DamageAction::possible(){
    return true;
}

void WorkOnProjectAction::execute() {
    actor->workOnProject(actor->getSkill(THINKING));                       //Chama a funcao de trabalhor no projeto da classe Actor, com os pontos de INT do jogador como parametro
    std::cout << actor->getName() << " trabalhou no seu projeto.\n";    
}

bool WorkOnProjectAction::possible(){
    return true;
}

void StudyAction::execute() {
    actor->study(actor->getSkill(CHARISMA));                           //Chama a funcao de estudar da classe Actor, com os pontos de WIS do jogador como parametro
    std::cout << actor->getName() << " estudou para a prova.\n";
}

void HealAction::execute() {
    target->heal(actor->getSkill(FIRST_AID));                                           //Chama a funcao de curar da classe Actor, com os pontos de WIS do jogador como parametro
    std::cout << actor->getName() << " curou " << target->getName() << "\n";
}

void Action::instantiate_actions(){
    DamageAction* damage_action = new DamageAction(nullptr, nullptr);
    WorkOnProjectAction* work_on_project_action = new WorkOnProjectAction(nullptr);
    StudyAction* study_action = new StudyAction(nullptr);
    HealAction* heal_action = new HealAction(nullptr, nullptr);
    game_actions.push_back(damage_action);
    game_actions.push_back(work_on_project_action);
    game_actions.push_back(study_action);
    game_actions.push_back(heal_action);
}