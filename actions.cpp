#include "actions.h"

Action::Action(Actor *actor): actor(actor){}

TargetedAction::TargetedAction(Actor *actor, Actor *target): Action(actor), target(target){}

WorkOnProjectAction::WorkOnProjectAction(Actor *actor): Action(actor){}

DamageAction::DamageAction(Actor *actor, Actor *target): TargetedAction(actor, target){}

StudyAction::StudyAction(Actor *actor): Action(actor){}

void DamageAction::execute() {
    target->damage(actor->getSkill("STR"));
}

void WorkOnProjectAction::execute() {
    actor->workOnProject(actor->getSkill("INT"));
}

void StudyAction::execute() {
    actor->study(actor->getSkill("WIS"));
}