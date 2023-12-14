#include "../include/fight.h"
#include "../include/dice.h"

FightAction::FightAction(Fight* fight, Actor *actor, Actor *target) : fight(fight), actor(actor), target(target){
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

FightAction* FightAction::FightActionByID(int id, Fight* fight, Actor* actor, Actor* target){
    if (id == FA_PUNCH){
        return new FA_Punch(fight, actor, target);
    }
    if (id == FA_TOPPLE){
        return new FA_Topple(fight, actor, target);
    }/*
    if (id == FA_DODGE){
        return new FA_Dodge(fight, actor, target);
    }
    if (id == FA_LEGENDARYAGILITY){
        return new FA_LegendaryAgility(fight, actor, target);
    }
    if (id == FA_UNTILTHEEND){
        return new FA_UntilTheEnd(fight, actor, target);
    }*/
    if (id == FA_UNSTOPPABLE){
        return new FA_Unstoppable(fight, actor, target);
    }
    if (id == FA_IMPROVISEDWEAPON){
        return new FA_ImprovisedWeapon(fight, actor, target);
    }/*
    if (id == FA_CHEAPTRICK){
        return new FA_CheapTrick(fight, actor, target);
    }
    if (id == FA_QUICKTHINKING){
        return new FA_QuickThinking(fight, actor, target);
    }
    if (id == FA_PATTERNFOUND){
        return new FA_PatternFound(fight, actor, target);
    }
    if (id == FA_PROCEEDINGASIHAVEFORESEEN){
        return new FA_ProceedingAsIHaveForeseen(fight, actor, target);
    }
    if (id == FA_AIMFORTHEWEAKPOINT){
        return new FA_AimForTheWeakPoint(fight, actor, target);
    }
    if (id == FA_GROUPSDOCTOR){
        return new FA_GroupsDoctor(fight, actor, target);
    }*/
    if (id == FA_SCREAM){
        return new FA_Scream(fight, actor, target);
    }/*
    if (id == FA_INSPIRATION){
        return new FA_Inspiration(fight, actor, target);
    }*/
    if (id == FA_KNIFESLASH){
        return new FA_KnifeSlash(fight, actor, target);
    }
    return nullptr;
}

FA_Punch::FA_Punch(Fight* fight, Actor *actor, Actor *target) : FightAction(fight, actor, target){
    weight = actor->getSkill(FITNESS);
    id = 0;
}

void FA_Punch::execute(){
    if (!target->isAlive()){
        return;
    }
    if (actor->skillRoll(FITNESS) > target->skillRoll(AGILITY)){
        actionText = actor->getName() + " acertou um soco em " + target->getName();
        target->damage(actor->skillRoll(FITNESS)/80 + 1);
    }
    else{
        actionText = actor->getName() + " errou um soco em " + target->getName();
    }
}

FA_Topple::FA_Topple(Fight* fight, Actor *actor, Actor *target) : FightAction(fight, actor, target){
    weight = 3;
    id = 0;
}

void FA_Topple::execute(){
    if (!target->isAlive()){
        return;
    }
    if (actor->skillRoll(FITNESS) > target->skillRoll(AGILITY)+20){
        actionText = actor->getName() + " derrubou " + target->getName();
        target->damage(actor->skillRoll(FITNESS)/40 + 1);
    }
    else{
        actionText = target->getName() + " desviou de um empurrão de " + actor->getName();
    }
}

bool FA_Topple::possible(){
    return actor->getSkill(FITNESS) >= 5;
}

FA_Unstoppable::FA_Unstoppable(Fight* fight, Actor *actor, Actor *target) : FightAction(fight, actor, target){
    weight = 3;
    id = 0;
}

void FA_Unstoppable::execute(){
    if (actor->skillCheck(ENDURANCE, 60)){
        actor->heal();
        actionText = actor->getName() + " juntou toda sua força para ignorar seus ferimentos";
    }
    else{
        actionText = actor->getName() + " soltou um suspiro de cansaço";
    }
}

bool FA_Unstoppable::possible(){
    return actor->getSkill(ENDURANCE) >= 5 && actor->getDamageLevel() > 0;
}

FA_ImprovisedWeapon::FA_ImprovisedWeapon(Fight* fight, Actor *actor, Actor *target) : FightAction(fight, actor, target){
    weight = actor->getSkill(LOGIC);
    id = 0;
}

void FA_ImprovisedWeapon::execute(){
    if (!target->isAlive()){
        return;
    }
    if (actor->skillRoll(FITNESS, 50) + actor->skillRoll(LOGIC, 50) > target->skillRoll(AGILITY)+5){
        actionText = actor->getName() + " apunhalou " + target->getName() + " com um lápis apontado";
        target->damage(actor->skillRoll(LOGIC) / 40);
    }
    else{
        actionText = actor->getName() + " ficou 6 segundos procurando um lápis";
    }
}

FA_Scream::FA_Scream(Fight* fight, Actor *actor, Actor *target) : FightAction(fight, actor, target){
    weight = actor->getSkill(COMMUNICATION);
    id = 0;
}

void FA_Scream::execute(){
    if (actor->skillRoll(COMMUNICATION)){
        fight->addMaxTime(-actor->skillRoll(COMMUNICATION)/25 -1);
    }
    actionText = actor->getName() + " gritou por ajuda";
}

bool FA_Scream::possible(){
    return fight->get_alignment(actor) == ALIGNMENT_VICTIM;
}

FA_KnifeSlash::FA_KnifeSlash(Fight* fight, Actor *actor, Actor *target) : FightAction(fight, actor, target){
    weight = 8;
    id = 1;
}

void FA_KnifeSlash::execute(){
    if (!target->isAlive()){
        return;
    }
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
    if (alignment == ALIGNMENT_VICTIM){
        maxTime -= fighter->skillRoll(COMMUNICATION) / 25;
    }
}

void Fight::addMaxTime(int time){
    maxTime += time;
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
    int chosen = Dice::single_die(hostiles)-1;
    for (int i = 0; i < fighters.size(); i++){
        if (chosen == 0 && alignments[fighters[i]] != alignments[actor]){
            return fighters[i];
        }
        if (alignments[fighters[i]] != alignments[actor]){
            chosen--;
        }
    }
    return nullptr;
}

bool Fight::getAction(Actor *actor){
    int total_weight = 0;
    int possible = 0;
    FightAction* fight_action;
    Actor* target = getTarget(actor);
    if (target == nullptr){
        return false;
    }
    for (int i = 0; i < FIGHT_ACTION_NUM; i++){
        fight_action = FightAction::FightActionByID(i, this, actor, target);
        if (fight_action->possible()){
            total_weight += fight_action->getWeight();
            possible++;
        }
        delete fight_action;
    }
    int chosen = Dice::single_die(total_weight)-1;
    for (int i = 0; i < possible; i++){
        fight_action = FightAction::FightActionByID(i, this, actor, target);
        if (fight_action->possible()){
            chosen -= fight_action->getWeight();
            if (chosen <= 0){
                fight_actions.push(FightAction::FightActionByID(i, this, actor, target));
                break;
            }
        }
        delete fight_action;
    }
    return true;
}

int Fight::get_alignment(Actor* fighter){
    return alignments[fighter];
}

void Fight::results(){
    while (!fight_actions.empty()){
        fight_actions.front()->execute();
        fight_log += fight_actions.front()->getText() + "\n";
        delete fight_actions.front();
        fight_actions.pop();
    }
    for (int i = 0; i < fighters.size(); i++){
        if (!fighters[i]->isAlive()){
            fight_log += fighters[i]->getName() + " morreu.\n";
            removeFighter(fighters[i]);
            i--;
        }
    }
}

int Fight::simulateFight(){
    for (int time = 0; time < maxTime; time++){
        for (int i = 0; i < fighters.size(); i++){
            if (!getAction(fighters[i])){
                if (alignments[fighters[i]] == ALIGNMENT_VICTIM){
                    return RESULT_AGRESSOR_DEAD;
                }
                else{
                    return RESULT_VICTIM_DEAD;
                }
            }
        }
        results();

    }
    return RESULT_TIME_OUT;
}

tgui::String Fight::getLog(){
    return fight_log;
}
