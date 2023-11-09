#ifndef V_ACTIONS
#define V_ACTIONS

#include "actor.h"
#include "player.h"

class Action {
    protected:
        Actor *actor;

    public:
        Action(Actor *actor);
        virtual void execute() = 0;
};

class TargetedAction : public Action {
    protected:
        Actor *target;

    public:
        TargetedAction(Actor *actor, Actor *target);
};

class WorkOnProjectAction : public Action {
    public:
        WorkOnProjectAction(Actor *actor);
        virtual void execute() override;
};

class StudyAction : public Action {
    public:
        StudyAction(Actor *actor);
        virtual void execute() override;
};

class DamageAction : public TargetedAction {
    public:
        DamageAction(Actor *actor, Actor *target);
        virtual void execute() override;
};



#endif