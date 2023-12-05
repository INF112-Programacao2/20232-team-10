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
        tgui::String resultsText;          //Texto que aparecerá para o agente no fim do turno 
        tgui::String description;
        int id;
        bool targeted;

    public:
        static std::vector<Action*> game_actions;
        static Action* ActionByID(int id, Actor *actor = nullptr, Actor *target = nullptr);
        static void instantiateActions();
        Action(Actor *actor);           //Construtor
        virtual void execute() = 0;     //Funcao para execucao da acao
        virtual bool possible();
        bool isTargeted();
        Actor *getActor();
        int get_id();
        tgui::String getDescription();
        tgui::String getResultsText();
        virtual void updateResultsText();
};

class TargetedAction : public Action {                  //Classe para acoes com alvo (classe filha da classe Action)
    protected:
        Actor *target;                                  //Alvo da acao
    public:
        TargetedAction(Actor *actor, Actor *target);    //Construtor
        Actor *getTarget();
        virtual void updateResultsText() override;
};

class WorkOnProjectAction : public Action {     //Classe para a acao de trabalhar no projeto (herda da classe Action, pois nao possui alvo)
    public:
        WorkOnProjectAction(Actor *actor);      //Construtor
        virtual void execute() override;        //Funcao para execucacao da acao
        //virtual bool possible() override;
};

class StudyAction : public Action {             //Classe para a acao de estudar
    public:
        StudyAction(Actor *actor);              
        virtual void execute() override;
        //virtual bool possible() override;
};

class StartFightAction : public TargetedAction {        //Classe para a acao de iniciar combate (herda da classe TargetedAction, pois possui alvo)
    public:
        StartFightAction(Actor *actor, Actor *target);  
        virtual void execute() override; 
        //virtual bool possible() override;
};

class HealAction : public TargetedAction {          //Classe para a acao de curar
    public:
        HealAction(Actor *actor, Actor *target);
        virtual void execute() override;
        //virtual bool possible() override;
};

#endif