#ifndef V_ACTIONS
#define V_ACTIONS
#include "actor.h"
#include "player.h"

class Action {
 protected:
  Actor *_actor;

 public:
  Action(Actor *actor);
  virtual void execute() = 0;
};

class TargetedAction : public Action {
 protected:
  Actor *_target;

 public:
  TargetedAction(Actor *actor, Actor *target);
};

class DamageAction : public TargetedAction {
 public:
  virtual void execute() override;
};

class WorkOnProjectAction : public Action {
 public:
  void execute(Player player);
};
#endif