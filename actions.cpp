#include "actions.h"
#include <iostream>

Action::Action(Actor *actor): actor(actor){}

TargetedAction::TargetedAction(Actor *actor, Actor *target): Action(actor), target(target){}

WorkOnProjectAction::WorkOnProjectAction(Actor *actor): Action(actor){}

DamageAction::DamageAction(Actor *actor, Actor *target): TargetedAction(actor, target){}

StudyAction::StudyAction(Actor *actor): Action(actor){}

HealAction::HealAction(Actor *actor, Actor *target) : TargetedAction(actor, target) {}

void DamageAction::execute() {
    int damagequant = actor->getSkill("STR") - target->getSkill("CON");
    target->damage(damagequant);
    std::cout << actor->getName() << " deu " << damagequant << " de dano em " << target->getName() << "\n";
}

void WorkOnProjectAction::execute() {
    actor->workOnProject(actor->getSkill("INT"));
    std::cout << actor->getName() << " trabalhou no seu projeto.\n";
}

void StudyAction::execute() {
    actor->study(actor->getSkill("WIS"));
    std::cout << actor->getName() << " estudou para a prova.\n";
}

void HealAction::execute() {
    target->heal(actor->getSkill("WIS"));
        std::cout << actor->getName() << " curou " << target->getName() << "\n";
}
