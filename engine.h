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
        //std::vector<Place*> places;
        unsigned int time = 0;

    public:
        void game();                                    // A FUNÇÃO!!!!!
        void day();
        void PlayerTurn1(Player *player);
        void playerTurn2(Player *player);
        void playerTurn3(Player *player);
        void playerTurn4(Player *player);
        void results();
        void createPlayer(std::string name, int atributes[6]);
        void characterCreator();
};

#endif