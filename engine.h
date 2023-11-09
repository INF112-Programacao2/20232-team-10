#ifndef V_ENGINE
#define V_ENGINE

#include <iostream>
#include <vector>

#include "actions.h"
#include "actor.h"
#include "player.h"

class Engine {
    private:
        std::vector<Player*> _players;
        std::vector<Action*> _turn_actions;
        unsigned int _time = 0;

    public:
        void game();                                    // A FUNÇÃO!!!!!
        void player_turn(Player *player);
        void results();
};

#endif