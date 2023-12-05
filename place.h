#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <vector>
#include <map>
#include "TGUI\TGUI.hpp"

//Locais onde o usuário pode visitar;

class Place {
    private:
        tgui::String name;
        tgui::String picture;
        int id;
        static int next_id;
    public:
        std::vector<int> placeActions;   //Vector para armazenar os lugares
        std::map<int, int> actionBonus;
        tgui::String getName();
        tgui::String getPicture();
        Place(tgui::String name, tgui::String picture);         //Construtor
};

#endif