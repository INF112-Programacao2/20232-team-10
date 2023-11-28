#ifndef V_FIGHT_ACTIONS
#define V_FIGHT_ACTIONS

class FightAction{
    protected:
        tgui::String actorText;
        tgui::String neutralText;
        tgui::String targetText;
        int weight;
        int damage;
};

#endif

#ifndef V_FIGHTER_CLASS
#define V_FIGHTER_CLASS

#include <vector>

class FighterClass{
    protected:
        std::vector<int> fighter_actions_ids;
    public:
        FightAction *chooseFightAction();
};

#endif

#ifndef V_FIGHT
#define V_FIGHT

#include <vector>
#include <queue>
#include "player.h"

class Fight{
    protected:
        std::vector<Actor*> fighters;
        std::queue<FightAction*> fight_actions;
    public:

};

#endif