#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <vector>
#include <map>
#include "TGUI/TGUI.hpp"

//Locais onde o usuário pode visitar;

class Place {
    private:
        tgui::String name;
        tgui::String picture;
        int id;
        static int next_id;
        std::map<int, int> actionBonus;
    public:
        tgui::String getName();
        tgui::String getPicture();
        void setBonus(int key, int value);
        int getBonus(int key);
        Place(tgui::String name, tgui::String picture);         //Construtor
};

#endif