#ifndef V_FIGHT_ACTIONS
#define V_FIGHT_ACTIONS

#include "player.h"

const int FIGHT_ACTION_NUM = 6;

enum fight_actions{
    FA_PUNCH,
    FA_TOPPLE,
    //FA_DODGE
    //FA_LEGENDARYAGILITY
    //FA_UNTILTHEEND
    FA_UNSTOPPABLE,
    FA_IMPROVISEDWEAPON,
    //FA_CHEAPTRICK,
    //FA_QUICKTHINKING,
    //FA_PATTERNFOUND,
    //FA_PROCEEDINGASIHAVEFORESEEN,
    //FA_AIMFORTHEWEAKPOINT,
    //FA_GROUPSDOCTOR,
    FA_SCREAM,
    //FA_INSPIRATION,
    FA_KNIFESLASH,
};

class Fight;

class FightAction{
    protected:
        Fight* fight;
        Actor *actor;
        Actor *target;
        tgui::String actionText;
        int weight;
        int id;
    public:
        FightAction(Fight* fight, Actor *actor, Actor *target=nullptr);
        static FightAction *FightActionByID(int id, Fight* fight, Actor* actor = nullptr, Actor* target = nullptr);
        tgui::String getText();
        int getID();
        int getWeight();
        virtual void execute() = 0;
        virtual bool possible();
};

class FA_Punch : public FightAction{
    public:
        FA_Punch(Fight* fight, Actor *actor, Actor *target);
        virtual void execute() override;
};

class FA_Topple : public FightAction{
    public:
        FA_Topple(Fight* fight, Actor *actor, Actor *target);
        virtual void execute() override;
        virtual bool possible() override;
};

/*
class FA_Dodge : public FightAction{
    public:
        FA_Dodge(Fight* fight, Actor *actor, Actor *target);
        virtual void execute() override;
};

class FA_LegendaryAgility : public FightAction{
    public:
        FA_LegendaryAgility(Fight* fight, Actor *actor, Actor *target);
        virtual void execute() override;
        virtual bool possible() override;
};

class FA_UntilTheEnd : public FightAction{
    public:
        FA_UntilTheEnd(Fight* fight, Actor *actor, Actor *target);
        virtual void execute() override;
        virtual bool possible() override;
};
*/

class FA_Unstoppable : public FightAction{
    public:
        FA_Unstoppable(Fight* fight, Actor *actor, Actor *target);
        virtual void execute() override;
        virtual bool possible() override;
};

class FA_ImprovisedWeapon : public FightAction{
    public:
        FA_ImprovisedWeapon(Fight* fight, Actor *actor, Actor *target);
        virtual void execute() override;
};
/*
class FA_CheapTrick : public FightAction{
    public:
        FA_CheapTrick(Fight* fight, Actor *actor, Actor *target);
        virtual void execute() override;
        virtual bool possible() override;
};

class FA_QuickThinking : public FightAction{
    public:
        FA_QuickThinking(Fight* fight, Actor *actor, Actor *target);
        virtual void execute() override;
        virtual bool possible() override;
};

class FA_PatternFound : public FightAction{
    public:
        FA_PatternFound(Fight* fight, Actor *actor, Actor *target);
        virtual void execute() override;
        virtual bool possible() override;
};

class FA_ProceedingAsIHaveForeseen : public FightAction{
    public:
        FA_ProceedingAsIHaveForeseen(Fight* fight, Actor *actor, Actor *target);
        virtual void execute() override;
        virtual bool possible() override;
};

class FA_AimForTheWeakPoint : public FightAction{
    public:
        FA_AimForTheWeakPoint(Fight* fight, Actor *actor, Actor *target);
        virtual void execute() override;
        virtual bool possible() override;
};

class FA_GroupsDoctor : public FightAction{
    public:
        FA_GroupsDoctor(Fight* fight, Actor *actor, Actor *target);
        virtual void execute() override;
        virtual bool possible() override;
};*/

class FA_Scream : public FightAction{
    public:
        FA_Scream(Fight* fight, Actor *actor, Actor *target);
        virtual void execute() override;
        virtual bool possible() override;
};

/*
class FA_Inspiration : public FightAction{
    public:
        FA_Inspiration(Fight* fight, Actor *actor, Actor *target);
        virtual void execute() override;
        virtual bool possible() override;
};*/

class FA_KnifeSlash : public FightAction{
    public:
        FA_KnifeSlash(Fight* fight, Actor *actor, Actor *target);
        virtual void execute() override;
        virtual bool possible() override;
};

#endif

#ifndef V_FIGHT
#define V_FIGHT

#include <vector>
#include <queue>
#include <map>
#include "player.h"

enum alignments {
    ALIGNMENT_VICTIM,
    ALIGNMENT_KILLER,
    ALIGNMENT_AGRESSOR
};

class Fight{
    protected:
        tgui::String fight_log;
        std::vector<Actor*> fighters;
        std::queue<FightAction*> fight_actions;
        std::map <Actor*,int> alignments;
        int maxTime = 10;
    public:
        void simulateFight();
        void addFighter(Actor *fighter, int alignment);
        void addMaxTime(int time);
        int get_alignment(Actor* fighter);
        void removeFighter(Actor *fighter);
        Actor *getTarget(Actor *actor);
        void getAction(Actor *actor);
        void results();
        tgui::String getLog();
};

#endif