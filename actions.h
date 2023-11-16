#ifndef V_ACTIONS
#define V_ACTIONS

#include "actor.h"
#include "player.h"

class Action {                          //Classe para acoes sem alvo
    protected:
        Actor *actor;                   //Quem vai executar a acao

    public:
        Action(Actor *actor);           //Construtor
        virtual void execute() = 0;     //Funcao para execucao da acao
};

class TargetedAction : public Action {                  //Classe para acoes com alvo (classe filha da classe Action)
    protected:
        Actor *target;                                  //Alvo da acao

    public:
        TargetedAction(Actor *actor, Actor *target);    //Construtor
};

class WorkOnProjectAction : public Action {     //Classe para a acao de trabalhar no projeto (herda da classe Action, pois nao possui alvo)
    public:
        WorkOnProjectAction(Actor *actor);      //Construtor
        virtual void execute() override;        //Funcao para execucacao da acao
};

class StudyAction : public Action {             //Classe para a acao de estudar
    public:
        StudyAction(Actor *actor);              
        virtual void execute() override;
};

class DamageAction : public TargetedAction {        //Classe para a acao de causar dano (herda da classe TargetedAction, pois possui alvo)
    public:
        DamageAction(Actor *actor, Actor *target);  
        virtual void execute() override;            
};

class HealAction : public TargetedAction {          //Classe para a acao de curar
    public:
        HealAction(Actor *actor, Actor *target);
        virtual void execute() override;
};

#endif