#ifndef V_ENGINE
#define V_ENGINE

#include <iostream>
#include <vector>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

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
        sf::RenderWindow window{{800, 600}, "CCPanico"};
        tgui::Gui gui{window};
        void game();                                    // A FUNÇÃO!!!!!
        void PlayerTurn1(Player *player);
        void playerTurn2(Player *player);
        void playerTurn3(Player *player);
        void pass_screen();
        void main_menu();
        void results();
        void createPlayer(std::string name, int atributes[6]);
        void characterCreator();
};

#endif