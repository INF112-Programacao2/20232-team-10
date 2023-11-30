#ifndef V_ENGINE
#define V_ENGINE

#include <vector>
#include <queue>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "actions.h"
#include "actor.h"
#include "player.h"

int triang(int n);

class Engine {
    private:
        std::vector<Player*> players;
        std::queue<Action*> turn_actions;
        //std::vector<Place*> places;
        unsigned int time = 0;

    public:
        sf::RenderWindow window{{800, 600}, "CCPanico"};
        tgui::Gui gui{window};
        void game();                                    // A FUNÇÃO!!!!!
        void playerTurn1(Player *player);
        void playerTurn2(Player *player);
        void playerTurn3(Player *player);
        void pass_screen(Player *player);
        void character_creator_screen();
        void main_menu();
        void results();
        void createPlayer(tgui::String name, int atributes[6]);
        void characterCreator();
        void result_screen(Player *player);

};

#endif
