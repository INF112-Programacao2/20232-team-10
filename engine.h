#ifndef V_ENGINE
#define V_ENGINE

#include <iostream>
#include <vector>

#include "actions.h"
#include "actor.h"
#include "player.h"

class Engine {
    private:
        std::vector<Player*> players;
        std::vector<Action*> turn_actions;
        unsigned int time = 0;

    public:
        void game();                                    // A FUNÇÃO!!!!!
        void playerTurn(Player *player);
        void results();
};

#endif