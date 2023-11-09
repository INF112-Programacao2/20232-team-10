#include "actions.h"

Action::Action(Actor *actor): _actor(actor){}

TargetedAction::TargetedAction(Actor *actor, Actor *target): Action(actor), _target(target){}

WorkOnProjectAction::WorkOnProjectAction(Actor *actor): Action(actor){}

DamageAction::DamageAction(Actor *actor, Actor *target): TargetedAction(actor, target){}

StudyAction::StudyAction(Actor *actor): Action(actor){}

void DamageAction::execute() {
    _target->damage(_actor->get_STR());
}

void WorkOnProjectAction::execute() {
    _actor->work_on_project(_actor->get_INT());
}

void StudyAction::execute() {
    _actor->study(_actor->get_WIS());
}