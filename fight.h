#ifndef V_FIGHT_ACTIONS
#define V_FIGHT_ACTIONS

#include "player.h"

class FightAction{
    protected:
        Actor *actor;
        Actor *target;
        tgui::String actionText;
        int weight;
        int id;
    public:
        FightAction(Actor *actor, Actor *target=nullptr);
        static FightAction *FightActionByID(int id, Actor *actor = nullptr, Actor *target = nullptr);
        tgui::String getText();
        int getID();
        int getWeight();
        virtual void execute() = 0;
        virtual bool possible();
};

class FA_Punch : public FightAction{
    public:
        FA_Punch(Actor *actor, Actor *target);
        virtual void execute() override;
};

class FA_KnifeSlash : public FightAction{
    public:
        FA_KnifeSlash(Actor *actor, Actor *target);
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

class Fight{
    protected:
        tgui::String fight_log;
        std::vector<Actor*> fighters;
        std::vector<FightAction*> local_actions;
        std::queue<FightAction*> fight_actions;
        std::map <Actor*,int> alignments;
    public:
        void simulateFight();
        void addFighter(Actor *fighter, int alignment);
        void removeFighter(Actor *fighter);
        Actor *getTarget(Actor *actor);
        void getAction(Actor *actor);
        void results();
        tgui::String getLog();
};

#endif