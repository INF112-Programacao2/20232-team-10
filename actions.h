#ifndef V_ACTIONS
#define V_ACTIONS

#include <vector>
#include "actor.h"
#include "player.h"

const int ACTION_NUM = 4;

class Action {                          //Classe para acoes sem alvo
    protected:
        Actor *actor;                   //Quem vai executar a acao
        tgui::String name;
        tgui::String actorText;          //Texto que aparecerá para o agente no fim do turno 
        int id;
        bool targeted;

    public:
        static std::vector<Action*> game_actions;
        static Action* ActionByID(int id, Actor *actor = nullptr, Actor *target = nullptr);
        static void instantiate_actions();
        Action(Actor *actor);           //Construtor
        virtual void execute() = 0;     //Funcao para execucao da acao
        virtual bool possible();
        bool isTargeted();
        int get_id();
        virtual tgui::String getDescription();
};

class TargetedAction : public Action {                  //Classe para acoes com alvo (classe filha da classe Action)
    protected:
        Actor *target;                                  //Alvo da acao
        tgui::String targetText;                         //Texto que aparecerá para o alvo no fim da ação

    public:
        TargetedAction(Actor *actor, Actor *target);    //Construtor
        virtual tgui::String getDescription() override;
};

class WorkOnProjectAction : public Action {     //Classe para a acao de trabalhar no projeto (herda da classe Action, pois nao possui alvo)
    public:
        WorkOnProjectAction(Actor *actor);      //Construtor
        virtual void execute() override;        //Funcao para execucacao da acao
        //virtual bool possible() override;
        virtual tgui::String getDescription() override;
};

class StudyAction : public Action {             //Classe para a acao de estudar
    public:
        StudyAction(Actor *actor);              
        virtual void execute() override;
        //virtual bool possible() override;
        virtual tgui::String getDescription() override;
};

class DamageAction : public TargetedAction {        //Classe para a acao de causar dano (herda da classe TargetedAction, pois possui alvo)
    public:
        DamageAction(Actor *actor, Actor *target);  
        virtual void execute() override; 
        //virtual bool possible() override;          
        virtual tgui::String getDescription() override; 
};

class HealAction : public TargetedAction {          //Classe para a acao de curar
    public:
        HealAction(Actor *actor, Actor *target);
        virtual void execute() override;
        //virtual bool possible() override;
        virtual tgui::String getDescription() override;
};

#endif