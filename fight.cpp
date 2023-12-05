#include "fight.h"
#include "dice.h"

FightAction::FightAction(Actor *actor, Actor *target) : actor(actor), target(target){
    actionText = "Ação base";
    weight = 0;
    id = -1;
};

bool FightAction::possible(){
    return true;
}

tgui::String FightAction::getText(){
    return actionText;
}

int FightAction::getID(){
    return id;
}

int FightAction::getWeight(){
    return weight;
}

FightAction* FightAction::FightActionByID(int id, Actor *actor, Actor *target){
    if (id == 0){
        return new FA_Punch(actor, target);
    }
    if (id == 1){
        return new FA_KnifeSlash(actor, target);
    }
    return nullptr;
}

FA_Punch::FA_Punch(Actor *actor, Actor *target) : FightAction(actor, target){
    weight = 3;
    id = 0;
}

void FA_Punch::execute(){
    if (actor->skillRoll(FITNESS) > target->skillRoll(AGILITY) && !target->skillCheck(ENDURANCE, 20)){
        target->damage();
        actionText = actor->getName() + " acertou um soco em " + target->getName();
    }
    else{
        actionText = actor->getName() + " errou um soco em " + target->getName();
    }
}

FA_KnifeSlash::FA_KnifeSlash(Actor *actor, Actor *target) : FightAction(actor, target){
    weight = 8;
    id = 1;
}

void FA_KnifeSlash::execute(){
    if (actor->skillRoll(FITNESS) > target->skillRoll(AGILITY)){
        target->damage();
        actionText = actor->getName() + " esfaqueou " + target->getName();
    }
    else{
        actionText = target->getName() + " desviou de uma facada de " + actor->getName();
    }
}

bool FA_KnifeSlash::possible(){
    return actor->isKiller();
}

void Fight::addFighter(Actor *fighter, int alignment){
    fighters.push_back(fighter);
    alignments[fighter] = alignment;
}

void Fight::removeFighter(Actor *fighter){
    for (int i = 0; i < fighters.size(); i++){
        if (fighters[i] == fighter){
            fighters.erase(fighters.begin() + i);
            i--;
        }
    }
}

Actor* Fight::getTarget(Actor *actor){
    int hostiles = 0;
    for (int i = 0; i < fighters.size(); i++){
        if (alignments[fighters[i]] != alignments[actor]){
            hostiles++;
        }
    }
    if (hostiles == 0){
        return nullptr;
    }
    int chosen = Dice::single_die(hostiles);
    for (int i = 0; i < fighters.size(); i++){
        if (alignments[fighters[i]] != alignments[actor]){
            chosen--;
        }
        if (chosen == 0){
            return fighters[i];
        }
    }
    return nullptr;
}

void Fight::getAction(Actor *actor){
    int total_weight = 0;
    int possible = 0;
    FightAction* fight_action;
    Actor* target = getTarget(actor);
    for (int i = 0; i < FIGHT_ACTION_NUM; i++){
        fight_action = FightAction::FightActionByID(i, actor, target);
        if (fight_action->possible()){
            total_weight += fight_action->getWeight();
            possible++;
        }
        delete fight_action;
    }
    int chosen = Dice::single_die(total_weight);
    for (int i = 0; i < possible; i++){
        fight_action = FightAction::FightActionByID(i, actor, target);
        chosen -= fight_action->getWeight();
        if (chosen <= 0){
            fight_actions.push(FightAction::FightActionByID(i, actor, getTarget(actor)));
            break;
        }
        delete fight_action;
    }
}

void Fight::results(){
    while (!fight_actions.empty()){
        fight_actions.front()->execute();
        fight_log += fight_actions.front()->getText() + "\n";
        delete fight_actions.front();
        fight_actions.pop();
    }
}

void Fight::simulateFight(){
    int maxTime = 10;
    for (int time = 0; time < maxTime; time++){
        for (int i = 0; i < fighters.size(); i++){
            getAction(fighters[i]);
        }
        results();
    }
}

tgui::String Fight::getLog(){
    return fight_log;
}