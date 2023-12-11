#ifndef V_ENGINE
#define V_ENGINE

#include <vector>
#include <queue>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <SFML/Audio.hpp>

#include "actions.h"
#include "actor.h"
#include "place.h"
#include "player.h"

int triang(int n);

const int PLACE_NUM = 6;
const int MAX_TIME = 8;

enum endings{
    NO_ENDING,
    KILL_THE_KILLER_ENDING,
    KILLER_WIN_ENDING,
    END_OF_SEMESTER_ENDING,
    EVERYONE_DEAD_ENDING,
};

class Engine {
    private:
        std::vector<Player*> players;
        std::queue<Action*> turn_actions;
        std::vector<Place*> places;
        unsigned int game_time = 0;

    public:
        sf::RenderWindow window{{800, 600}, "CCPanico"};
        tgui::Gui gui{window};
        sf::Music horrorgame;
        void game(int player_num, int turn1_time, int turn2_time);                                    // A FUNÇÃO!!!!!
        void game_settings();
        void playerTurn1(Player *player, int turn_time);
        void playerTurn2(Player *player, int turn_time);
        //void playerTurn3(Player *player);
        void pass_screen(Player *player);
        void character_creator_screen();
        void main_menu();
        void results();
        void createPlayer(tgui::String name, int atributes[6]);
        void deletePlayer(int id);
        void result_screen(Player *player);
        void role_screen(Player *player);
        void roleSelector();
        void instantiatePlaces();
        bool check_for_ending();
        void ending_screen(int ending);
        int getTime();
};

#endif
